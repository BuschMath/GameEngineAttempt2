#include "EntityCreator.h"

std::shared_ptr<Entity> EntityCreator::CreateEntity(const std::string& name) {
    auto entity = m_entityFactory->CreateEntity(name);
    return entity;
}

void EntityCreator::AddPositionComponent(std::shared_ptr<Entity> entity, float x, float y, float z) {
    auto positionComponent = entity->AddComponent<PositionComponent>();
    glm::vec3 position(x, y, z);
    positionComponent->SetPosition(position);
}

void EntityCreator::AddVelocityComponent(std::shared_ptr<Entity> entity, float x, float y, float z) {
    auto velocityComponent = entity->AddComponent<VelocityComponent>();
    glm::vec3 velocity(x, y, z);
    velocityComponent->SetVelocity(velocity);
}

void EntityCreator::AddHealthComponent(std::shared_ptr<Entity> entity, int health) {
    auto healthComponent = entity->AddComponent<HealthComponent>();
    healthComponent->SetHealth(health);
}

void EntityCreator::AddPhysicsComponent(std::shared_ptr<Entity> entity)
{
    auto physicsComponent = entity->AddComponent<PhysicsComponent>();
}

void EntityCreator::SaveScene(const std::string& fileName) const {
    m_entityFactory->SaveScene(fileName);
}

