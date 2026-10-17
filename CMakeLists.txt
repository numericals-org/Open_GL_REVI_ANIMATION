cmake_minimum_required(VERSION 4.2.1)
project(Revi VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(Revi
    src/main.cpp
    src/glad.c
    src/config.cpp
    src/factories/factory.cpp
    src/view/shader.cpp
    src/system/camera_system.cpp
    src/system/motion_system.cpp
    src/system/render_system.cpp
    src/controller/app.cpp
    src/system/animation_system.cpp
    src/factories/mesh_factory.cpp     
)

target_include_directories(Revi PRIVATE dependencies)
target_link_libraries(Revi PRIVATE ${GLFW3_LIBRARY} OpenGL::GL)

target_compile_definitions(Revi PRIVATE PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")