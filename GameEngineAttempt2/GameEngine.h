#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Window.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "ComponentFactory.h"
#include "ComponentManager.h"
#include "EntityFactory.h"
#include "EntityCreator.h"

class GameEngine {
public:
    static GameEngine& GetInstance() {
        static GameEngine instance;
        return instance;
    }

    void Initialize();
    void Update(float deltaTime);
    void Render();

    // Add more public methods as necessary...
    void CreateEntities();

private:
    GameEngine(); // Private constructor to enforce singleton pattern
    ~GameEngine(); // Private destructor to prevent accidental deletion

    // Add private member variables as necessary...
    Window* m_window;
    std::shared_ptr<spdlog::logger> m_gameEngineLogger;
    ComponentFactory* m_componentFactory;
    ComponentManager* m_componentManager;
    EntityFactory* m_entityFactory;
    EntityCreator* m_entityCreator;

    // Disable copy and assignment
    GameEngine(const GameEngine&) = delete;
    GameEngine& operator=(const GameEngine&) = delete;
};

#endif // !GAME_ENGINE_H

