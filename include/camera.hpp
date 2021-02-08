#ifndef CAMERA
#define CAMERA

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "math.hpp"

class Camera {
public:
    bool isGUIInteracting = false;

    Camera();
    Camera(vec3 position, vec3 target, unsigned int screen_width, unsigned int screen_height);
    mat4 get_proj();
    mat4 get_view();
    void look_at(vec3 look_at);
    void orbit(vec3 pos, float radius = 10.0f);
    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void keyboard_callback(GLFWwindow* window);
private:
    float MouseSensibility = 0.1f;
    float yaw = -90.0f;
    float pitch = 0.0f;
    float lastMousex = 400;
    float lastMousey = 300;
    float cameraSpeed = 1.0f;
    bool firstMouse = true;

    mat4 proj;
    mat4 view;
    
    vec3 position;
    vec3 target;
    vec3 direction;
    vec3 cameraRight;
    vec3 up;
    vec3 worldUp = vec3(0.0f, 1.0f, 0.0f);

    float fov;
    float screen_width, screen_height;
    float zNear;
    float zFar;

    void updateCamera();
};

#endif