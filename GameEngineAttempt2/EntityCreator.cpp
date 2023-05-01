#include "EntityCreator.h"

std::shared_ptr<Entity> EntityCreator::CreateEntity(const std::string& name) {
    auto entity = m_entityFactory->CreateEntity(name);
    return entity;
}

void EntityCreator::AddPositionComponent(std::shared_ptr<Entity> entity, float x, float y, float z) {
    auto positionComponent = entity->AddComponent<PositionComponent>();
    positionComponent->SetParent(entity);
    glm::vec3 position(x, y, z);
    positionComponent->SetPosition(position);
}

void EntityCreator::AddVelocityComponent(std::shared_ptr<Entity> entity, float x, float y, float z) {
    auto velocityComponent = entity->AddComponent<VelocityComponent>();
    velocityComponent->SetParent(entity);
    glm::vec3 velocity(x, y, z);
    velocityComponent->SetVelocity(velocity);
}

void EntityCreator::AddHealthComponent(std::shared_ptr<Entity> entity, int health) {
    auto healthComponent = entity->AddComponent<HealthComponent>();
    healthComponent->SetParent(entity);
    healthComponent->SetHealth(health);
}

void EntityCreator::AddPhysicsComponent(std::shared_ptr<Entity> entity, glm::vec3 acceleration, bool isCollidable, float mass,
                                        glm::vec3 position, glm::quat rotation, glm::vec3 scale, glm::vec3 velocity)
{
    auto physicsComponent = entity->AddComponent<PhysicsComponent>();
    physicsComponent->SetParent(entity);

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

void EntityCreator::AddRenderComponent(std::shared_ptr<Entity> entity, const std::string& filePath) {
    // Load mesh data
    MeshLoader meshLoader;
    if (!meshLoader.LoadMesh(filePath)) {
        std::cout << "Failed to load mesh: " << filePath << "\n";
        return;
    }

    // Create VAO, VBO, and EBO
    unsigned int vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, meshLoader.GetVertices().size() * sizeof(Vertex), &meshLoader.GetVertices()[0], GL_STATIC_DRAW);
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshLoader.GetIndices().size() * sizeof(unsigned int), &meshLoader.GetIndices()[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(2);

    // Create render component
    auto renderComponent = std::make_shared<RenderComponent>();
    renderComponent->SetMeshDataFilePath(filePath);
    renderComponent->SetParent(entity);
    renderComponent->SetMesh(vao, vbo, ebo, meshLoader.GetIndices().size());

    // Add render component to entity
    entity->AddComponent<RenderComponent>();
}
