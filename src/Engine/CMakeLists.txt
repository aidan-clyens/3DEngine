project(EngineCore)

add_subdirectory(ECS)

add_library(${PROJECT_NAME} Engine.cpp Object3D.cpp Renderer.cpp InputManager.cpp Camera.cpp Shader.cpp Texture.cpp Texture2D.cpp DepthTexture.cpp TextureCubeMap.cpp SquareMesh.cpp CubeMesh.cpp Physics.cpp utils/load_image.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ../../include)
target_include_directories(${PROJECT_NAME} PUBLIC ../../thirdparty/)
target_include_directories(${PROJECT_NAME} PUBLIC ../../thirdparty/bullet3/src)
target_include_directories(${PROJECT_NAME} PUBLIC ../../thirdparty/glfw)
target_include_directories(${PROJECT_NAME} PUBLIC ../../thirdparty/glm)
target_include_directories(${PROJECT_NAME} PUBLIC ../../thirdparty/glad/include)
target_link_libraries(${PROJECT_NAME} ECS glfw glad glm BulletDynamics BulletCollision LinearMath ${GLFW_LIBRARIES})
