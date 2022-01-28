project(EngineCore)

add_library(${PROJECT_NAME} Engine.cpp Object3D.cpp Renderer.cpp Camera.cpp Shader.cpp Texture.cpp Texture2D.cpp Cube.cpp utils/load_image.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ../../include)
target_include_directories(${PROJECT_NAME} PUBLIC ../../thirdparty/)
target_include_directories(${PROJECT_NAME} PUBLIC ../../thirdparty/glfw)
target_include_directories(${PROJECT_NAME} PUBLIC ../../thirdparty/glm)
target_include_directories(${PROJECT_NAME} PUBLIC ../../thirdparty/glad/include)
target_link_libraries(${PROJECT_NAME} glfw glad glm ${GLFW_LIBRARIES})
