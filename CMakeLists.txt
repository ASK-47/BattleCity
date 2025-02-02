cmake_minimum_required (VERSION 3.31 FATAL_ERROR)

set(PROJECT_NAME BattleCity)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
	scr/main.cpp

	scr/Renderer/ShaderProgram.h
	scr/Renderer/ShaderProgram.cpp

	scr/Resources/ResourceManager.h
	scr/Resources/ResourceManager.cpp

	scr/Resources/stb_image.h
	
	scr/Renderer/Texture2D.h
	scr/Renderer/Texture2D.cpp
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

add_subdirectory(external/glfw)

target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)