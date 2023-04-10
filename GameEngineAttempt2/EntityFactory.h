#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

class SceneFileManager;

#include <memory>
#include <unordered_map>
#include "Entity.h"
#include "EntityManager.h"
#include "SceneFileManager.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

class EntityFactory {
public:
    static EntityFactory& GetInstance() {
        static EntityFactory instance;
        return instance;
    }

    std::shared_ptr<Entity> CreateEntity(const std::string& name = "") {
        auto entity = std::make_shared<Entity>(name);
        m_entityManager->AddEntity(entity);

        return entity;
    }

    const std::vector<std::shared_ptr<Entity>> GetEntities() const { return m_entityManager->GetEntities(); }

    template<typename T, typename... Args>
    std::shared_ptr<T> AddComponent(std::shared_ptr<Entity> entity, Args&&... args) {
        return entity->AddComponent<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    std::vector<std::shared_ptr<T>> GetComponents(std::shared_ptr<Entity> entity) const {
        return entity->GetComponents<T>();
    }

    void SaveScene(const std::string& fileName) const;
    bool LoadScene(const std::string& fileName);

private:
    EntityFactory() {
        m_entityManager = std::make_unique<EntityManager>();
        try
        {
            m_entityFactoryLogger = spdlog::basic_logger_mt("entityManager", "logs/entityFactoryLog.dat");
        }
        catch (const spdlog::spdlog_ex& ex)
        {
            std::cout << "Log initialization failed: " << ex.what() << std::endl;
        }
        m_entityFactoryLogger->set_level(spdlog::level::info);
        m_entityFactoryLogger->info("EntityFactory constructor complete.\n");
    }

    std::unique_ptr<EntityManager> m_entityManager;
    std::shared_ptr<spdlog::logger> m_entityFactoryLogger;
};

#endif // ENTITY_FACTORY_H
