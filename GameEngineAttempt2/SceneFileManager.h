#ifndef SCENE_FILE_MANAGER_H
#define SCENE_FILE_MANAGER_H

class EntityFactory;

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
#include "EntityFactory.h"
#include "Component.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"  
#include "HealthComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "EntityCreator.h"

class SceneFileManager {
public:
    static bool LoadScene(const std::string& filePath, EntityFactory& entityFactory); 
    static bool SaveScene(const std::string& filePath, const std::vector<std::shared_ptr<Entity>>& entities);
};

#endif // SCENE_FILE_MANAGER_H
