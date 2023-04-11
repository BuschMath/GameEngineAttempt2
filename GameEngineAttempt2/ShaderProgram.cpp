#include "ShaderProgram.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include "glm/gtc/type_ptr.hpp"

ShaderProgram::ShaderProgram()
    : m_programID(0)
{
}

ShaderProgram::ShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderSourceCStr = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderSourceCStr, NULL);
    glCompileShader(vertexShader);

    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        throw std::runtime_error("Failed to compile vertex shader:\n" + std::string(infoLog));
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderSourceCStr = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderSourceCStr, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        throw std::runtime_error("Failed to compile fragment shader:\n" + std::string(infoLog));
    }

    m_programID = glCreateProgram();
    glAttachShader(m_programID, vertexShader);
    glAttachShader(m_programID, fragmentShader);
    glLinkProgram(m_programID);

    glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(m_programID, 512, NULL, infoLog);
        throw std::runtime_error("Failed to link shader program:\n" + std::string(infoLog));
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


ShaderProgram::~ShaderProgram()
{
    if (m_programID != 0)
    {
        glDeleteProgram(m_programID);
    }
}

bool ShaderProgram::loadShaderFromFile(const std::string& filePath, GLenum shaderType)
{
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        std::cerr << "Failed to open shader file: " << filePath << std::endl;
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return loadShaderFromString(buffer.str(), shaderType);
}

bool ShaderProgram::loadShaderFromString(const std::string& shaderSource, GLenum shaderType)
{
    GLuint shaderID = glCreateShader(shaderType);

    const char* sourcePtr = shaderSource.c_str();
    glShaderSource(shaderID, 1, &sourcePtr, nullptr);
    glCompileShader(shaderID);

    GLint success = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

    if (success == GL_FALSE)
    {
        GLint logSize = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logSize);

        std::vector<GLchar> errorLog(logSize);
        glGetShaderInfoLog(shaderID, logSize, &logSize, &errorLog[0]);

        std::cerr << "Failed to compile shader: " << std::endl;
        std::cerr << &errorLog[0] << std::endl;

        glDeleteShader(shaderID);

        return false;
    }

    m_shaders.push_back(shaderID);

    return true;
}

bool ShaderProgram::link()
{
    if (m_programID != 0)
    {
        std::cerr << "Shader program already linked" << std::endl;
        return false;
    }

    m_programID = glCreateProgram();

    for (auto shader : m_shaders)
    {
        glAttachShader(m_programID, shader);
    }

    glLinkProgram(m_programID);

    GLint success = 0;
    glGetProgramiv(m_programID, GL_LINK_STATUS, &success);

    if (success == GL_FALSE)
    {
        GLint logSize = 0;
        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &logSize);

        std::vector<GLchar> errorLog(logSize);
        glGetProgramInfoLog(m_programID, logSize, &logSize, &errorLog[0]);

        std::cerr << "Failed to link shader program: " << std::endl;
        std::cerr << &errorLog[0] << std::endl;

        glDeleteProgram(m_programID);
        m_programID = 0;

        return false;
    }

    return true;
}

void ShaderProgram::bind() const
{
    if (m_programID != 0)
    {
        glUseProgram(m_programID);
    }
}

void ShaderProgram::unbind() const
{
    glUseProgram(0);
}

GLint ShaderProgram::getUniformLocation(const std::string& name)
{
    if (m_programID != 0)
    {
        return glGetUniformLocation(m_programID, name.c_str());
    }
    else
    {
        return -1;
    }
}

void ShaderProgram::setUniformInt(const std::string& name, int value) {
    glUniform1i(glGetUniformLocation(m_programID, name.c_str()), value);
}

void ShaderProgram::setUniformFloat(const std::string& name, float value) {
    glUniform1f(glGetUniformLocation(m_programID, name.c_str()), value);
}

void ShaderProgram::setUniformVec3(const std::string& name, const glm::vec3& value) {
    glUniform3fv(glGetUniformLocation(m_programID, name.c_str()), 1, glm::value_ptr(value));
}

void ShaderProgram::setUniformMat4(const std::string& name, const glm::mat4& value) {
    glUniformMatrix4fv(glGetUniformLocation(m_programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
