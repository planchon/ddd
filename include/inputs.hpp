#ifndef INPUTS
#define INPUTS

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "camera.hpp"

void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos, Camera cam);

#endif