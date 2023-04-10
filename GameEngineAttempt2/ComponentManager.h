#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include <memory>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include "Component.h"

class ComponentManager {
public:
    static ComponentManager& GetInstance() {
        static ComponentManager instance;
        return instance;
    }

    template<typename T, typename... Args>
    std::shared_ptr<T> AddComponent(Args&&... args) {
        static_assert(std::is_base_of<Component, T>::value, "T must be a subclass of Component");

        auto component = std::make_shared<T>(std::forward<Args>(args)...);
        m_components[typeid(T)].push_back(component);
        return component;
    }

    template<typename T>
    std::vector<std::shared_ptr<T>> GetComponents() {
        static_assert(std::is_base_of<Component, T>::value, "T must be a subclass of Component");

        std::vector<std::shared_ptr<T>> components;
        auto& componentList = m_components[typeid(T)];
        for (auto& component : componentList) {
            auto typedComponent = std::dynamic_pointer_cast<T>(component);
            if (typedComponent) {
                components.push_back(typedComponent);
            }
        }

        return components;
    }

    void RemoveComponent(std::shared_ptr<Component> component) {
        auto& componentList = m_components[typeid(*component)];
        componentList.erase(std::remove(componentList.begin(), componentList.end(), component), componentList.end());
    }

private:
    ComponentManager() {} // Private constructor to enforce singleton pattern
    ~ComponentManager() {} // Private destructor to prevent accidental deletion

    std::unordered_map<std::type_index, std::vector<std::shared_ptr<Component>>> m_components;

    // Disable copy and assignment
    ComponentManager(const ComponentManager&) = delete;
    ComponentManager& operator=(const ComponentManager&) = delete;
};

#endif // !COMPONENT_MANAGER_H
