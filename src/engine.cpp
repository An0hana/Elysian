#include "engine.h"
#include "window.h"
#include <iostream>

Engine::Engine() 
    : m_window(nullptr)
    , m_running(false)
{
}

Engine::~Engine() {
    if (m_window) {
        delete m_window;
    }
}

bool Engine::Initialize(int width, int height, const char* title) {
    std::cout << "Initializing Simple Game Engine..." << std::endl;

    // 创建窗口
    m_window = new Window();
    if (!m_window->Create(width, height, title)) {
        std::cout << "Failed to create window!" << std::endl;
        return false;
    }

    m_running = true;
    std::cout << "Engine initialized successfully!" << std::endl;
    return true;
}

void Engine::Run() {
    std::cout << "Starting game loop..." << std::endl;

    while (m_running && !m_window->ShouldClose()) {
        // 处理窗口事件
        m_window->ProcessEvents();

        // 调用游戏逻辑
        OnUpdate();

        // 渲染
        m_window->BeginRender();
        OnRender();
        m_window->EndRender();
    }

    std::cout << "Game loop ended." << std::endl;
}