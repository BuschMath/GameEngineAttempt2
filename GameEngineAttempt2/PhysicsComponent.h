#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include "Component.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

class PhysicsComponent : public Component {
public:
    glm::vec3 position; // 3D position
    glm::vec3 velocity; // 3D velocity
    glm::vec3 acceleration; // 3D acceleration
    float mass; // Mass of the entity
    bool isCollidable; // Flag indicating if the entity is collidable
    glm::quat rotation; // Rotation quaternion
    glm::vec3 scale; // Scale factor in x, y, and z directions

    PhysicsComponent() : position(0.0f), velocity(0.0f), acceleration(0.0f), mass(1.0f), isCollidable(true), rotation(1.0f, 0.0f, 0.0f, 0.0f), scale(1.0f) {}

    // Update the physics component based on time step
    void Update(float deltaTime) {
        // Update position based on velocity and time step
        position += velocity * deltaTime;

        // Update velocity based on acceleration and time step
        velocity += acceleration * deltaTime;
    }

    // Apply a force to the physics component
    void ApplyForce(const glm::vec3& force) {
        // Update acceleration based on force and mass
        acceleration += force / mass;
    }

    // Set the mass of the physics component
    void SetMass(float mass) {
        this->mass = mass;
    }

    // Set the rotation of the physics component
    void SetRotation(const glm::quat& rotation) {
        this->rotation = rotation;
    }

    // Set the scale of the physics component
    void SetScale(const glm::vec3& scale) {
        this->scale = scale;
    }

    glm::mat4 GetTransform() const {
        // Calculate the transformation matrix of the entity based on its position, rotation, and scale
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
        glm::mat4 rotationMatrix = glm::toMat4(rotation);
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

        return translationMatrix * rotationMatrix * scaleMatrix;
    }
};


#endif // !PHYSICS_COMPONENT_H
