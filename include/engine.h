#pragma once

class Window;

/**
 * 简单游戏引擎核心类 - 学习版本
 * 最基础的功能：创建窗口、游戏循环、渲染
 */
class Engine {
public:
    Engine();
    ~Engine();

    // 初始化引擎
    bool Initialize(int width = 800, int height = 600, const char* title = "Simple Game Engine");
    
    // 运行游戏主循环
    void Run();

protected:
    // 虚函数，供继承的游戏类重写
    virtual void OnUpdate() {}
    virtual void OnRender() {}

private:
    Window* m_window;
    bool m_running;
};