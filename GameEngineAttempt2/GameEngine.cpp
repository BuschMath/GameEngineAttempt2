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

    m_entityCreator = new EntityCreator();

    m_renderSystem = new RenderSystem();

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

    m_entityFactory->LoadScene(SCENE_DATA_FILE);

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
    m_renderSystem->Render();

    // Swap the front and back buffers
    glfwSwapBuffers(m_window->GetGLFWwindow());
}

void GameEngine::CreateEntities()
{
    std::cout << "Welcome to EntityCreator CLI!\n";
    std::string command;
    std::string name;
    std::shared_ptr<Entity> entity;

    while (true) {
        std::cout << "\nEnter a command ('create', 'physics, 'health', 'save' or 'exit'): ";
        std::getline(std::cin, command);

        if (command == "create") {
            std::cout << "Enter entity name: ";
            std::cin >> name;
            entity = m_entityCreator->CreateEntity(name);
            std::cout << "Entity created!\n";
            std::getline(std::cin, name);
        }
        else if (command == "physics") {
            m_entityCreator->AddPhysicsComponent(entity);
            std::cout << "Physics component added!\n";
            std::getline(std::cin, name);
        }
        else if (command == "health") {
            std::cout << "Enter the health value for the health component: ";
            float health;
            std::cin >> health;
            m_entityCreator->AddHealthComponent(entity, health);
            std::cout << "Health component added!\n";
            std::getline(std::cin, name);
        }
        else if (command == "save") {
            std::cout << "Enter the file name to save to: ";
            std::string fileName;
            std::getline(std::cin >> std::ws, fileName);
            m_entityCreator->SaveScene(fileName);
            std::cout << "Data saved to file " << fileName << "!\n";
            std::getline(std::cin, name);
        }
        else if (command == "exit")
            return;
        else {
            std::cout << "Invalid command, please try again.\n";
        }
    }
}
