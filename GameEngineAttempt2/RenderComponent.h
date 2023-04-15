#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include "Component.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class RenderComponent : public Component {
public:
    RenderComponent() {
        m_vao = 0;
        m_vbo = 0;
        m_ebo = 0;
        m_elementCount = 0;
        m_meshDataFilePath = "";
    }
    virtual ~RenderComponent() {}

    void SetMesh(unsigned int vao, unsigned int vbo, unsigned int ebo, unsigned int elementCount) {
        m_vao = vao;
        m_vbo = vbo;
        m_ebo = ebo;
        m_elementCount = elementCount;
    }

    void SetMeshDataFilePath(std::string meshDataFilePath) { m_meshDataFilePath = meshDataFilePath; }

    unsigned int GetVAO() const { return m_vao; }
    unsigned int GetVBO() const { return m_vbo; }
    unsigned int GetEBO() const { return m_ebo; }
    unsigned int GetElementCount() const { return m_elementCount; }
    std::string& GetMeshDataFilePath() { return m_meshDataFilePath; }

private:
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ebo;
    unsigned int m_elementCount;
    std::string m_meshDataFilePath;
};

#endif // !RENDER_COMPONENT_H
