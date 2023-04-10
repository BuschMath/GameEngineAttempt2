#ifndef VELOCITY_COMPONENT_H
#define VELOCITY_COMPONENT_H

#include "Component.h"
#include <glm/glm.hpp>

class VelocityComponent : public Component {
public:
    VelocityComponent(glm::vec3 velocity = glm::vec3(0.0f)) : m_velocity(velocity) {}

    glm::vec3 GetVelocity() const { return m_velocity; }
    void SetVelocity(glm::vec3 velocity) { m_velocity = velocity; }

private:
    glm::vec3 m_velocity;
};

#endif // !VELOCITY_COMPONENT_H