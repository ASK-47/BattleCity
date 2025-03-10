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

	scr/Renderer/Sprite.h
	scr/Renderer/Sprite.cpp	

	scr/Renderer/VertexBuffer.h
	scr/Renderer/VertexBuffer.cpp

	scr/Renderer/VertexArray.h
	scr/Renderer/VertexArray.cpp

	scr/Renderer/VertexBufferLayout.h
	scr/Renderer/VertexBufferLayout.cpp

	scr/Renderer/Renderer.h
	scr/Renderer/Renderer.cpp

	scr/Renderer/SpriteAnimator.h
	scr/Renderer/SpriteAnimator.cpp
	
	scr/Renderer/IndexBuffer.h
	scr/Renderer/IndexBuffer.cpp	
	
	scr/Game/Game.cpp
	scr/Game/Game.h

	scr/Game/GameStates/IGameState.h

	scr/Game/GameStates/StartScreen.cpp
	scr/Game/GameStates/StartScreen.h

	scr/Game/GameStates/Level.cpp
	scr/Game/GameStates/Level.h	

	scr/System/Timer.cpp
	scr/System/Timer.h

	scr/Physics/PhysicsEngine.cpp
	scr/Physics/PhysicsEngine.h
	
	scr/Game/GameObjects/Tank.cpp
	scr/Game/GameObjects/Tank.h

	scr/Game/GameObjects/iGameObject.cpp
	scr/Game/GameObjects/iGameObject.h	

	scr/Game/GameObjects/BrickWall.cpp
	scr/Game/GameObjects/BrickWall.h

	scr/Game/GameObjects/BetonWall.cpp
	scr/Game/GameObjects/BetonWall.h

	scr/Game/GameObjects/Trees.cpp
	scr/Game/GameObjects/Trees.h

	scr/Game/GameObjects/Ice.cpp
	scr/Game/GameObjects/Ice.h

	scr/Game/GameObjects/Eagle.cpp
	scr/Game/GameObjects/Eagle.h

	scr/Game/GameObjects/Water.cpp
	scr/Game/GameObjects/Water.h

	scr/Game/GameObjects/Border.cpp
	scr/Game/GameObjects/Border.h

	scr/Game/GameObjects/Bullet.cpp
	scr/Game/GameObjects/Bullet.h
	
	scr/Game/AIComponent.cpp
	scr/Game/AIComponent.h
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory(external/glm)
target_link_libraries(${PROJECT_NAME} glm)

include_directories(external/rapidjson/include)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)