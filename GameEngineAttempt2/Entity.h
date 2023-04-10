#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <string>
#include <vector>
#include "Component.h"

class Entity : public std::enable_shared_from_this<Entity> {
public:
    Entity(const std::string& name = "") : m_name(name) {}

    const std::string& GetName() const { return m_name; }
    void SetName(const std::string& name) { m_name = name; }

    template<typename T, typename... Args>
    std::shared_ptr<T> AddComponent(Args&&... args) {
        static_assert(std::is_base_of<Component, T>::value, "T must be a subclass of Component");

        auto component = std::make_shared<T>(std::forward<Args>(args)...);
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

private:
    std::string m_name;
    std::vector<std::shared_ptr<Component>> m_components;
};

#endif // !ENTITY_H
