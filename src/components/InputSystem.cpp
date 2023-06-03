#include "InputSystem.hpp"

InputSystem::InputSystem(GLFWwindow *window, CameraComponent &camera)
    : m_Window(window), m_Camera(camera) {
  m_TargetLookAngleX = 0.0f;
  m_TargetLookAngleY = 0.0f;

  glfwGetCursorPos(window, &m_CursorX, &m_CursorY);
}

void InputSystem::update(float deltaTime) {
  controlMouseInput(deltaTime);
  controlKeyboardInput(deltaTime);
}

void InputSystem::controlMouseInput(float deltaTime) {
  double newCursorX;
  double newCursorY;
  float maxLookPitch = 1.7f;
  float mouseSensitivity = 5.0f;

  glfwGetCursorPos(m_Window, &newCursorX, &newCursorY);

  m_TargetLookAngleX -= (newCursorY - m_CursorY) * 0.002f;
  m_TargetLookAngleY -= (newCursorX - m_CursorX) * 0.002f;

  if (m_TargetLookAngleX > maxLookPitch)
    m_TargetLookAngleX = maxLookPitch;
  if (m_TargetLookAngleX < -maxLookPitch)
    m_TargetLookAngleX = -maxLookPitch;

  m_CursorX = newCursorX;
  m_CursorY = newCursorY;

  float tempCurrentLookAngleX, tempCurrentLookAngleY;

  tempCurrentLookAngleX =
      m_Camera.getCurrentLookAngleX() +
      (m_TargetLookAngleX - m_Camera.getCurrentLookAngleX()) * deltaTime *
          mouseSensitivity;

  tempCurrentLookAngleY =
      m_Camera.getCurrentLookAngleY() +
      (m_TargetLookAngleY - m_Camera.getCurrentLookAngleY()) * deltaTime *
          mouseSensitivity;

  m_Camera.setCurrentLookAngleX(tempCurrentLookAngleX);
  m_Camera.setCurrentLookAngleY(tempCurrentLookAngleY);

  m_Camera.computeCameraOrientation();
  m_Camera.computeWalkVectors();
}

void InputSystem::controlKeyboardInput(float deltaTime) {
  float movementSpeed = 10.0f;

  glm::vec3 movementVector(0.0f);

  if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
    movementVector +=
        m_Camera.getMovementForwardVec() * movementSpeed * deltaTime;

  if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
    movementVector -=
        m_Camera.getMovementForwardVec() * movementSpeed * deltaTime;

  if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
    movementVector +=
        m_Camera.getMovementSidewayVec() * movementSpeed * deltaTime;

  if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
    movementVector -=
        m_Camera.getMovementSidewayVec() * movementSpeed * deltaTime;

  glm::vec3 tempPosition = m_Camera.getPosition();
  tempPosition += movementVector;
  m_Camera.setPosition(tempPosition);
}