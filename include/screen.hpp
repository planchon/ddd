#ifndef SCREEN
#define SCREEN

#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "color.hpp"

void screen_resize_callback(GLFWwindow* window, int width, int height);
void clearScreen(RGBA* color);

#endif