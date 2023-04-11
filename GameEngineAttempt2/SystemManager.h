#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <vector>
#include "SystemFactory.h"

// SystemManager class
class SystemManager {
public:
    ~SystemManager() {
        // Shutdown all systems
        for (auto& system : m_Systems) {
            system->Shutdown();
            delete system;
        }
    }

    template<typename T>
    void AddSystem() {
        T* system = SystemFactory::CreateSystem<T>();
        m_Systems.push_back(system);
        system->Initialize();
    }

    void Update(float deltaTime) {
        // Update all systems
        for (auto& system : m_Systems) {
            system->Update(deltaTime);
        }
    }

private:
    std::vector<System*> m_Systems; // Vector to store all systems
};

#endif // !SYSTEM_MANAGER_H

