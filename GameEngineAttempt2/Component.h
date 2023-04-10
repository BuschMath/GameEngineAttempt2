#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component : public std::enable_shared_from_this<Component> {
public:
    virtual ~Component() = default;

    // Add any necessary public member functions for the component...
    void SetParent(std::shared_ptr<Entity> parent) { m_parent = parent; }
    std::shared_ptr<Entity> GetParent() const { return m_parent.lock(); }

protected:
    Component() = default;

private:
    // Add any necessary private member variables for the component...
    std::weak_ptr<Entity> m_parent;
};

#endif // !COMPONENT_H
