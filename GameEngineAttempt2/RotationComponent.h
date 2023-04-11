#ifndef ROTATION_COMPONENT_H
#define ROTATION_COMPONENT_H

#include "Component.h"
#include <glm/glm.hpp> // For GLM types

class RotationComponent : public Component {
public:
    RotationComponent(const glm::vec3& rotation = glm::vec3(0.0f, 0.0f, 0.0f))
        : m_Rotation(rotation) {}

    const glm::vec3& GetRotation() const { return m_Rotation; }
    void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; }

private:
    glm::vec3 m_Rotation; // Euler angles for rotation
};

#endif // !ROTATION_COMPONENT_H
