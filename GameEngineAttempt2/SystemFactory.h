#ifndef SYSTEM_FACTORY_H
#define SYSTEM_FACTORY_H

#include "System.h"

// SystemFactory class
class SystemFactory {
public:
    template<typename T>
    static T* CreateSystem() {
        return new T();
    }
};

#endif // !SYSTEM_FACTORY_H

