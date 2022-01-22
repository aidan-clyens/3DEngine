project(EngineExamples)

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ../include)
target_include_directories(${PROJECT_NAME} PUBLIC ../thirdparty/glfw)
target_include_directories(${PROJECT_NAME} PUBLIC ../thirdparty/glm)
target_include_directories(${PROJECT_NAME} PUBLIC ../thirdparty/glad/include)
target_link_libraries(${PROJECT_NAME} EngineCore)