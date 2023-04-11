#ifndef SYSTEM_H
#define SYSTEM_H

// Forward declaration of Entity class
class Entity;

// System base class
class System {
public:
    virtual void Initialize() {}
    virtual void Update(float deltaTime) {}
    virtual void Shutdown() {}
};

#endif // !SYSTEM_H
