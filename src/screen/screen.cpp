#include "../../include/screen.hpp"

// callback called when the user resize the screen
void screen_resize_callback(GLFWwindow* window, int width, int height) {
    glViewport(0,0,width, height);
}

// clear the screen using a RGBA color
void clearScreen(RGBA* color) {
    glClearColor(color->R, color->G, color->B, color->A);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}