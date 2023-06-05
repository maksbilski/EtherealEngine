#include "InputSystem.hpp"

InputSystem::InputSystem(GLFWwindow *window, EntityManager &entityManager)
    : m_Window(window), m_EntityManager(entityManager) {
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
      m_EntityManager.getCameraComponent().getCurrentLookAngleX() +
      (m_TargetLookAngleX -
       m_EntityManager.getCameraComponent().getCurrentLookAngleX()) *
          deltaTime * m_MouseSensitivity;

  tempCurrentLookAngleY =
      m_EntityManager.getCameraComponent().getCurrentLookAngleY() +
      (m_TargetLookAngleY -
       m_EntityManager.getCameraComponent().getCurrentLookAngleY()) *
          deltaTime * m_MouseSensitivity;

  m_EntityManager.getCameraComponent().setCurrentLookAngleX(
      tempCurrentLookAngleX);
  m_EntityManager.getCameraComponent().setCurrentLookAngleY(
      tempCurrentLookAngleY);

  m_EntityManager.getCameraComponent().computeCameraOrientation();
  m_EntityManager.getCameraComponent().computeWalkVectors();
}

void InputSystem::controlKeyboardInput(float deltaTime) {

  glm::vec3 movementVector(0.0f);

  if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
    movementVector +=
        m_EntityManager.getCameraComponent().getMovementForwardVec() *
        m_MovementSpeed * deltaTime;

  if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
    movementVector -=
        m_EntityManager.getCameraComponent().getMovementForwardVec() *
        m_MovementSpeed * deltaTime;

  if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
    movementVector +=
        m_EntityManager.getCameraComponent().getMovementSidewayVec() *
        m_MovementSpeed * deltaTime;

  if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
    movementVector -=
        m_EntityManager.getCameraComponent().getMovementSidewayVec() *
        m_MovementSpeed * deltaTime;

  if (glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    m_JumpTimer = 0.5f;
  }
  m_EntityManager.getCameraComponent().updatePosition(movementVector);
  m_EntityManager.getCameraComponent().computeCameraOrientation();
  m_EntityManager.getCameraComponent().computeWalkVectors();
}