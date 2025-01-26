#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int g_windowSizeX = 640;
int g_windowSizeY = 480;

//Callback for changing window size
void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height) {
    g_windowSizeX - width;
    g_windowSizeY = height;
    glad_glViewport(0, 0, g_windowSizeX, g_windowSizeY);//coordinates and size of window for rendrering
}

//Callback for pressing the keys
void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode) {
    
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);//close the window        
    }    
}

int main() {    

    /* Initialize the library */
    //check that library was init
    if (!glfwInit())
    {
        std::cout << "glfwInit failed" << std::endl;
        return -1;
    }

    //We want to use GLFW 4..6  and OPEN GL core profile
    glfwWindowHint(GLFW_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "Battle City", nullptr, nullptr);
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
	
	glClearColor(1, 1, 0, 1);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))//cycle is stopped then the window is closed
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);//frame rendering
        
        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);//changing front and back buffer frames
        
        /* Poll for and process events */
        glfwPollEvents();//press the key, changing pos of cursor, closing the window, changing size of the window
    }
    glfwTerminate();//free the resourses, stop the programm  
}