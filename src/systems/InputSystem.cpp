#include "InputSystem.hpp"
#include "../vendor/glm/gtc/quaternion.hpp"
#include "../vendor/glm/gtx/quaternion.hpp"

InputSystem::InputSystem(GLFWwindow *window, EntityManager &entityManager)
    : m_Window(window), m_EntityManager(entityManager) {
  m_TargetLookAngleX = 0.0f;
  m_TargetLookAngleY = 0.0f;

  m_MouseSensitivity = 0.001f;
  m_MovementSpeed = 50.0f;
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
  float maxLookPitch = 1.5707963f - 0.01f;

  glfwGetCursorPos(m_Window, &newCursorX, &newCursorY);

  m_TargetLookAngleX -= (newCursorY - m_CursorY) * m_MouseSensitivity;
  m_TargetLookAngleY -= (newCursorX - m_CursorX) * m_MouseSensitivity;

  if (m_TargetLookAngleX > maxLookPitch)
    m_TargetLookAngleX = maxLookPitch;
  if (m_TargetLookAngleX < -maxLookPitch)
    m_TargetLookAngleX = -maxLookPitch;

  m_CursorX = newCursorX;
  m_CursorY = newCursorY;

  m_EntityManager.getCameraComponent().setCurrentLookAngleX(m_TargetLookAngleX);
  m_EntityManager.getCameraComponent().setCurrentLookAngleY(m_TargetLookAngleY);

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