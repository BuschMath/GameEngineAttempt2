#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include "Component.h"

class HealthComponent : public Component {
public:
    HealthComponent(int health = 100) : m_health(health) {}

    int GetHealth() const { return m_health; }
    void SetHealth(int health) { m_health = health; }

private:
    int m_health;
};

#endif // !HEALTH_COMPONENT_H