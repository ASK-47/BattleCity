cmake_minimum_required (VERSION 3.31 FATAL_ERROR)

set(PROJECT_NAME BattleCity)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} 
	scr/main.cpp
	scr/Renderer/ShaderProgram.h
	scr/Renderer/ShaderProgram.cpp
)

add_subdirectory(external/glfw)

target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)