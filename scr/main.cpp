#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/vec2.hpp>
#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include "Renderer/ShaderProgram.h"
#include "Resources/ResourceManager.h"
#include "Renderer/Texture2D.h"
#include "Renderer/Sprite.h"


GLfloat points[] = {
    0.0f, 50.0f, 0.0f,
    50.0f, -50.0f, 0.0f,
    -50.0f, -50.0f, 0.0f
};

GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

GLfloat texCoord[] = {
    0.5f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f
};

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

glm::ivec2 g_windowSize(640, 480);

//Callback for changing window size
void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height) {
    g_windowSize.x = width;
    g_windowSize.y = height;
    glViewport(0, 0, g_windowSize.x, g_windowSize.y);//coordinates and size of window for rendrering
}

//Callback for pressing the keys
void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode) {
    
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);//close the window        
    }    
}

int main(int argc, char** argv) {    

    /* Initialize the library */
    //check that library was init
    if (!glfwInit())
    {
        std::cout << "glfwInit failed" << std::endl;
        return -1;
    }

    //We want to use GLFW 4..6  and OPEN GL core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(g_windowSize.x, g_windowSize.y, "Battle City", nullptr, nullptr);
    //check that window was created
    if (!pWindow)
    {
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
    std::cout << "Render: " << glGetString(GL_RENDERER) << std::endl;
    
    //Info about OpenGL version
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	//std::cout << "OpenGL" << GLVersion.major << "." << GLVersion.minor << std::endl;
	
    //Color thst fill Window
	glClearColor(1, 1, 0, 1);

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

    {
    ResourceManager resourceManager(argv[0]);//file path for exe    
        auto pDefaultShaderProgram = resourceManager.loadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
        if (!pDefaultShaderProgram) {
            std::cerr << "Can't create shader program: " << "DefaultShader" << std::endl;
            return -1;
        }
        /*std::string vertexShader(vertex_shader);
        std::string fragmentShader (fragment_shader);
        Renderer::ShaderProgram shaderProgram(vertexShader, fragment_shader);//ctor call
        if (!shaderProgram.isCompiled()) {//in case of error
            std::cerr << "Can't create shader program!" << std::endl;
            return -1;
        }
        */

        auto pSpriteShaderProgram = resourceManager.loadShaders("SpriteShader", "res/shaders/vSprite.txt", "res/shaders/fSprite.txt");
        if (!pSpriteShaderProgram) {
            std::cerr << "Can't create shader program: " << "SpriteShader" << std::endl;
            return -1;
        }

        //Load texture
        auto tex = resourceManager.loadTexture("DefaultTexture", "res/textures/map_16x16.png");

        //Load sprite
        //auto pSprite = resourceManager.loadSprite("NewSprite", "Default Texture", "SpriteShader", 50, 100);
        std::vector<std::string> subTexturesNames = { "block", "topBlock", "bottomBlock", "leftBlock", "rightBlock", "topLeftBlock", "topRightBlock", "bottomLeftBlock", "bottomRightBlock", "beton" };
        auto pTextureAtlas = resourceManager.loadTextureAtlas("DefaultTextureAtlas", "res/textures/map_16x16.png", std::move(subTexturesNames), 16, 16);
        
        auto pSprite = resourceManager.loadSprite("NewSprite", "DefaultTextureAtlas", "SpriteShader", 100, 100, "block");
        pSprite->setPosition(glm::vec2(300, 100));

        //Passing shaders into display adapter
        //Vetex Buffer Object (VBO)
        GLuint points_vbo = 0;//vbo id
        //generation of buffer
        glGenBuffers(1, &points_vbo);//1- number of buffers, &points_vbo adress of buffer
        //making the generated buffer current
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        //passing buffer info to video adapter
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
        //type of buffer, size of data, dats, hint for video adapter

        //Color Buffer Object (CBO)
        GLuint colors_vbo = 0;
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);

        //Texture Buffer Object (TBO)
        GLuint textCord_vbo = 0;
        glGenBuffers(1, &textCord_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, textCord_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_STATIC_DRAW);

        //Creation of vertex arrays object (VAO)
        GLuint vao = 0;//vao id
        glGenVertexArrays(1, &vao);//generation of vao
        //making the generated array current
        glBindVertexArray(vao);

        //Activation of ponts coordinate (location=0) in vec3 vertex_position
        glEnableVertexAttribArray(0);//0 - position (location) for points
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        //0-position (location)
        //3 - nubmer of passing vec (vec3)
        //GL_FLOAT type of data, 
        //GL_FALSE - no need to norm
        //0 - offset step (stride) 
        //nullprt - starting offset 

        glEnableVertexAttribArray(1);//1 - position (location) for color
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(2);//1 - position (location) for texture
        glBindBuffer(GL_ARRAY_BUFFER, textCord_vbo);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        pDefaultShaderProgram->use();
        pDefaultShaderProgram->setInt("tex", 0);//0 slot

        //the identity matrix just for example
        glm::mat4 modelMatrix_1 = glm::mat4(1.f);
        //1 moving of matrix (model matrix transform from local space to world space)
        modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(100.f, 50.f, 0.f));
        //2 moving of matrix (matrix transform from world space to view space) == identity matrix (nothing to transform)
        //3 moving of matrix (matrix transform from view space to clip space)

        glm::mat4 modelMatrix_2 = glm::mat4(1.f);
        //1 moving of matrix (model matrix transform from local space to world space)
        modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(590.f, 50.f, 0.f));

        glm::mat4 projectlMatrix = glm::ortho(0.f, static_cast<float>(g_windowSize.x), 0.f, static_cast<float>(g_windowSize.y), -100.f, 100.f);
        
        pDefaultShaderProgram->setMatrix4("projectionMat", projectlMatrix);

        pSpriteShaderProgram->use();
        pSpriteShaderProgram->setInt("tex", 0);//0 set into slot 0
        pSpriteShaderProgram->setMatrix4("projectionMat", projectlMatrix);

        /* Loop until the user closes the window */
       //rendering
        while (!glfwWindowShouldClose(pWindow))//cycle is stopped then the window is closed
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);//frame rendering (clearing the screen)

            //Chosing the shaders programm

            //glUseProgram(shader_programm);
            //shaderProgram.use();
            pDefaultShaderProgram->use();
            //pDefaultShaderProgram->setInt("tex", 0);//0 slot

            glBindVertexArray(vao);//enable current vertex arrays object (VAO)
            tex->bind();
            
            pDefaultShaderProgram->setMatrix4("modelMat", modelMatrix_1);
            glDrawArrays(GL_TRIANGLES, 0, 3);//drawning vao
            //GL_TRIANGLES - type of vertex interpretation
            //0 - starting point in vec3
            //3 - number of vertex (points)

            pDefaultShaderProgram->setMatrix4("modelMat", modelMatrix_2);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            pSprite->render();

            /* Swap front and back buffers */
            glfwSwapBuffers(pWindow);//changing front and back buffer frames

            /* Poll for and process events */
            glfwPollEvents();//press the key, changing pos of cursor, closing the window, changing size of the window
        }
    }
    glfwTerminate();//free the resourses, stop the programm  
}