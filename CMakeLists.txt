cmake_minimum_required(VERSION 3.0)

project(MinecraftChallenge VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(thirdparty/bgfx.cmake)
add_subdirectory(thirdparty/glfw)

add_executable(${PROJECT_NAME} src/main.cpp)