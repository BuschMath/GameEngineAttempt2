#include "GameEngine.h"
#include <iostream>
#include <string>

int wWidth = 800;
int wHeight = 600;
const char* wName = "My Game";

GameEngine::GameEngine()
{
    m_window = nullptr;
    
    try
    {
        m_gameEngineLogger = spdlog::basic_logger_mt("gameEngine", "logs/gameEngineLog.dat");
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cout << "Log initialization failed: " << ex.what() << std::endl;
    }
    m_gameEngineLogger->set_level(spdlog::level::info);

    m_componentFactory = &ComponentFactory::GetInstance();
    m_componentManager = &ComponentManager::GetInstance();
    m_entityFactory = &EntityFactory::GetInstance();

    m_gameEngineLogger->info("GameEngine constructor complete.\n.");
}

GameEngine::~GameEngine()
{
    glfwTerminate(); m_gameEngineLogger->info("GameEngine destructor complete.\n");
}

void GameEngine::Initialize() {
    // Initialize GLFW
    if (!glfwInit()) {
        // Print error message to console
        std::cerr << "Failed to initialize GLFW\n";
        // Print error to log
        m_gameEngineLogger->error("Failed to initialize GLFW.\n");
        return;
    }
    m_gameEngineLogger->info("GLFW initialized.\n");

    // Create an OpenGL window and context
    m_window = new Window(wWidth, wHeight, wName);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        // Print error message to console
        std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(err) << "\n";
        m_gameEngineLogger->error("GLEW failed to initialize.\n");
        return;
    }
    m_gameEngineLogger->info("GLEW initialized.\n");

    // Initialize input handling
    // Initialize audio system
    // ...
    m_gameEngineLogger->info("GameEngine initialization complete.\n");
}

void GameEngine::Update(float deltaTime) {
    // Handle user input
    // Update game state based on time and input
    // ...
}

void GameEngine::Render() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render the current game state
    // ...

    // Swap the front and back buffers
    glfwSwapBuffers(m_window->GetGLFWwindow());
}
