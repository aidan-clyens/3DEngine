project(ECS)

add_library(${PROJECT_NAME} ECS.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ../../../include)