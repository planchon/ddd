#include "../../include/camera.hpp"

Camera::Camera() {
    this->target    = glm::vec3(1.0f, 0.0f, 0.0f);
    this->position  = glm::vec3(0, 0.0f, 0);
    this->direction = glm::vec3(1.0f, 0.0f, 1.0f);

    this->direction   = glm::normalize(this->position - this->target);
    this->cameraRight = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), this->direction));
    this->up          = glm::cross(this->direction, this->cameraRight);

    this->fov           = 45.0f;
    this->screen_height = 600.0f;
    this->screen_width  = 800.0f;
    this->zNear         = 0.1f;
    this->zFar         = 100.0f;

    this->proj = glm::perspective(glm::radians(this->fov), (float) this->screen_width / (float) this->screen_height, this->zNear, this->zFar);
    this->view = glm::mat4(1.0f);
    this->view = glm::translate(this->view, this->position);
}

void Camera::look_at(glm::vec3 look_at) {
    this->view = glm::lookAt(this->position, look_at, this->up);  
}

// make the cam orbit around pos
void Camera::orbit(glm::vec3 pos, float radius) {
    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;

    this->view = glm::lookAt(this->position + glm::vec3(camX, 0.0, camZ), pos, glm::vec3(0.0f, 1.0f, 0.0f));  
}

Camera::Camera(glm::vec3 position, glm::vec3 target) : Camera::Camera() {
    this->position = position;
    this->target   = target;

    this->view = glm::translate(this->view, this->position);
    this->look_at(target);
    
}

glm::mat4 Camera::get_view() {
    return this->view;
}

glm::mat4 Camera::get_proj() {
    return this->proj;
}