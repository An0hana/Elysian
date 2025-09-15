#pragma once

#include <windows.h>

/**
 * 简单窗口类 - 学习版本
 * 只专注于Windows平台，最基础的窗口功能
 */
class Window {
public:
    Window();
    ~Window();

    // 创建窗口
    bool Create(int width, int height, const char* title);
    
    // 处理窗口事件
    void ProcessEvents();
    
    // 检查窗口是否应该关闭
    bool ShouldClose() const;
    
    // 清空屏幕并开始渲染
    void BeginRender();
    
    // 完成渲染并显示
    void EndRender();

private:
    HWND m_hwnd;
    HDC m_hdc;
    HGLRC m_hglrc;
    
    bool m_shouldClose;
    
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};