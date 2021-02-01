#include "../../include/inputs.hpp"

void processInput(GLFWwindow* window) {
    // si on appuie sur echap la fenetre se ferme
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
} 