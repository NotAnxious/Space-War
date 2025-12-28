// 导入库文件
#include <conio.h>
#include <graphics.h>
#include <spdlog.h>
#include <iostream>
#include <vector>
#include <Windows.h>
#include <cstdlib>
#include <ctime>
#include <ene.h>
#include <ship.h>
#include <main.h>
#pragma comment(lib,"msimg32.lib")
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

using namespace std;


int main() {
	// 初始化
	spdlog::info("Space War game starting");
	EnablePrivileges(GetCurrentProcess(), SE_SHUTDOWN_NAME);
	GetCpuInfo();
	// 内存判断
	if (!GetSystemMemoryUsage()) {
		spdlog::critical("Insufficient memory!");
		if (MessageBox(NULL, L"Insufficient memory!Place try again", L"Space-war", MB_RETRYCANCEL|MB_ICONHAND) == IDRETRY/*弹窗提示*/) {
			cout << "\7";
			system("start Space-War");
		}
		return 0;
	}

	// 初始化变量
	HDC hdc = GetDC(NULL);
	clock_t Tstart, Tend;// 计时器
	srand(time(0));// 初始化时间种子方便生成随机数

	HWND gameHWND = FindWindow(NULL,L"Space-War");// 获取游戏窗口句柄
	HICON icon = ExtractIcon(NULL, L"png/icon.ico", 0);// 获取窗口图标
	SendMessage(gameHWND, WM_SETTEXT, NULL, (LPARAM)icon);

	// 预加载图片
	spdlog::info("images loading");
	IMAGE myShipPng;
	IMAGE enePng;
	IMAGE starrySkyPng;
	IMAGE LPortalPng;
	IMAGE RPortalPng;
	loadimage(&myShipPng, _T("png/spaceship/spaceship.png"));
	loadimage(&starrySkyPng,_T("png/starry-sky/starry-sky.png"));
	loadimage(&LPortalPng, _T("png/portal/left-portal.png"));
	loadimage(&RPortalPng, _T("png/portal/right-portal.png"));
	loadimage(&enePng, _T("png/spaceship_2/spaceship.png"));

	// 创建窗口
	spdlog::info("Creating game window");
	
	int rW = GetSystemMetrics(SM_CXSCREEN); // 屏幕宽度 像素
	int rH = GetSystemMetrics(SM_CYSCREEN); // 屏幕高度 像素
	spdlog::info("Screen resolution: {0}x{1}", rW, rH);
	HWND hwnd = initgraph(rW, rH); // 初始化窗口并获取窗口句柄
	spdlog::info("Game window initialized successfully");

	// 初始化窗口
	LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE); // 获取窗口信息
	// 设置窗口信息 最大化 取消标题栏及边框
	SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);// 直接修改窗口样式
	SetWindowPos(hwnd, HWND_TOP, 0, 0, rW, rH, 0);
	
	// 切换输入法

	SwitchInputMethod();

	// 运行主循环
	spdlog::info("Entering main game loop");
	while (true) {
		Tstart = clock();// 开始计时
		BeginBatchDraw(); // 开始双缓冲
		cleardevice(); // 清屏
		// 获取屏幕大小
		const int cx = GetDeviceCaps(hdc, HORZRES);// 屏幕x轴长度
		const int cy = GetDeviceCaps(hdc, VERTRES);// 屏幕y轴长度

		// 显示图片
		showImage(NULL, 0, 0, &starrySkyPng);// 星空背景(最后置)
		showImage(NULL, 0, cy - 217, &LPortalPng);// 左传送门
		showImage(NULL, cx - 150, cy - 217, &RPortalPng);// 右传送门
		showImage(NULL, shipX, cy - 204, &myShipPng);// 我方飞船(最前置)
		
		// 按下esc键就退出
		if (pressTheEsaKey()) { return 0; }
		// 刷新坐标
		RefreshShipPosit();
		RefreshENEPosit();
		// 防止飞船超出屏幕
		if (shipX >= cx) { shipX = -125; }// 超过右边
		if (shipX <= -126) { shipX = cx; }// 超过左边

		EndBatchDraw(); // 结束双缓冲绘图
		Sleep(1);
	}
}