#include "engine.h"
#include <iostream>
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#ifdef _WIN32
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#endif

/**
 * 超简单的游戏示例
 * 只显示一个旋转的三角形
 */
class MyFirstGame : public Engine {
private:
    float rotation;

public:
    MyFirstGame() : rotation(0.0f) {}

protected:
    void OnUpdate() override {
        // 简单的旋转动画
        rotation += 1.0f;
        if (rotation > 360.0f) {
            rotation = 0.0f;
        }
    }

    void OnRender() override {
        // 设置2D视图
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef(rotation, 0.0f, 0.0f, 1.0f);
        
        // 画一个彩色三角形
        glBegin(GL_TRIANGLES);
            glColor3f(1.0f, 0.0f, 0.0f); // 红色
            glVertex2f(0.0f, 0.5f);
            
            glColor3f(0.0f, 1.0f, 0.0f); // 绿色
            glVertex2f(-0.5f, -0.5f);
            
            glColor3f(0.0f, 0.0f, 1.0f); // 蓝色
            glVertex2f(0.5f, -0.5f);
        glEnd();
    }
};

int main() {
    std::cout << "=== My First Game Engine ===" << std::endl;
    std::cout << "Press ESC or close window to exit" << std::endl;

    MyFirstGame game;

    if (!game.Initialize(800, 600, "My First Game")) {
        std::cout << "Failed to initialize!" << std::endl;
        return -1;
    }

    game.Run();

    std::cout << "Game ended!" << std::endl;
    return 0;
}