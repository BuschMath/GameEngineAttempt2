#ifndef COMPONENT_FACTORY_H
#define COMPONENT_FACTORY_H

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <memory>
#include "Component.h"

class ComponentFactory {
public:
    static ComponentFactory& GetInstance() {
        static ComponentFactory instance;
        return instance;
    }

    template<typename T, typename... Args>
    std::shared_ptr<T> CreateComponent(Args&&... args) {
        static_assert(std::is_base_of<Component, T>::value, "T must be a subclass of Component");

        auto component = std::make_shared<T>(std::forward<Args>(args)...);
        m_components[typeid(T)].push_back(component);

        return component;
    }

private:
    ComponentFactory() {}; // Private constructor to enforce singleton pattern
    ~ComponentFactory() {}; // Private destructor to prevent accidental deletion

    // Disable copy and assignment
    ComponentFactory(const ComponentFactory&) = delete;
    ComponentFactory& operator=(const ComponentFactory&) = delete;

    std::unordered_map<std::type_index, std::vector<std::shared_ptr<Component>>> m_components;
};


#endif // !COMPONENT_FACTORY_H
