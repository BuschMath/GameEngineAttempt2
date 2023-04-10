#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <memory>
#include "Entity.h"

class EntityManager {
public:
    void AddEntity(std::shared_ptr<Entity> entity) {
        m_entities.push_back(entity);
    }

    void RemoveEntity(std::shared_ptr<Entity> entity) {
        // Remove the entity from the list
        m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());

        // Remove all components from the entity
        entity->RemoveComponents();
    }

    std::vector<std::shared_ptr<Entity>> GetEntities() const {
        return m_entities;
    }

private:
    std::vector<std::shared_ptr<Entity>> m_entities;
};

#endif // !ENTITY_MANAGER_H
