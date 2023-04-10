#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include <memory>
#include <unordered_map>
#include "Entity.h"
#include "EntityManager.h"

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

private:
    EntityFactory() {
        m_entityManager = std::make_unique<EntityManager>();
    }

    std::unique_ptr<EntityManager> m_entityManager;
};

#endif // ENTITY_FACTORY_H
