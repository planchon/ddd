#include "../include/ddd.hpp"

using namespace std;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

Camera cam = Camera(glm::vec3(0,0,3.0f), glm::vec3(0.0f, 0.0f, 0.0f));

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
    
    // set the callback for the screen resize event
    glfwSetFramebufferSizeCallback(window, screen_resize_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    

    // load de GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    } 

    // openGL parameters
    glEnable(GL_DEPTH_TEST);

    RGBA screenColor = RGBA(0, 0, 150, 255);

    // float vertices[] = {
    //     // positions          // colors           // texture coords
    //      0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
    //      0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    //     -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    //     -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    // };

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Shader triangleShader = Shader("shaders/triangle/vertex.glsl", "shaders/triangle/fragments.glsl");
    // Shader camShader = Shader("shaders/shaderv2/vertex.glsl", "shaders/shaderv2/frag.glsl");
    Shader camShader = Shader("shaders/camera_test/vertex.glsl", "shaders/camera_test/fragments.glsl");
    Texture textureBois = Texture("assets/container.jpg");

    // std::string modelPath("assets/monkey/suzanne.obj");
    std::string modelPath("assets/backpack/backpack.obj");
    Model test = Model(modelPath);

    camShader.use();

    glm::vec3 cubePositions[] = {
        glm::vec3( 5.0f,  5.0f,  5.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3( 0.0f,  5.0f,  2.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    vec3 cube;
    mat4 model;

    while(!glfwWindowShouldClose(window)) {
        processInput(window);
        cam.keyboard_callback(window);

        clearScreen(&screenColor);

        camShader.use();
        // cube = glm::vec3(cos((float) glfwGetTime()), sin((float) glfwGetTime()), -5.0f);
        // model = glm::mat4(1.0f);
        // model = glm::translate(model, cube);

        camShader.set("view", cam.get_view());
        camShader.set("proj", cam.get_proj());
        
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));	

        camShader.set("model", model);
        test.render(camShader);

        // rendu des cubes moches
        glBindVertexArray(VAO);

        for (glm::vec3 vec : cubePositions) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, vec);
            camShader.set("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);

    glfwTerminate();
    std::cout << "ddd closing" << std::endl;
    return 0;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    cam.mouse_callback(xpos, ypos);
    glfwSetCursorPos(window, 400, 300);
}