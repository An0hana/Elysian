cmake_minimum_required(VERSION 3.10)
project(SimpleGameEngine)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加头文件目录
include_directories(include)

# 源文件
set(ENGINE_SOURCES
    src/engine.cpp
    src/window.cpp
)

set(DEMO_SOURCES
    examples/main.cpp
)

# Windows系统库
if(WIN32)
    set(SYSTEM_LIBS opengl32 gdi32 user32 glu32)
endif()

# 创建游戏可执行文件
add_executable(game ${ENGINE_SOURCES} ${DEMO_SOURCES})

# 链接库
target_link_libraries(game ${SYSTEM_LIBS})

# 设置输出目录
set_target_properties(game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)