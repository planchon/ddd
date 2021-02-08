#include "../../include/camera.hpp"

Camera::Camera() {
    this->target    = vec3(0.0f, 0.0f, -1.0f);
    this->position  = vec3(0.0f, 0.0f, 0.0f);
    this->up        = vec3(0.0f, 1.0f, 0.0f);

    this->fov           = 45.0f;
    this->screen_height = 600.0f;
    this->screen_width  = 800.0f;
    this->zNear         = 0.1f;
    this->zFar         = 10000.0f;

    this->proj = glm::perspective(glm::radians(this->fov), (float) this->screen_width / (float) this->screen_height, this->zNear, this->zFar);

    this->updateCamera();
}

Camera::Camera(glm::vec3 position, glm::vec3 target, unsigned int screen_width, unsigned int screen_height) : Camera::Camera() {
    this->position = position;
    this->target   = target;
    this->screen_height = screen_height;
    this->screen_width = screen_width;

    this->updateCamera();    
}

// make the cam orbit around pos
void Camera::orbit(glm::vec3 pos, float radius) {
    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;

    this->view = glm::lookAt(this->position + glm::vec3(camX, 0.0, camZ), pos, glm::vec3(0.0f, 1.0f, 0.0f));  
}

glm::mat4 Camera::get_view() {
    return lookAt(this->position, this->position + this->target, this->up);
}

glm::mat4 Camera::get_proj() {
    return this->proj;
}

void Camera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
    xoffset *= this->MouseSensibility;
    yoffset *= this->MouseSensibility;

    this->yaw   += xoffset;
    this->pitch += yoffset;

    if (constrainPitch) {
        if (this->pitch > 89.0f)
            this->pitch = 89.0f;
        if (this->pitch < -89.0f)
            this->pitch = -89.0f;
    }

    this->updateCamera();
}

void Camera::updateCamera() {
    vec3 front;
    front.x = cos(radians(this->yaw)) * cos(radians(this->pitch));
    front.y = sin(radians(this->pitch));
    front.z = sin(radians(this->yaw)) * cos(radians(this->pitch));
    this->target = normalize(front);

    this->cameraRight = normalize(cross(this->target, this->worldUp));
    this->up = normalize(cross(this->cameraRight, this->target));
}

void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (!this->isGUIInteracting) {
        if (this->firstMouse) {
            this->lastMousex = xpos;
            this->lastMousey = ypos;
            this->firstMouse = false;
        }

        float xoffset = xpos - this->lastMousex;
        float yoffset = this->lastMousey - ypos;

        this->lastMousex = 400;
        this->lastMousey = 300;

        this->processMouseMovement(xoffset, yoffset);

        glfwSetCursorPos(window, 400, 300);
    }
}

void Camera::keyboard_callback(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        this->position += this->target * this->cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        this->position -= this->target * this->cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        this->position -= this->cameraRight * this->cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        this->position += this->cameraRight * this->cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        this->position += this->worldUp * this->cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        this->position -= this->worldUp * this->cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        this->isGUIInteracting = !this->isGUIInteracting;
    }
}