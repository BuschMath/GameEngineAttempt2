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

void EntityCreator::AddPhysicsComponent(std::shared_ptr<Entity> entity, glm::vec3 acceleration, bool isCollidable, float mass,
                                        glm::vec3 position, glm::quat rotation, glm::vec3 scale, glm::vec3 velocity)
{
    auto physicsComponent = entity->AddComponent<PhysicsComponent>();

    physicsComponent->acceleration.x = acceleration.x;
    physicsComponent->acceleration.y = acceleration.y;
    physicsComponent->acceleration.z = acceleration.z;

    physicsComponent->isCollidable = isCollidable;

    physicsComponent->mass = mass;

    physicsComponent->position.x = position.x;
    physicsComponent->position.y = position.y;
    physicsComponent->position.z = position.z;

    physicsComponent->rotation.w = rotation.w;
    physicsComponent->rotation.x = rotation.x;
    physicsComponent->rotation.y = rotation.y;
    physicsComponent->rotation.z = rotation.z;

    physicsComponent->scale.x = scale.x;
    physicsComponent->scale.y = scale.y;
    physicsComponent->scale.z = scale.z;

    physicsComponent->velocity.x = velocity.x;
    physicsComponent->velocity.y = velocity.y;
    physicsComponent->velocity.z = velocity.z;
}

void EntityCreator::SaveScene(const std::string& fileName) const {
    m_entityFactory->SaveScene(fileName);
}

