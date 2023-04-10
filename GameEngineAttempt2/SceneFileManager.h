#ifndef SCENE_FILE_MANAGER_H
#define SCENE_FILE_MANAGER_H

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
#include "EntityFactory.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"  
#include "HealthComponent.h"

class SceneFileManager {
public:
    static bool LoadScene(const std::string& filePath, EntityFactory& entityFactory); 
    static bool SaveScene(const std::string& filePath, const EntityFactory& entityFactory);
};

#endif // SCENE_FILE_MANAGER_H
