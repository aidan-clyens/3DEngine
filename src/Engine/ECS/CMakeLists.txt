project(ECS)

add_library(${PROJECT_NAME} ECS.cpp Mesh.cpp MeshInstances.cpp Model.cpp Rigidbody.cpp DynamicCharacterController.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ../../../include)
target_include_directories(${PROJECT_NAME} PUBLIC ../../../thirdparty/bullet3/src)
target_include_directories(${PROJECT_NAME} PUBLIC ../../../thirdparty/glm)
target_include_directories(${PROJECT_NAME} PUBLIC ../../../thirdparty/glad/include)
target_include_directories(${PROJECT_NAME} PUBLIC ../../../thirdparty/assimp/include)
target_link_libraries(${PROJECT_NAME} glfw glad glm assimp BulletDynamics BulletCollision LinearMath ${GLFW_LIBRARIES})