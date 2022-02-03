project(ECS)

add_library(${PROJECT_NAME} ECS.cpp Mesh.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ../../../include)
target_include_directories(${PROJECT_NAME} PUBLIC ../../../thirdparty/glm)
target_include_directories(${PROJECT_NAME} PUBLIC ../../../thirdparty/glad/include)
target_link_libraries(${PROJECT_NAME} glfw glad glm ${GLFW_LIBRARIES})