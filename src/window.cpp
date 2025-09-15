#include "window.h"
#include <iostream>
#include <gl/GL.h>

Window::Window() 
    : m_hwnd(nullptr)
    , m_hdc(nullptr)
    , m_hglrc(nullptr)
    , m_shouldClose(false)
{
}

Window::~Window() {
    if (m_hglrc) {
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(m_hglrc);
    }
    if (m_hdc) {
        ReleaseDC(m_hwnd, m_hdc);
    }
    if (m_hwnd) {
        DestroyWindow(m_hwnd);
    }
}

LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    
    switch (uMsg) {
        case WM_CLOSE:
        case WM_DESTROY:
            if (window) {
                window->m_shouldClose = true;
            }
            return 0;
            
        case WM_KEYDOWN:
            if (wParam == VK_ESCAPE) {
                if (window) {
                    window->m_shouldClose = true;
                }
            }
            return 0;
    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool Window::Create(int width, int height, const char* title) {
    // 注册窗口类
    WNDCLASSA wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = "SimpleGameEngine";
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

    RegisterClassA(&wc);

    // 创建窗口
    m_hwnd = CreateWindowA(
        "SimpleGameEngine",
        title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        width, height,
        nullptr, nullptr,
        GetModuleHandle(nullptr),
        nullptr
    );

    if (!m_hwnd) {
        std::cout << "Failed to create window!" << std::endl;
        return false;
    }

    // 设置窗口用户数据
    SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

    // 获取设备上下文
    m_hdc = GetDC(m_hwnd);

    // 设置像素格式
    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;

    int pixelFormat = ChoosePixelFormat(m_hdc, &pfd);
    SetPixelFormat(m_hdc, pixelFormat, &pfd);

    // 创建OpenGL上下文
    m_hglrc = wglCreateContext(m_hdc);
    wglMakeCurrent(m_hdc, m_hglrc);

    // 显示窗口
    ShowWindow(m_hwnd, SW_SHOW);

    std::cout << "Window created: " << width << "x" << height << std::endl;
    return true;
}

void Window::ProcessEvents() {
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

bool Window::ShouldClose() const {
    return m_shouldClose;
}

void Window::BeginRender() {
    // 清屏
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::EndRender() {
    // 交换缓冲区
    SwapBuffers(m_hdc);
}