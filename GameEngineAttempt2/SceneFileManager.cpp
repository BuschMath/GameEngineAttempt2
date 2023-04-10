#include "SceneFileManager.h"

bool SceneFileManager::LoadScene(const std::string& filePath, EntityFactory& entityFactory) {
    std::ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
        std::cerr << "Failed to open scene file: " << filePath << "\n";
        return false;
    }

    nlohmann::json jsonData;
    fileStream >> jsonData;

    if (!jsonData.is_object() || !jsonData.contains("entities")) {
        std::cerr << "Invalid scene file format: " << filePath << "\n";
        return false;
    }

    for (const auto& entityData : jsonData["entities"]) {
        auto entity = entityFactory.CreateEntity(entityData["name"]);

        if (entityData.count("position") > 0) {
            auto position = entity->AddComponent<PositionComponent>();
            glm::vec3 tempPos;
            tempPos.x = entityData["position"]["x"];
            tempPos.y = entityData["position"]["y"];
            tempPos.z = entityData["position"]["z"];
            position->SetPosition(tempPos);
        }

        if (entityData.count("velocity") > 0) {
            auto velocity = entity->AddComponent<VelocityComponent>();
            glm::vec3 tempVel;
            tempVel.x = entityData["velocity"]["x"];
            tempVel.y = entityData["velocity"]["y"];
            tempVel.z = entityData["velocity"]["z"];
            velocity->SetVelocity(tempVel);
        }

        if (entityData.count("health") > 0) {
            auto health = entity->AddComponent<HealthComponent>();
            health->SetHealth(entityData["health"]["value"]);
        }

        // add more components as needed
    }

    return true;
}

bool SceneFileManager::SaveScene(const std::string& filePath, const EntityFactory& entityFactory) {
    nlohmann::json jsonData;

    for (const auto& entity : entityFactory.GetEntities()) {
        nlohmann::json entityData;
        entityData["name"] = entity->GetName();

        if (entity->HasComponent<PositionComponent>()) {
            const auto positionComp = entity->GetComponents<PositionComponent>();
            nlohmann::json positionData;
            glm::vec3 position = positionComp[0]->GetPosition();
            positionData["x"] = position.x;
            positionData["y"] = position.y;
            positionData["z"] = position.z;
            entityData["position"] = positionData;
        }

        if (entity->HasComponent<VelocityComponent>()) {
            const auto velocityComp = entity->GetComponents<VelocityComponent>();
            nlohmann::json velocityData;
            glm::vec3 velocity = velocityComp[0]->GetVelocity();
            velocityData["x"] = velocity.x;
            velocityData["y"] = velocity.y;
            velocityData["z"] = velocity.z;
            entityData["velocity"] = velocityData;
        }

        if (entity->HasComponent<HealthComponent>()) {
            const auto healthComp = entity->GetComponents<HealthComponent>();
            nlohmann::json healthData;
            int health = healthComp[0]->GetHealth();
            healthData["value"] = health;
            entityData["health"] = healthData;
        }

        // add more components as needed

        jsonData["entities"].push_back(entityData);
    }

    std::ofstream fileStream(filePath);
    if (!fileStream.is_open()) {
        std::cerr << "Failed to create scene file: " << filePath << "\n";
        return false;
    }

    fileStream << jsonData.dump(4);
    return true;
}