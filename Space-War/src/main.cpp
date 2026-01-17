// 导入库
#include <iostream>
#include <Windows.h>
#include <spdlog/spdlog.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <opencv2/opencv.hpp>

GLFWwindow* window;
using namespace glm;
using namespace std;
using namespace cv;

void initglfw() {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

int main()
{
	// 初始化GLFW
    if (!glfwInit())
    {
        return -1;
    }

    // 初始化图片
    Mat shipPng = imread("png/spaceship/spaceship.png", IMREAD_COLOR);

    //设置长宽
    int shipWidth = shipPng.cols;
    int shipHeight = shipPng.rows;
    //设置图像指针
    GLubyte* shipPixels;
    //设置指针长度
    int shipPixellength = shipWidth * shipHeight * 3;
    //开辟指针空间
    shipPixels = new GLubyte[shipPixellength];
    //图像指针复制
    memcpy(shipPixels, shipPng.data, shipPixellength * sizeof(char));

    // 获取屏幕大小
    HDC hdc = GetDC(NULL);
    const int cx = GetDeviceCaps(hdc, HORZRES);// 窗口x轴长度
    const int cy = GetDeviceCaps(hdc, VERTRES);// 窗口y轴长度

	// 设置GLFW窗口属性
	glfwWindowHint(GLFW_SAMPLES, 4);// 4x 抗锯齿
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);// OpenGL 3.3
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS 不需要
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 打开一个窗口并创建它的OpenGL上下文
    window = glfwCreateWindow(cx, cy, "Space War", NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 初始化GLEW
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return -1;
    }

	// 设置键盘输入模式
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// 设置清屏颜色
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    do {
        // 清屏
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 判断退出
        if (!(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)) {
            // 关闭OpenGL窗口并终止GLFW
            glfwTerminate();
            return 0;
        }
        glDrawPixels(shipWidth, shipHeight, NULL, GL_UNSIGNED_BYTE, shipPixels);
        // 交换缓冲区
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (true);
}