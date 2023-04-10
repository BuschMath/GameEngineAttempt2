#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include "Component.h"
#include <glm/glm.hpp>

class PositionComponent : public Component {
public:
    PositionComponent(glm::vec3 position = glm::vec3(0.0f)) : m_position(position) {}

    glm::vec3 GetPosition() const { return m_position; }
    void SetPosition(glm::vec3 position) { m_position = position; }

private:
    glm::vec3 m_position;
};

#endif // !POSITION_COMPONENT_H