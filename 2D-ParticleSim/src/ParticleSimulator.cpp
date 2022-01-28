#include "ParticleSimulator.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "ResourceManager.h"
#include "CellMatrix.h"

// elements
#include "Sand.h" 
#include "Water.h"

// game video settings
const unsigned int SCREEN_WIDTH = 1280;
const unsigned int SCREEN_HEIGHT = 720;

// inputs
bool ParticleSimulator::Keys[1024];
glm::vec2 ParticleSimulator::MousePos;
bool ParticleSimulator::MouseButtons[7];

CellMatrix* cellMatrix;

void framebuffer_size_callback(GLFWwindow* window, int height, int width);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void cursor_positon_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void ParticleSimulator::Init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, false);

    //GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout", glfwGetPrimaryMonitor(), nullptr);
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "2D Particle Simulator", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, cursor_positon_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glfwSwapInterval(1);

    // OpenGL configuration
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    //ImGui Configuration;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    //--------------------Load Resources--------------------
    // Load Shaders
    ResourceManager::LoadShader("shaders/spriteVS.shader", "shaders/spriteFS.shader", nullptr, "spriteShader");

    // configure shaders
    glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("spriteShader").Use().SetInteger("image", 0);
    ResourceManager::GetShader("spriteShader").SetMatrix4("projection", proj);

    // Load Renderer
    spriteRenderer = new SpriteRenderer(ResourceManager::GetShader("spriteShader"), SCREEN_WIDTH, SCREEN_HEIGHT);

    // Load Textures
    ResourceManager::LoadTexture("src/textures/sand.png", true, "sandTexture");
    ResourceManager::LoadTexture("src/textures/water.png", true, "waterTexture");

    // Load Matrix
    glm::vec2 cellDim(1000, 1000);

    // Configure Matrix
    cellMatrix = new CellMatrix(spriteRenderer, cellDim.x, cellDim.y);
}

void ParticleSimulator::HandleInput()
{
    if (!uiSelected)
    {
		if (MouseButtons[GLFW_MOUSE_BUTTON_LEFT])
		{
			cellMatrix->AddElement(new Sand(glm::vec2((int)(MousePos.x / cellMatrix->cellSize), -(int)(MousePos.y / cellMatrix->cellSize)), 
                                            ResourceManager::GetTexture("sandTexture")));
		}
		if (MouseButtons[GLFW_MOUSE_BUTTON_RIGHT])
		{
			cellMatrix->AddElement(new Water(glm::vec2((int)(MousePos.x / cellMatrix->cellSize), -(int)(MousePos.y / cellMatrix->cellSize)), 
                                            ResourceManager::GetTexture("waterTexture")));
		}
    }
}

void ParticleSimulator::Update()
{
    GetFPS();
    cellMatrix->UpdateElements();
}

void ParticleSimulator::Render()
{
	glfwPollEvents();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Imgui frames
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

	// calculate delta time
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

    cellMatrix->DrawElements();

    // Imgui Ui
    ImGui::Begin("Select Element Type");
    ImGui::Text("Each Element has its own properties");
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);

}

void ParticleSimulator::Clean()
{
    // ImGui Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    cellMatrix->CleanElements();
    delete cellMatrix;

    delete spriteRenderer;
    glfwTerminate();
}

float ParticleSimulator::GetFPS()
{
	timeDiff = currentFrame - lastTime;
	frames++;
	if (timeDiff >= 1.0)
	{
	    std::cout << frames <<  "fps" << std::endl;
        if (frames <= 30)
        {
            std::cout << "PERFORMANCE DROP AT : " << cellMatrix->getNumberOfElements() << std::endl;
        }
	    frames = 0;
	    lastTime = currentFrame;
	}
    return frames;
}

// callbacks
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            ParticleSimulator::Keys[key] = true;
        else if (action == GLFW_RELEASE)
            ParticleSimulator::Keys[key] = false;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void cursor_positon_callback(GLFWwindow* window, double xpos, double ypos)
{
    ParticleSimulator::MousePos = glm::vec2(xpos, ypos);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button >= 0 && button <= 7)
    {
        if (action == GLFW_PRESS)
        {
            ParticleSimulator::MouseButtons[button] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            ParticleSimulator::MouseButtons[button] = false;
        }
    }
}

