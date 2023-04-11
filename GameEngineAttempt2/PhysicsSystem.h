#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include "System.h"

// PhysicsSystem class
class PhysicsSystem : public System {
public:
    void Initialize() override {
        // Initialize physics system
    }

    void Update(float deltaTime) override {
        // Update physics system
    }

    void Shutdown() override {
        // Shutdown physics system
    }
};

#endif // !PHYSICS_SYSTEM_H

