#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>

#include <glm/vec2.hpp>

//TO INIT GAME
#include "Game/Game.h"

//TO READ EXE-PATH, TO UNLOAD RESOURCES
#include "Resources/ResourceManager.h"
#include "Renderer/Renderer.h"

//==========================================================
// REMOVED TO Game.cpp => bool Game::init()// 
//#include "Renderer/ShaderProgram.h"
//#include "Renderer/Texture2D.h"
//#include "Renderer/Sprite.h"//
//#include "Renderer/AnimatedSprite.h"
//==========================================================

//==========================================================
// DO NOT NEED TRIANGLES ANY MORE
//GLfloat points[] = {
//    0.0f, 50.0f, 0.0f,
//    50.0f, -50.0f, 0.0f,
//    -50.0f, -50.0f, 0.0f
//};
//
//GLfloat colors[] = {
//    1.0f, 0.0f, 0.0f,
//    0.0f, 1.0f, 0.0f,
//    0.0f, 0.0f, 1.0f
//};
//
//GLfloat texCoord[] = {
//    0.5f, 1.0f,
//    1.0f, 0.0f,
//    0.0f, 0.0f
//};
//==========================================================

//==========================================================
//REMOVED INTO VERTEX FILES
/*
//micro-programm for vertex shader
const char* vertex_shader =
"#version 460\n"//probably 110
"layout (location=0) in vec3 vertex_position;"
"layout (location=1) in vec3 vertex_color;"
"out vec3 color;"
"void main() {"
"   color=vertex_color;"
"   gl_Position=vec4(vertex_position, 1.0f);"
"}";

//micro-programm for fragment shader
const char* fragment_shader =
"#version 460\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main() {"
"   frag_color=vec4(color, 1.0f);"
"}";
*/
//==========================================================

glm::ivec2 g_windowSize(640, 480);//init window size 
Game g_game(g_windowSize);//start

//==========================================================
//DO NOT NEED EAGLE ANYMORE
//bool isEagle = false;
//==========================================================

//Callback for changing window size
void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height) {
    g_windowSize.x = width;
    g_windowSize.y = height;
    //glViewport(0, 0, g_windowSize.x, g_windowSize.y);//coordinates and size of window for rendrering
    RenderEngine::Renderer::setViewport(width, height);
}

//Callback for pressing the keys
void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode) {    
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {//close the window by ESCAPE
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
    //if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {//activate isEagle by ENTER
    //    isEagle = !isEagle;
    //}
    g_game.setKey(key, action);
}

int main(int argc, char** argv) {    

    /* Initialize the library */
    //check that library was init
    if (!glfwInit()) {
        std::cout << "glfwInit failed" << std::endl;
        return -1;
    }

    //VIDEO ADAPTER INIT
    //We want to use GLFW 4..6  and OPEN GL core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(g_windowSize.x, g_windowSize.y, "Battle City", nullptr, nullptr);
    //check that window was created
    if (!pWindow) {
        std::cout << "glfwCreateWindow failed" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    //Registation of callback functions
    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);
	
	if(!gladLoadGL()) {
		std::cout << "Can't load GLAD" << std::endl;
		return -1;
	}		
	
    //Info about device
    //std::cout << "Render: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Renderer: " << RenderEngine::Renderer::getRendererStr() << std::endl;
    
    //Info about OpenGL version
    //std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	//std::cout << "OpenGL" << GLVersion.major << "." << GLVersion.minor << std::endl;	 
    std::cout << "OpenGL version: " << RenderEngine::Renderer::getVersionStr() << std::endl;

    //Color thst fill Window
    //glClearColor(1, 1, 0, 1);    
    //COLOUR WAS CHANGED FOR BLACK
    
    //glClearColor(0, 0, 0, 1);
    RenderEngine::Renderer::setClearColor(0, 0, 0, 1);

    //==========================================================
    // DO NOT NEED SINGLE TRIANGLE ANY MORE
    /*
    //Creating the vetrex shader
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);//passing initial code to vertex shader
    glShaderSource(vs, 1, &vertex_shader, nullptr);//vs - shader id, 1- number of C-lines, &vertex_shader - adress if C-line, nullprt - ptr to array of widths
    glCompileShader(vs);//command to compile shader

    //Creating the fragment shader
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);//passing initial code to fragment shader
    glShaderSource(fs, 1, &fragment_shader, nullptr);//vs - shader id, 1- number of C-lines, &vertex_shader - adress if C-line, nullprt - ptr to array of widths
    glCompileShader(fs);//command to compile shader

    //Linking into shader programm after vs and fs shaders compilation
    GLuint shader_programm = glCreateProgram();
    glAttachShader(shader_programm, vs);
    glAttachShader(shader_programm, fs);
    glLinkProgram(shader_programm);//linking

    //Deleting vs and fs vertex after linking
    glDeleteShader(vs);
    glDeleteShader(fs);
    */
    //==========================================================

    {
        ResourceManager::setExecutablePath(argv[0]);//file path for exe
    
    //==========================================================
    // REMOVED TO Game.cpp => bool Game::init()
    // object resourceManager ==> ResourceManager (see Game.cpp)
    // 
    //ResourceManager resourceManager(argv[0]);//file path for exe    
    //    auto pDefaultShaderProgram = resourceManager.loadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
    //    if (!pDefaultShaderProgram) {
    //        std::cerr << "Can't create shader program: " << "DefaultShader" << std::endl;
    //        return -1;
    //    }
    //    /*std::string vertexShader(vertex_shader);
    //    std::string fragmentShader (fragment_shader);
    //    Renderer::ShaderProgram shaderProgram(vertexShader, fragment_shader);//ctor call
    //    if (!shaderProgram.isCompiled()) {//in case of error
    //        std::cerr << "Can't create shader program!" << std::endl;
    //        return -1;
    //    }
    //    */

    //    auto pSpriteShaderProgram = resourceManager.loadShaders("SpriteShader", "res/shaders/vSprite.txt", "res/shaders/fSprite.txt");
    //    if (!pSpriteShaderProgram) {
    //        std::cerr << "Can't create shader program: " << "SpriteShader" << std::endl;
    //        return -1;
    //    }

    //    //Load texture
    //    auto tex = resourceManager.loadTexture("DefaultTexture", "res/textures/map_16x16.png");

    //    //Load sprite
    //    //auto pSprite = resourceManager.loadSprite("NewSprite", "Default Texture", "SpriteShader", 50, 100);
    //    //std::vector<std::string> subTexturesNames = { "block", "topBlock", "bottomBlock", "leftBlock", "rightBlock", "topLeftBlock", "topRightBlock", "bottomLeftBlock", "bottomRightBlock", "beton" };
    //    
    //    std::vector<std::string> subTexturesNames = {
    //        "block",
    //        "topBlock",
    //        "bottomBlock",
    //        "leftBlock",
    //        "rightBlock",
    //        "topLeftBlock",
    //        "topRightBlock",
    //        "bottomLeftBlock",
    //        "bottomRightBlock",
    //        
    //        "beton",
    //        "topBeton",
    //        "bottomBeton",
    //        "leftBeton",
    //        "rightBeton",
    //        "topLeftBeton",
    //        "topRightBeton",
    //        "bottomLeftBeton",
    //        "bottomRightBeton",

    //        "water1",
    //        "water2",
    //        "water3",
    //        
    //        "trees",
    //        "ice",
    //        "wall",

    //        "eagle",
    //        "deadEagle",
    //        
    //        "nothing",
    //        "respawn1",
    //        "respawn2",
    //        "respawn3",
    //        "respawn4"
    //    };      
    //            
    //    auto pTextureAtlas = resourceManager.loadTextureAtlas("DefaultTextureAtlas", "res/textures/map_16x16.png", std::move(subTexturesNames), 16, 16);
    //    
    //    auto pSprite = resourceManager.loadSprite("NewSprite", "DefaultTextureAtlas", "SpriteShader", 100, 100, "beton");
    //    pSprite->setPosition(glm::vec2(300, 100));//set position for static sprite

    //    auto pAnimatedSprite = resourceManager.loadAnimatedSprite("NewAnimatedSprite", "DefaultTextureAtlas", "SpriteShader", 100, 100, "beton");//init subtexture for animated sprite
    //    pAnimatedSprite->setPosition(glm::vec2(300, 300));//set position for animated sprite

    //    std::vector<std::pair<std::string, uint64_t>> waterState;//new subtxture for animated sprite
    //    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water1", 1000000000));
    //    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water2", 1000000000));
    //    waterState.emplace_back(std::make_pair<std::string, uint64_t>("water3", 1000000000));
    //    
    //    std::vector<std::pair<std::string, uint64_t>> eagleState;//new subtxture for animated sprite
    //    eagleState.emplace_back(std::make_pair<std::string, uint64_t>("eagle", 1000000000));
    //    eagleState.emplace_back(std::make_pair<std::string, uint64_t>("deadEagle", 1000000000));
    //    
    //    //insert of states
    //    pAnimatedSprite->insertState("waterState", std::move(waterState));
    //    pAnimatedSprite->insertState("eagleState", std::move(eagleState));

    //    pAnimatedSprite->setState("waterState");
    
    //==========================================================
    // DO NOT NEED TRIANGLES ANYMORE
    //    //Passing shaders into display adapter
    //    //Vetex Buffer Object (VBO)
    //    GLuint points_vbo = 0;//vbo id
    //    //generation of buffer
    //    glGenBuffers(1, &points_vbo);//1- number of buffers, &points_vbo adress of buffer
    //    //making the generated buffer current
    //    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    //    //passing buffer info to video adapter
    //    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    //    //type of buffer, size of data, dats, hint for video adapter

    //    //Color Buffer Object (CBO)
    //    GLuint colors_vbo = 0;
    //    glGenBuffers(1, &colors_vbo);
    //    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);

    //    //Texture Buffer Object (TBO)
    //    GLuint textCord_vbo = 0;
    //    glGenBuffers(1, &textCord_vbo);
    //    glBindBuffer(GL_ARRAY_BUFFER, textCord_vbo);
    //    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_STATIC_DRAW);

    //    //Creation of vertex arrays object (VAO)
    //    GLuint vao = 0;//vao id
    //    glGenVertexArrays(1, &vao);//generation of vao
    //    //making the generated array current
    //    glBindVertexArray(vao);

    //    //Activation of ponts coordinate (location=0) in vec3 vertex_position
    //    glEnableVertexAttribArray(0);//0 - position (location) for points
    //    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    //    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    //    //0-position (location)
    //    //3 - nubmer of passing vec (vec3)
    //    //GL_FLOAT type of data, 
    //    //GL_FALSE - no need to norm
    //    //0 - offset step (stride) 
    //    //nullprt - starting offset 

    //    glEnableVertexAttribArray(1);//1 - position (location) for color
    //    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    //    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    //    glEnableVertexAttribArray(2);//1 - position (location) for texture
    //    glBindBuffer(GL_ARRAY_BUFFER, textCord_vbo);
    //    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    // DO NOT NEED TRIANGLES ANYMORE
    //==========================================================

    //    pDefaultShaderProgram->use();
    //    pDefaultShaderProgram->setInt("tex", 0);//0 slot

    //    //the identity matrix just for example
    //    glm::mat4 modelMatrix_1 = glm::mat4(1.f);
    //    //1 moving of matrix (model matrix transform from local space to world space)
    //    modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(100.f, 50.f, 0.f));
    //    //2 moving of matrix (matrix transform from world space to view space) == identity matrix (nothing to transform)
    //    //3 moving of matrix (matrix transform from view space to clip space)

    //    glm::mat4 modelMatrix_2 = glm::mat4(1.f);
    //    //1 moving of matrix (model matrix transform from local space to world space)
    //    modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(590.f, 50.f, 0.f));

    //    glm::mat4 projectlMatrix = glm::ortho(0.f, static_cast<float>(g_windowSize.x), 0.f, static_cast<float>(g_windowSize.y), -100.f, 100.f);
    //    pDefaultShaderProgram->setMatrix4("projectionMat", projectlMatrix);

    //    pSpriteShaderProgram->use();
    //    pSpriteShaderProgram->setInt("tex", 0);//0 set into slot 0
    //    pSpriteShaderProgram->setMatrix4("projectionMat", projectlMatrix);
            
        g_game.init();
        auto lastTime = std::chrono::high_resolution_clock::now();


        /* Loop until the user closes the window */
       //rendering
        while (!glfwWindowShouldClose(pWindow))//cycle is stopped then the window is closed
        {
            //==========================================================
            //DO NOT NEED EAGLE ANYMORE
            /*if (isEagle) {
                pAnimatedSprite->setState("eagleState");
            }
            else {
                pAnimatedSprite->setState("waterState");
            }*/
            //==========================================================
            
            /* Poll for and process events */
            glfwPollEvents();//press the key, changing pos of cursor, closing the window, changing size of the window

            //update
            auto currentTime = std::chrono::high_resolution_clock::now();
            uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();//while cycle duration
            lastTime = currentTime;//start 
            //pAnimatedSprite->update(duration);//update every cycle
            g_game.update(duration);
            
            /* Render here */
            //glClear(GL_COLOR_BUFFER_BIT);//frame rendering (clearing the screen)
            RenderEngine::Renderer::clear();


            //==========================================================
            // DO NOT NEED TRIANGLES ANYMORE
            //Chosing the shaders programm

            //glUseProgram(shader_programm);
            //shaderProgram.use();
            //pDefaultShaderProgram->use();

            ////pDefaultShaderProgram->setInt("tex", 0);//0 slot

            //glBindVertexArray(vao);//enable current vertex arrays object (VAO)
            //tex->bind();
            //
            //pDefaultShaderProgram->setMatrix4("modelMat", modelMatrix_1);
            //glDrawArrays(GL_TRIANGLES, 0, 3);//drawning vao
            ////GL_TRIANGLES - type of vertex interpretation
            ////0 - starting point in vec3
            ////3 - number of vertex (points)

            //pDefaultShaderProgram->setMatrix4("modelMat", modelMatrix_2);
            //glDrawArrays(GL_TRIANGLES, 0, 3);
            //pSprite->render();//render static sprite
            //==========================================================

            //==========================================================
            // UPDATE OF ANIMATES SPRITES IS DONE ABOVE g_game.update(duration) 
            //pAnimatedSprite->render();//render animated sprite            
            //==========================================================            

            g_game.render();

            /* Swap front and back buffers */
            glfwSwapBuffers(pWindow);//changing front and back buffer frames
            
        }
        ResourceManager::unloadAllResources();
    }
    glfwTerminate();//free the resourses, stop the programm  
}