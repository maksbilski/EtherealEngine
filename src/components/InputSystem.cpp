#include "InputSystem.hpp"

InputSystem::InputSystem(GLFWwindow *window, CameraComponent &camera)
    : m_Window(window), m_Camera(camera) {
  m_TargetLookAngleX = 0.0f;
  m_TargetLookAngleY = 0.0f;

  m_MouseSensitivity = 5.0f;
  m_MovementSpeed = 10.0f;
  m_JumpTimer = 0.0f;

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
          m_MouseSensitivity;

  tempCurrentLookAngleY =
      m_Camera.getCurrentLookAngleY() +
      (m_TargetLookAngleY - m_Camera.getCurrentLookAngleY()) * deltaTime *
          m_MouseSensitivity;

  m_Camera.setCurrentLookAngleX(tempCurrentLookAngleX);
  m_Camera.setCurrentLookAngleY(tempCurrentLookAngleY);

  m_Camera.computeCameraOrientation();
  m_Camera.computeWalkVectors();
}

void InputSystem::controlKeyboardInput(float deltaTime) {

  glm::vec3 movementVector(0.0f);

  if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
    movementVector +=
        m_Camera.getMovementForwardVec() * m_MovementSpeed * deltaTime;

  if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
    movementVector -=
        m_Camera.getMovementForwardVec() * m_MovementSpeed * deltaTime;

  if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
    movementVector +=
        m_Camera.getMovementSidewayVec() * m_MovementSpeed * deltaTime;

  if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
    movementVector -=
        m_Camera.getMovementSidewayVec() * m_MovementSpeed * deltaTime;

  if (glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    m_JumpTimer = 0.5f;
  }

  if (m_JumpTimer > 0)

    m_Camera.updatePosition(movementVector);
}