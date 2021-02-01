#include "../include/ddd.hpp"

using namespace std;

int main() {
    cout << "ddd launching" << endl;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // creation de la fenetre
    GLFWwindow* window = glfwCreateWindow(800, 600, "ddd", NULL, NULL);
    if (window == NULL) {
        cout << "failed creating the GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // load de GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    } 

    glViewport(0,0,800,600);

    // set the callback for the screen resize event
    glfwSetFramebufferSizeCallback(window, screen_resize_callback);

    RGBA screenColor = RGBA(155, 250, 200, 255);

    // basic triangle
    float vertices[] = {
        -0.5f, -0.5f, 0,
         0.5f, -0.5f, 0,
            0,  0.5f, 0
    };

    ShaderProgram sp;
    Shader vertex = Shader("../shaders/vertex.glsl", GL_VERTEX_SHADER);
    Shader frag = Shader("../shaders/fragments.glsl", GL_VERTEX_SHADER);
    sp.addShader(vertex);
    sp.addShader(frag);

    sp.link();

    // vertex buffer object
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        clearScreen(&screenColor);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}