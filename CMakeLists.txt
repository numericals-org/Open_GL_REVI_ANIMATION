cmake_minimum_required(VERSION 4.2.1)
project(Revi VERSION 1.0.0)
cmake_policy(SET CMP0072 NEW)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(Revi
    src/main.cpp
    src/config.cpp
)

target_include_directories(Revi PRIVATE dependencies)

target_link_libraries(Revi PRIVATE ${GLFW3_LIBRARY} OpenGL::GL)

target_compile_definitions(Revi PRIVATE PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")