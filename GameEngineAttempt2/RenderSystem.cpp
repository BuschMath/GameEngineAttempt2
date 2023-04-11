#include "RenderSystem.h"

RenderSystem::RenderSystem() {
    // Initialize OpenGL resources (VAO, VBO, EBO, shaders, etc.)
    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);

    glGenBuffers(1, &m_vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
    // Set up vertex data, buffer data to VBO, set vertex attributes

    glGenBuffers(1, &m_elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferObject);
    // Set up element (index) data, buffer data to EBO

    // Compile and link shaders, create shader program
    m_ShaderProgram.loadShaderFromFile("vertexShader.glsl", GL_VERTEX_SHADER);
    m_ShaderProgram.loadShaderFromFile("fragmentShader.glsl", GL_FRAGMENT_SHADER);
    m_ShaderProgram.link();
    // Attach shaders, link program, set uniform locations, etc.

    // Unbind VAO, VBO, EBO, shaders
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glUseProgram(0);
}

RenderSystem::~RenderSystem() {
    // Clean up OpenGL resources (VAO, VBO, EBO, shaders, etc.)
    glDeleteBuffers(1, &m_vertexBufferObject);
    glDeleteBuffers(1, &m_elementBufferObject);
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void RenderSystem::RegisterEntity(const std::shared_ptr<Entity>& entity) {
    // Add the entity to the list of registered entities
    m_entities.push_back(entity);
}

void RenderSystem::UnregisterEntity(const std::shared_ptr<Entity>& entity) {
    // Remove the entity from the list of registered entities
    auto it = std::find(m_entities.begin(), m_entities.end(), entity);
    if (it != m_entities.end()) {
        m_entities.erase(it);
    }
}

void RenderSystem::Update(float deltaTime) {
    // Update any necessary rendering logic based on the current game state and time
}

void RenderSystem::Render() {
    // Render all registered entities using the current camera settings
    m_ShaderProgram.bind();
    glBindVertexArray(m_vertexArrayObject);

    // Set up camera uniform data, such as view matrix, projection matrix, etc.
    // Set other uniform data, such as lights, materials, etc.

    for (const auto& entity : m_entities) {
        // Check if the entity has a render component
        if (entity->HasComponent<RenderComponent>()) {
            // Get the render component of the entity
            auto renderComponent = entity->GetComponents<RenderComponent>();

            // Update model matrix uniform with the transform of the entity
            m_ShaderProgram.setUniformMat4()
            glUniformMatrix4fv(/* Model matrix uniform location */, 1, GL_FALSE, glm::value_ptr(entity->GetTransform()));

            // Render the entity's geometry using the element buffer object and draw call
            glDrawElements(/* Draw mode */, /* Element count */, GL_UNSIGNED_INT, 0);
        }
    }

    // Unbind VAO and shader program
    glBindVertexArray(0);
    glUseProgram(0);
}

void RenderSystem::SetCamera(const std::shared_ptr<Camera>& camera) {
    // Set the camera to be used for rendering
    m_camera = camera;
}