cmake_minimum_required(VERSION 3.0)

project(MinecraftChallenge VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(thirdparty/bgfx.cmake)

add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/bgfx.cmake/bgfx/include)
target_link_libraries(${PROJECT_NAME} bgfx glfw)