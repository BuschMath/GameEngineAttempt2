#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <vector>
#include <memory>
#include <gl/glew.h>
#include "Entity.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "Camera.h"
#include "ShaderProgram.h"

class RenderSystem {
public:
    RenderSystem();
    ~RenderSystem();

    void RegisterEntity(const std::shared_ptr<Entity>& entity);
    void UnregisterEntity(const std::shared_ptr<Entity>& entity);
    void Update(float deltaTime);
    void Render();

    void SetCamera(const std::shared_ptr<Camera>& camera);

private:
    GLuint m_vertexArrayObject; // OpenGL VAO
    GLuint m_vertexBufferObject; // OpenGL VBO
    GLuint m_elementBufferObject; // OpenGL EBO

    std::vector<std::shared_ptr<Entity>> m_entities;
    std::shared_ptr<Camera> m_camera;
    ShaderProgram m_ShaderProgram;
};

#endif // !RENDER_SYSTEM_H

