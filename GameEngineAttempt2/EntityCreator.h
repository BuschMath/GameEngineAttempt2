#ifndef ENTITY_CREATOR_H
#define ENTITY_CREATOR_H

#include "EntityFactory.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "HealthComponent.h"
#include "PhysicsComponent.h"

class EntityCreator {
public:
    EntityCreator() { m_entityFactory = &EntityFactory::GetInstance(); }

    std::shared_ptr<Entity> CreateEntity(const std::string& name = "");

    void AddPositionComponent(std::shared_ptr<Entity> entity, float x, float y, float z);
    void AddVelocityComponent(std::shared_ptr<Entity> entity, float x, float y, float z);
    void AddHealthComponent(std::shared_ptr<Entity> entity, int health);
    void AddPhysicsComponent(std::shared_ptr<Entity> entity);

    void SaveScene(const std::string& fileName) const;

private:
    EntityFactory* m_entityFactory;
};

#endif // !ENTITY_CREATOR_H
