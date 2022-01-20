cmake_minimum_required(VERSION 3.0)

project(3DEngine VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)

add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/glm)

add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/glfw)
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/glm)
target_include_directories(${PROJECT_NAME} PUBLIC thirdparty/glad/include)
target_link_libraries(${PROJECT_NAME} EngineCore)
