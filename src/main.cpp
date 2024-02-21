#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

Camera cam;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

void processInput(GLFWwindow *window)
{
    const float camSpeed = 2.5f * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam.camPos += camSpeed * cam.camFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam.camPos -= camSpeed * cam.camFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam.camPos -= glm::normalize(glm::cross(cam.camFront, cam.camUp)) * camSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam.camPos += glm::normalize(glm::cross(cam.camFront, cam.camUp)) * camSpeed;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    cam.mouse_callback(window, xpos, ypos);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    cam.scroll_callback(window, xoffset, yoffset);
}

int main() {
    
    //initialize glfw, set gl version 3.3
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    

    GLFWwindow* window = glfwCreateWindow(800, 600, "tony window", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "failed to create glfw window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    //pass GLAD the function to load the address of the OpenGL function pointers
    
    //make the window the main context on the current thread
    glfwMakeContextCurrent(window);
    glewInit();

    //tell openGL the size of rendering window
    glViewport(0,0,800,600);

    //adjust viewport on resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    /*
    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };
    */

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 2,
        0, 2, 3    // second triangle
    };
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    Shader sh("assets/shader.vs", "assets/shader.fs");
    sh.use();

    Texture tex;
    tex.addTex("assets/container.jpg", false);
    tex.addTex("assets/awesomeface.png", true);

    sh.setInt("texture1", 0);
    sh.setInt("texture2", 1);

    tex.actTex(0);
    tex.actTex(1);
    
    glEnable(GL_DEPTH_TEST); 
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    //glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 3.0f);  
    //glm::vec3 camTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    //glm::vec3 camDirection = glm::normalize(camPos - camTarget);

    //glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    //glm::vec3 camRight = glm::normalize(glm::cross(up, camDirection));
    //glm::vec3 camUp = glm::normalize(glm::cross(camRight, camDirection));

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(0.0, 0.0, 0.0));
    trans = glm::rotate(trans, glm::radians(55.0f), glm::vec3(-1.0, -1.0, 0.0));

    

    unsigned int transformLoc = glGetUniformLocation(sh.ID, "transform");
    unsigned int viewLoc = glGetUniformLocation(sh.ID, "view");
    unsigned int projLoc = glGetUniformLocation(sh.ID, "projection");

    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(cam.view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(cam.proj));
    
    unsigned int VBO, VAO, EBO;

    glCreateVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glCreateBuffers(1, &VBO);
    
    glNamedBufferStorage(VBO, sizeof(vertices), vertices, GL_DYNAMIC_STORAGE_BIT);

    glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(vertices)/36);

    glEnableVertexArrayAttrib(VAO, 0);
    glEnableVertexArrayAttrib(VAO, 1);
    //glEnableVertexArrayAttrib(VAO, 2);

    glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribFormat(VAO, 1, 2, GL_FLOAT, GL_FALSE, 3*sizeof(float));

    //glVertexArrayAttribFormat(VAO, 1, 0, GL_FLOAT, GL_FALSE, 3*sizeof(float));
    //glVertexArrayAttribFormat(VAO, 2, 2, GL_FLOAT, GL_FALSE, 3*sizeof(float));

    glVertexArrayAttribBinding(VAO, 0, 0);
    glVertexArrayAttribBinding(VAO, 1, 0);  
    //glVertexArrayAttribBinding(VAO, 2, 0);  
    while(!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;  
        processInput(window);
        glfwPollEvents();        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glBindVertexArray(VAO);

        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(cam.view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(cam.proj));
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        for (int i = 0; i < 10; i++) {
            trans = glm::mat4(1.0f);
            trans = glm::translate(trans, cubePositions[i]);
            float angle = 20.0f * i; 
            trans = glm::rotate(trans, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            transformLoc = glGetUniformLocation(sh.ID, "transform");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glBindVertexArray(0);
        
        glfwSwapBuffers(window);
    } 

    glfwTerminate();
    return 0;
}