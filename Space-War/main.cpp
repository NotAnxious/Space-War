// 导入库文件
#include <ene.h>
#include <ship.h>
#include <main.h>
#include <bullet.h>
#pragma comment(lib,"msimg32.lib")
#pragma comment(lib,"winmm.lib")
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")// 不显示终端窗口

// 切换渲染模式：1 = 使用 EasyX BeginBatchDraw/EndBatchDraw（原来的双缓冲）
//               0 = 关闭 Begin/End，直接即时绘制（可能闪烁，但用于排查）
#define USE_EASYX_BATCH 0

using namespace std;

int main() {
	// 确保高精度定时器（请求 1ms 分辨率）
	struct TimerResolution {
		TimerResolution() { timeBeginPeriod(1); }
		~TimerResolution() { timeEndPeriod(1); }
	} _timerRes;

	// 初始化
	spdlog::info("Space War game starting");
	EnablePrivileges(GetCurrentProcess(), SE_SHUTDOWN_NAME);
	GetCpuInfo();
	// 内存判断
	if (!GetSystemMemoryUsage()) {
		spdlog::critical("Insufficient memory!");
		if (MessageBox(NULL, L"Insufficient memory!Place try again", L"Space-war", MB_RETRYCANCEL | MB_ICONHAND) == IDRETRY/*弹窗提示*/) {
			cout << "\7";
			system("start Space-War");
		}
		return 0;
	}
	// 初始化变量
	HDC hdc = GetDC(NULL);
	srand((unsigned)time(0));// 初始化时间种子方便生成随机数

	// 帧率控制参数（目标 FPS，可按需修改）
	const double targetFPS = 100.0;
	const double targetFrameMs = 1000.0 / targetFPS;

	// FPS 计算（每秒更新一次）
	int frameCount = 0;
	double currentFPS = 0.0;
	auto fpsTimer = chrono::steady_clock::now();

	HWND gameHWND = FindWindow(NULL, L"Space-War");// 获取游戏窗口句柄
	HICON icon = ExtractIcon(NULL, L"png/icon.ico", 0);// 获取窗口图标
	SendMessage(gameHWND, WM_SETTEXT, NULL, (LPARAM)icon);

	// 预加载图片
	spdlog::info("images loading");
	IMAGE myShipPng;
	IMAGE starrySkyPng;
	IMAGE LPortalPng;
	IMAGE RPortalPng;
	loadimage(&myShipPng, _T("png/spaceship/spaceship.png"));
	loadimage(&starrySkyPng, _T("png/starry-sky/starry-sky.png"));
	loadimage(&LPortalPng, _T("png/portal/left-portal.png"));
	loadimage(&RPortalPng, _T("png/portal/right-portal.png"));
	loadimage(&bulletPng, _T("png/bullet/bullet.png"));
	loadimage(&enePng, _T("png/spaceship_2/spaceship.png"));

	// 创建窗口
	spdlog::info("Creating game window");

	int rW = GetSystemMetrics(SM_CXSCREEN); // 屏幕宽度 像素
	int rH = GetSystemMetrics(SM_CYSCREEN); // 屏幕高度 像素
	spdlog::info("Screen resolution: {0}x{1}", rW, rH);
	HWND hwnd = initgraph(rW, rH); // 初始化窗口并获取窗口句柄
	spdlog::info("Game window initialized successfully");

	// 初始化窗口
	const LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE); // 获取窗口信息
	// 设置窗口信息 最大化 取消标题栏及边框
	SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);// 直接修改窗口样式
	SetWindowPos(hwnd, HWND_TOP, 0, 0, rW, rH, 0);

	// 切换输入法
	SwitchInputMethod();

	// 运行主循环
	spdlog::info("Entering main game loop");
	while (true) {

		// 本帧计时开始
		auto frameStart = chrono::steady_clock::now();

		BeginBatchDraw(); // 开始双缓冲
		cleardevice(); // 清屏

		// 按下esc键就退出
		if (pressTheEsaKey()) { return 0; }

		// 获取屏幕大小
		const int cx = GetDeviceCaps(hdc, HORZRES);// 屏幕x轴长度
		const int cy = GetDeviceCaps(hdc, VERTRES);// 屏幕y轴长度

		// 显示图片
		showImage(NULL, 0, 0, &starrySkyPng);// 星空背景(最后置)
		showImage(NULL, 0, cy - 217, &LPortalPng);// 左传送门
		showImage(NULL, cx - 150, cy - 217, &RPortalPng);// 右传送门
		// 显示敌机
		for (int i = 0; i < eneX.size(); ++i) {
			showImage(NULL, eneX[i], eneY[i], &enePng);
		}
		// 显示子弹
		for (int i = 0; i < bulletX.size(); ++i) {
			showImage(NULL, bulletX[i], bulletY[i], &bulletPng);
		}
		showImage(NULL, shipX, cy - 204, &myShipPng);// 我方飞船(最前置)

		// 随机生成敌机
		if (getRand(1,60) == 1) {
			addENE(getRand(0, cx - 400));
		}
		createbullet(returnShipX(), cy - 204);// 创建子弹

		// 刷新坐标
		RefreshShipPosit();
		RefreshENEPosit();
		RefreshBulletPosit();
		// 碰撞检测
		collisionDetection();

		// 防止超出屏幕
		if (shipX >= cx) { shipX = -125; }// 超过右边
		if (shipX <= -126) { shipX = cx; }// 超过左边
		eneOutOfScreenDetection(cy);
		bulletOutOfScreenDetection();

		EndBatchDraw(); // 结束双缓冲绘图

		// FPS 统计
		frameCount++;
		auto now = chrono::steady_clock::now();
		auto fpsElapsed = chrono::duration_cast<chrono::duration<double>>(now - fpsTimer);
		if (fpsElapsed.count() >= 1.0) {
			currentFPS = frameCount / fpsElapsed.count();
			frameCount = 0;
			fpsTimer = now;
			spdlog::info("FPS: {0}", currentFPS);
		}

		// 帧率限制：先 Sleep 大部分剩余时间，再自旋等待精确到目标（减少 Sleep 过长导致的欠帧）
		auto frameEnd = chrono::steady_clock::now();
		double elapsedMs = chrono::duration<double, milli>(frameEnd - frameStart).count();
		double remainMs = targetFrameMs - elapsedMs;

		if (remainMs > 1.5) {
			// Sleep 剩余时间减去一点（留给后续自旋）
			DWORD sleepTime = (DWORD)(remainMs)-1;
			Sleep(sleepTime);
		}
		// 自旋/让出直到到达目标时间点（精确对齐）
		while (chrono::duration<double, milli>(chrono::steady_clock::now() - frameStart).count() < targetFrameMs) {
			// 轻量让出 CPU，避免完全忙等
			std::this_thread::yield();
		}
	}
}