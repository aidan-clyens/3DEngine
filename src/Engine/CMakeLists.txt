project(Engine)

add_library(${PROJECT_NAME} Object3D.cpp Renderer.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ../../include)
target_include_directories(${PROJECT_NAME} PUBLIC ../../thirdparty/bgfx.cmake/bgfx/include)
target_include_directories(${PROJECT_NAME} PUBLIC ../../thirdparty/eigen)
target_link_libraries(${PROJECT_NAME} bgfx glfw)