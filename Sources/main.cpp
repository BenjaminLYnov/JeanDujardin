/// \file main.cpp
/// \brief Main file for the project.
/// \version 1.0
/// \date 2024

#include "pch.h"

#include "lib/Math/MathMatrix.h"
#include "lib/Math/Vertex.h"
#include "lib/Clock/lsgClock.h"
#include "Geometries/Triangle.h"

#include <cmath>
#include <array>

#include "Widget/WidgetManager.h"
#include "Widget/Partials/FloatSlider.h"
#include "Widget/Partials/BooleanCheckbox.h"

#include <memory> // Pour std::unique_ptr

const unsigned DEFAULT_WINDOW_WIDTH = 800;
const unsigned DEFAULT_WINDOW_HEIGHT = 600;

static void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

/// \fn int main(int argc, char** argv)
///
int main(int argc, char **argv)
{
    // Setup OPTICK
    // OPTICK_FRAME("MainThread");

    // Setup GLFW
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    // Create window with graphics context
    GLFWwindow *window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup GLEW
    glewExperimental = GL_TRUE;
    if (glewInit())
    {
        throw std::runtime_error("Glew init error");
    }

    // Setup scene

    VertexF p0{{-0.8f, -0.9f, 0.f}, {1.f, 0.f, 0.f, 1.f}};
    VertexF p1{{0.9f, -0.9f, 0.f}, {0.f, 1.f, 0.f, 1.f}};
    VertexF p2{{0.9f, 0.8f, 0.f}, {0.f, 0.f, 1.f, 1.f}};

    TriangleF t0{p0, p1, p2};

    p0 = {{-0.9f, -0.8f, 0.f}, {1.f, 0.f, 1.f, 1.f}};
    p1 = {{-0.9f, 0.9f, 0.f}, {1.f, 1.f, 0.f, 1.f}};
    p2 = {{0.8f, 0.9f, 0.f}, {0.f, 1.f, 1.f, 1.f}};

    TriangleF t1{p0, p1, p2};

    float aspect = (float)DEFAULT_WINDOW_WIDTH / (float)DEFAULT_WINDOW_HEIGHT;
    float fov = 45.f / 180.f * F_PI;
    float n = 0.01f;
    float f = 100.f;

    // Camera Transform :
    float cameraPitch = 0.f;
    float cameraRoll = 0.f;
    float cameraYaw = 0.f;
    TransformF cameraPosition(
        {0.f, 0.f, -10.f}, {cameraPitch, cameraRoll, cameraYaw}, {1.f, 1.f, 1.f});

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Start clock
    slgClock clock;
    double dTime = clock.restart();

    // Init Widget manager
    std::unique_ptr<UWidgetManager> WidgetManager = std::make_unique<UWidgetManager>();
    
    float NbVertice = 0;
    // float AnotherThing = new float(0);
    float AnotherThing = 0;
    float Zoom = 0;
    // bool* bEnableShadow = new bool(true);
    bool bEnableShadow = true;

    WidgetManager->AddWidget<UFloatSlider>("Nombre de vertice", &NbVertice, 0.0f, 100.0f);
    WidgetManager->AddWidget<UFloatSlider>("Autre chose", &AnotherThing, 0.0f, 100.0f);
    WidgetManager->AddWidget<UFloatSlider>("Zoom", &Zoom, -100.0f, 100.0f);
    WidgetManager->AddWidget<UBooleanCheckbox>("Enable Shadows", &bEnableShadow);

    // Game Loop
    while (!glfwWindowShouldClose(window))
    {
        std::cout << Zoom << "\n";
        dTime = clock.restart();

        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        // IMPORTANT
        WidgetManager->DisplayWidgets();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        aspect = (float)display_w / (float)display_h;
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}