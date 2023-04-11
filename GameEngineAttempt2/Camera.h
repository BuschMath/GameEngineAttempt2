#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
public:
    Camera() {}
    virtual ~Camera() {}

    void SetPosition(const glm::vec3& position) { m_position = position; }
    void SetRotation(float yaw, float pitch, float roll) {
        m_yaw = yaw;
        m_pitch = pitch;
        m_roll = roll;
        UpdateCameraVectors();
    }

    const glm::vec3& GetPosition() const { return m_position; }
    const glm::vec3& GetFront() const { return m_front; }
    const glm::vec3& GetUp() const { return m_up; }
    const glm::vec3& GetRight() const { return m_right; }
    float GetYaw() const { return m_yaw; }
    float GetPitch() const { return m_pitch; }
    float GetRoll() const { return m_roll; }

    glm::mat4 GetViewMatrix() const {
        return glm::lookAt(m_position, m_position + m_front, m_up);
    }

private:
    glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 m_right = glm::vec3(1.0f, 0.0f, 0.0f);
    float m_yaw = -90.0f;
    float m_pitch = 0.0f;
    float m_roll = 0.0f;

    void UpdateCameraVectors() {
        glm::vec3 front;
        front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        front.y = sin(glm::radians(m_pitch));
        front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_front = glm::normalize(front);
        m_right = glm::normalize(glm::cross(m_front, glm::vec3(0.0f, 1.0f, 0.0f)));
        m_up = glm::normalize(glm::cross(m_right, m_front));
    }
};

#endif // !CAMERA_H

