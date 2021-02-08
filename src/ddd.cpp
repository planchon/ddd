#include "../include/ddd.hpp"

using namespace std;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
static void ShowExampleAppSimpleOverlay(bool* p_open);

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

Camera cam = Camera(glm::vec3(0,0,3.0f), glm::vec3(0.0f, 0.0f, 0.0f), SCR_WIDTH, SCR_HEIGHT);

int main() {
    cout << "ddd launching" << endl;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // creation de la fenetre
    GLFWwindow* window = glfwCreateWindow(1280, 720, "ddd", NULL, NULL);

    if (window == NULL) {
        cout << "failed creating the GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // vsync ?

    // load de GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    } 

    // openGL parameters
    glEnable(GL_DEPTH_TEST);

    // set the callback for the screen resize event
    glfwSetFramebufferSizeCallback(window, screen_resize_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    //imgui
    ImGui::CreateContext();
    // ImGuiIO &io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    RGBA screenColor = RGBA(0, 0, 150, 255);

    Shader camShader = Shader("shaders/camera_test/vertex.glsl", "shaders/camera_test/fragments.glsl");

    Model house = Model(std::string("assets/d2/de_dust2.obj"));

    bool overlay_open = true;

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // process des inputs
        processInput(window);
        cam.keyboard_callback(window);

        clearScreen(&screenColor);

        camShader.use();

        camShader.set("view", cam.get_view());
        camShader.set("proj", cam.get_proj());
        
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1, 0, 0));

        camShader.set("model", model);
        house.render(camShader);

        if (cam.isGUIInteracting) {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ShowExampleAppSimpleOverlay(&overlay_open);

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);

    glfwTerminate();
    std::cout << "ddd closing" << std::endl;
    return 0;
}

static void ShowExampleAppSimpleOverlay(bool* p_open)
{
    const float DISTANCE = 10.0f;
    static int corner = 0;
    ImGuiIO& io = ImGui::GetIO();
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
    window_flags |= ImGuiWindowFlags_NoMove;
        ImVec2 window_pos = ImVec2((corner & 1) ? io.DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? io.DisplaySize.y - DISTANCE : DISTANCE);
        ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
        ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
    ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
    if (ImGui::Begin("ddd - statistiques", p_open, window_flags))
    {
        ImGui::Text("ddd - statistiques");
        ImGui::Separator();
        ImGui::Text("fps: 1000, ticks: 60");
    }
    ImGui::End();
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    cam.mouse_callback(window, xpos, ypos);
}