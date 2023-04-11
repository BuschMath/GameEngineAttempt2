#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <string>
#include <unordered_map>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

class ShaderProgram {
public:
    ShaderProgram();
    ShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
    ~ShaderProgram();

    GLuint getProgram() const { return m_programID; };

    void bind() const;
    void unbind() const;

    void setUniformInt(const std::string& name, int value);
    void setUniformFloat(const std::string& name, float value);
    void setUniformVec3(const std::string& name, const glm::vec3& value);
    void setUniformMat4(const std::string& name, const glm::mat4& value);

    bool loadShaderFromFile(const std::string& filePath, GLenum shaderType);
    bool loadShaderFromString(const std::string& shaderSource, GLenum shaderType);

    bool link();

private:
    GLuint m_programID;
    std::vector<GLuint> m_shaders;
    std::unordered_map<std::string, GLint> m_uniforms;

    GLint getUniformLocation(const std::string& name);
};

#endif // !SHADER_PROGRAM_H

