/// \file main.cpp
/// \brief Main file for the project.
/// \version 1.0
/// \date 2024

#include "pch.h"

#include "lib/Math/MathMatrix.h"
#include "lib/Math/Vertex.h"
#include "lib/Clock/lsgClock.h"
#include "Geometries/Triangle.h"
#include "Geometries/Plane.h"

#include "ConfigManager/ConfigManager.h"

#include <cmath>
#include <array>

const unsigned DEFAULT_WINDOW_WIDTH = 800;
const unsigned DEFAULT_WINDOW_HEIGHT = 600;

static void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

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
    GLFWwindow *window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
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

    glEnable(GL_DEPTH_TEST);

    // Setup scene

    float aspect = (float)DEFAULT_WINDOW_WIDTH / (float)DEFAULT_WINDOW_HEIGHT;
    float fov = 45.f / 180.f * F_PI;
    float n = 0.01f;
    float f = 100.f;

    // Camera Transform :
 
    TransformF cameraTransform(
        {0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f, 0.f});

    // plane transform
    TransformF planeTransform(
        {0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f});

    PlaneF *plane1 = new PlaneF(planeTransform, 10);

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
    bool show_demo_window = false;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Start clock
    slgClock clock;
    double dTime = clock.restart();

    auto Config = UConfigManager::GetInstance();

    while (!glfwWindowShouldClose(window))
    {
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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Config->DisplayWidgets();

        // IMPORTANT
        // Confi->DisplayWidgets();

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // update scene
        // cameraPitch += dTime;
        // cameraYaw += dTime;
        cameraTransform = TransformF(
            {Config->CameraLocationX, Config->CameraLocationY, Config->CameraLocationZ},
            {Config->CameraRotationPitch, Config->CameraRotationRoll, Config->CameraRotationYaw},
            {Config->CameraScaleX, Config->CameraScaleY, Config->CameraScaleZ});

        // cameraTransform.rotation = QuatF({F_PI * 0.25f * sin(cameraPitch), cameraRoll, cameraYaw * F_PI * 2.f});

        Mat4F P = Mat4F::MakeProjection(aspect, fov, n, f);
        Mat4F V(cameraTransform);

        planeTransform = TransformF(
            {Config->PlaneLocationX, Config->PlaneLocationY, Config->PlaneLocationZ},
            {Config->PlaneRotationPitch, Config->PlaneRotationRoll, Config->PlaneRotationYaw},
            {Config->PlaneScaleX, Config->PlaneScaleY, Config->PlaneScaleZ});
        // {Config->CameraLocationX, Config->CameraLocationY, Config->CameraLocationZ}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f});

        plane1->transform = planeTransform;
        plane1->size = Config->PlaneSize;

        //  Clear window
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        // Rendering
        plane1->render(V, P);

        //    std::cout << Config->CameraLocationX << "\n";

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        aspect = (float)display_w / (float)display_h;
        glViewport(0, 0, display_w, display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    delete plane1;

    return 0;
}