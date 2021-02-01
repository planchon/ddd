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

    RGBA screenColor = RGBA(0, 0, 0, 255);

    // basic triangle
    float vertices[] = {
        -0.5f, -0.5f, 0,
         0.5f, -0.5f, 0,
            0,  0.5f, 0
    };

    ShaderProgram sp;
    Shader vertex = Shader("shaders/vertex.glsl", GL_VERTEX_SHADER);
    Shader frag = Shader("shaders/fragments.glsl", GL_FRAGMENT_SHADER);

    sp.addShader(vertex);
    sp.addShader(frag);

    sp.link();

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while(!glfwWindowShouldClose(window)) {
        processInput(window);
        
        clearScreen(&screenColor);

        glUseProgram(sp.get_id());
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(sp.get_id());

    glfwTerminate();
    return 0;
}