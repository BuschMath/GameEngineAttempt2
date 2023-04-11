#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <string>
#include <vector>
#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

class Entity : public std::enable_shared_from_this<Entity> {
public:
    Entity(const std::string& name = "") : m_name(name) {}

    const std::string& GetName() const { return m_name; }
    void SetName(const std::string& name) { m_name = name; }

    template<typename T>
    std::shared_ptr<T> AddComponent() {
        std::shared_ptr<T> component = std::make_shared<T>();
        static_assert(std::is_base_of<Component, T>::value, "T must be a subclass of Component");

        component->SetParent(shared_from_this());
        m_components.push_back(component);

        return component;
    }

    template<typename T>
    std::vector<std::shared_ptr<T>> GetComponents() const {
        static_assert(std::is_base_of<Component, T>::value, "T must be a subclass of Component");

        std::vector<std::shared_ptr<T>> components;
        for (auto& component : m_components) {
            auto typedComponent = std::dynamic_pointer_cast<T>(component);
            if (typedComponent) {
                components.push_back(typedComponent);
            }
        }

        return components;
    }

    void RemoveComponents() {
        for (auto& component : m_components) {
            component->SetParent(std::shared_ptr<Entity>());
        }
        m_components.clear();
    }

    template<typename T>
    bool HasComponent() const {
        static_assert(std::is_base_of<Component, T>::value, "T must be a subclass of Component");

        for (auto& component : m_components) {
            if (dynamic_cast<T*>(component.get())) {
                return true;
            }
        }

        return false;
    }

    glm::mat4 GetTransform() const {
        // Calculate the transformation matrix of the entity based on its position, rotation, and scale
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), m_position);
        glm::mat4 rotationMatrix = glm::toMat4(m_rotation);
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), m_scale);

        return translationMatrix * rotationMatrix * scaleMatrix;
    }

private:
    std::string m_name;
    std::vector<std::shared_ptr<Component>> m_components;
};

#endif // !ENTITY_H
