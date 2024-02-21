#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Camera
{
public:
    // the program ID
    unsigned int ID;
    glm::vec3 camPos;
    glm::vec3 camFront;
    glm::vec3 camUp;
    glm::mat4 view;
    glm::mat4 proj;
    float yaw;
    float pitch;
    float lastX, lastY, fov;
    bool firstMouse;
    // constructor reads and builds the shader
    Camera() {
        camPos   = glm::vec3(0.0f, 0.0f,  3.0f);
        camFront = glm::vec3(0.0f, 0.0f, -1.0f);
        camUp    = glm::vec3(0.0f, 1.0f,  0.0f);
        view     = glm::lookAt(camPos, camPos + camFront, camUp);
        proj     = glm::perspective(glm::radians(fov), (float)800/(float)600, 0.1f, 100.0f);

        yaw   = -90.0f;
        pitch = 0.0f;

        lastX = 400;
        lastY = 300;

        fov = 45.0f;

        firstMouse = true;
    };

    void update() {
        view     = glm::lookAt(camPos, camPos + camFront, camUp);
        proj     = glm::perspective(glm::radians(fov), (float)800/(float)600, 0.1f, 100.0f);
    }
    void mouse_callback(GLFWwindow* window, double xpos, double ypos)
    {
        if (firstMouse) // initially set to true
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
        lastX = xpos;
        lastY = ypos;

        const float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw   += xoffset;
        pitch += yoffset;

        if(pitch > 89.0f)
            pitch =  89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;
        
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        camFront = glm::normalize(direction);
        update();
    }

    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        fov -= (float)yoffset;
        if (fov < 1.0f)
            fov = 1.0f;
        if (fov > 45.0f)
            fov = 45.0f; 
        update();
        
    }
};
  
#endif