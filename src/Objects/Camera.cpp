#define _USE_MATH_DEFINES
#include <cmath>

#include "Camera.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../vendor/glm/gtc/matrix_inverse.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../vendor/glm/gtc/random.hpp"
#include "../vendor/glm/gtc/type_ptr.hpp"
#include "../vendor/glm/gtx/rotate_vector.hpp"

Camera::Camera(GLFWwindow *window, glm::vec3 position)
    : m_Window(window), m_Position(position) {
  m_JumpTimer = 0.0f;
  m_Gravity = 0.0f;
  m_IsTouchingGround = false;
  m_IsMoving = false;

  m_TargetLookAngleX = 0.0f;
  m_TargetLookAngleY = 0.0f;

  m_LookAngleX = 0.0f;
  m_LookAngleY = 0.0f;

  computeWalkVectors();
  glfwGetCursorPos(window, &m_OldMouseX, &m_OldMouseY);
}

void Camera::computeWalkVectors() {
  m_UpVec = glm::vec3(0.0f, 1.0f, 0.0f);
  m_ForwardVec =
      glm::rotate(glm::vec3(0.0f, 0.0f, -1.0f), m_LookAngleY, m_UpVec);
  m_SidewayVec = glm::normalize(glm::cross(m_ForwardVec, m_UpVec));
}

void Camera::controlMouseInput(float deltaTime) {
  double mouseX, mouseY;

  float maxLookPitch = 1.7f;
  float turnSpeed = 5.0f;

  glfwGetCursorPos(m_Window, &mouseX, &mouseY);

  m_TargetLookAngleX -= (mouseY - m_OldMouseY) * 0.002f;
  m_TargetLookAngleY -= (mouseX - m_OldMouseX) * 0.002f;
  if (m_TargetLookAngleX > maxLookPitch)
    m_TargetLookAngleX = maxLookPitch;
  if (m_TargetLookAngleX < -maxLookPitch)
    m_TargetLookAngleX = -maxLookPitch;

  m_OldMouseX = mouseX;
  m_OldMouseY = mouseY;

  m_LookAngleX = m_LookAngleX +
                 (m_TargetLookAngleX - m_LookAngleX) * deltaTime * turnSpeed;
  m_LookAngleY = m_LookAngleY +
                 (m_TargetLookAngleY - m_LookAngleY) * deltaTime * turnSpeed;
}

void Camera::controlMovement(float deltaTime) {
  const float movementSpeed = 10.0f;

  glm::vec3 movementVector(0.0f);

  m_IsMoving = false;

  if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS) {
    movementVector += m_ForwardVec * movementSpeed * deltaTime;
    m_IsMoving = true;
  }
  if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS) {
    movementVector -= m_ForwardVec * movementSpeed * deltaTime;
    m_IsMoving = true;
  }
  if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS) {
    movementVector += m_SidewayVec * movementSpeed * deltaTime;
    m_IsMoving = true;
  }
  if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS) {
    movementVector -= m_SidewayVec * movementSpeed * deltaTime;
    m_IsMoving = true;
  }

  m_Position += movementVector;
}

void Camera::computeCameraOrientation() {
  // Initialize identity matrix
  glm::mat4 camera(1.0f);

  // Apply yaw (rotation around the y-axis)
  camera = glm::rotate(camera, m_LookAngleY, glm::vec3(0.0f, 1.0f, 0.0f));

  // Apply pitch (rotation around the x-axis)
  camera = glm::rotate(camera, m_LookAngleX, glm::vec3(1.0f, 0.0f, 0.0f));

  // Extract the right, up, and forward vectors from the rotation matrix
  m_CameraSideway = glm::vec3(camera[0]);  // Right vector
  m_CameraUp = glm::vec3(camera[1]);       // Up vector
  m_CameraForward = -glm::vec3(camera[2]); // Forward vector, note the inversion

  // Compute the look position by adding the forward vector to the camera
  // position
  m_CameraLook = m_Position + m_CameraForward;
}
