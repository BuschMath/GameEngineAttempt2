#include "EntityFactory.h"
#include "SceneFileManager.h"

void EntityFactory::SaveScene(const std::string& fileName) const {
    SceneFileManager::SaveScene(fileName, m_entityManager->GetEntities());
}

bool EntityFactory::LoadScene(const std::string& fileName) {
    m_entityManager->RemoveAllEntities();
    if (!SceneFileManager::LoadScene(fileName, *this))
    {
        m_entityFactoryLogger->error("Failed to load scene.\n");
        return false;
    }

    return true;
}