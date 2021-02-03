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
    Camera();
    Camera(glm::vec3 position, glm::vec3 target);
    glm::mat4 get_proj();
    glm::mat4 get_view();
    void look_at(glm::vec3 look_at);
    void orbit(glm::vec3 pos, float radius = 10.0f);
private:
    glm::mat4 proj;
    glm::mat4 view;

    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 direction;
    glm::vec3 cameraRight;
    glm::vec3 up;

    float fov;
    float screen_width, screen_height;
    float zNear;
    float zFar;
};

#endif