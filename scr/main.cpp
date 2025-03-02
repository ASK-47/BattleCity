#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>

#include <glm/vec2.hpp>

#include "Game/Game.h"

#include "Resources/ResourceManager.h"
#include "Renderer/Renderer.h"

#include "Physics/PhysicsEngine.h"

glm::ivec2 g_windowSize(13 * 16, 14 * 16);
std::unique_ptr<Game> g_game = std::make_unique<Game>(g_windowSize);

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height) {
    g_windowSize.x = width;
    g_windowSize.y = height;
    //const float level_aspect_ratio = 13.f / 14.f;
    const float level_aspect_ratio = static_cast<float>(g_game->getCurrentLevelWidth()) / g_game->getCurrentLevelHeight();
    unsigned int viewPortWidth = g_windowSize.x;
    unsigned int viewPortHeight = g_windowSize.y;
    unsigned int viewPortLeftOffset = 0;
    unsigned int viewPortBottomOffset = 0;

    if (static_cast<float>(g_windowSize.x) / g_windowSize.y > level_aspect_ratio) {
        viewPortWidth = static_cast<unsigned int>(g_windowSize.y * level_aspect_ratio);
        viewPortLeftOffset = (g_windowSize.x - viewPortWidth) / 2;
    }
    else {
        viewPortHeight = static_cast<unsigned int>(g_windowSize.x / level_aspect_ratio);
        viewPortBottomOffset = (g_windowSize.y - viewPortHeight) / 2;
    }
    RenderEngine::Renderer::setViewport(viewPortWidth, viewPortHeight, viewPortLeftOffset, viewPortBottomOffset);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode) {    
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {//close the window by ESCAPE
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    } 
    g_game->setKey(key, action);
}

int main(int argc, char** argv) {    
    if (!glfwInit()) {
        std::cout << "glfwInit failed" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);    
    
    GLFWwindow* pWindow = glfwCreateWindow(g_windowSize.x, g_windowSize.y, "Battle City", nullptr, nullptr);
    if (!pWindow) {
        std::cout << "glfwCreateWindow failed" << std::endl;
        glfwTerminate();
        return -1;
    }    
    
    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);    
    glfwMakeContextCurrent(pWindow);
	
	if(!gladLoadGL()) {
		std::cout << "Can't load GLAD" << std::endl;
		return -1;
	}		
    
    std::cout << "Renderer: " << RenderEngine::Renderer::getRendererStr() << std::endl;      
    std::cout << "OpenGL version: " << RenderEngine::Renderer::getVersionStr() << std::endl;
    
    RenderEngine::Renderer::setClearColor(0, 0, 0, 1);  
    RenderEngine::Renderer::setDepthTest(true);
    {
        ResourceManager::setExecutablePath(argv[0]);//file path for exe          
        
        PhysicsEngine::init();
        
        g_game->init();

        glfwSetWindowSize(pWindow, static_cast<int>(3*g_game->getCurrentLevelWidth()), static_cast<int>(3*g_game->getCurrentLevelHeight()));
        auto lastTime = std::chrono::high_resolution_clock::now();

        while (!glfwWindowShouldClose(pWindow)){//cycle is stopped then the window is closed           
            glfwPollEvents();//press the key, changing pos of cursor, closing the window, changing size of the window
           
            auto currentTime = std::chrono::high_resolution_clock::now();
            double duration = std::chrono::duration<double, std::milli>(currentTime - lastTime).count();
            lastTime = currentTime;//start             
            
            g_game->update(duration);
            PhysicsEngine::update(duration);
            
            RenderEngine::Renderer::clear();

            g_game->render();
            
            glfwSwapBuffers(pWindow);//changing front and back buffer frames            
        }

        PhysicsEngine::terminate();
        g_game = nullptr;
        ResourceManager::unloadAllResources();
    }
    glfwTerminate();//free the resourses, stop the programm  
}