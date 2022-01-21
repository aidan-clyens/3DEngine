project(EngineCore)

add_library(${PROJECT_NAME} Object3D.cpp Renderer.cpp Camera.cpp Shader.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ../../include)
target_include_directories(${PROJECT_NAME} PUBLIC ../../thirdparty/glfw)
target_include_directories(${PROJECT_NAME} PUBLIC ../../thirdparty/glm)
target_include_directories(${PROJECT_NAME} PUBLIC ../../thirdparty/glad/include)
target_link_libraries(${PROJECT_NAME} glfw glad glm ${GLFW_LIBRARIES})
