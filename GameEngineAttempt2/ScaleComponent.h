#ifndef SCALE_COMPONENT_H
#define SCALE_COMPONENT_H

#include "Component.h"
#include <glm/glm.hpp>

class ScaleComponent {
public:
    ScaleComponent(const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
        : m_Scale(scale) {}

    const glm::vec3& GetScale() const { return m_Scale; }
    void SetScale(const glm::vec3& scale) { m_Scale = scale; }

private:
    glm::vec3 m_Scale; // Scale factors for x, y, and z axes
};

#endif // !SCALE_COMPONENT_H

