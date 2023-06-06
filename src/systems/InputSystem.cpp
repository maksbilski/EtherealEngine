#include "InputSystem.hpp"
#include "../vendor/glm/gtc/quaternion.hpp"
#include "../vendor/glm/gtx/quaternion.hpp"

InputSystem::InputSystem(GLFWwindow *window, EntityManager &entityManager)
    : m_Window(window), m_EntityManager(entityManager) {
  m_TargetLookAngleX = 0.0f;
  m_TargetLookAngleY = 0.0f;

  m_MouseSensitivity = 10.0f;
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
  updateWeaponTransform();
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
  updateWeaponTransform();
  m_EntityManager.getCameraComponent().computeWalkVectors();
}

void InputSystem::updateWeaponTransform() {
  glm::vec3 weaponPosition = m_EntityManager.getCameraComponent().getPosition();
  glm::vec3 weaponPositionOffset = glm::vec3(2.0f, -3.0f, -12.0f);
  weaponPosition += weaponPositionOffset;
  glm::vec3 weaponRotation = m_EntityManager.getCameraComponent().getRotation();
  glm::vec3 weaponRotationOffset = glm::vec3(0.0f, -90.0f, 0.0f);
  weaponRotation -= weaponRotationOffset;
  // glm::mat4 rotationMatrix = glm::mat4(
  //     glm::vec4(m_EntityManager.getCameraComponent().getCameraSidewayVec(),
  //               0.0f),
  //     glm::vec4(m_EntityManager.getCameraComponent().getCameraUpVec(), 0.0f),
  //     glm::vec4(-m_EntityManager.getCameraComponent().getCameraForwardVec(),
  //               0.0f),
  //     glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
  // glm::quat quaternion = glm::quat(rotationMatrix);
  // glm::vec3 weaponRotation = glm::eulerAngles(quaternion);
  //
  // weaponRotation = glm::degrees(weaponRotation);
  //
  // weaponRotation.y -= 90.0f;

  m_EntityManager
      .getComponent<TransformComponent>(
          m_EntityManager.getCurrentWeaponEntity())
      .setPosition(weaponPosition);
  m_EntityManager
      .getComponent<TransformComponent>(
          m_EntityManager.getCurrentWeaponEntity())
      .setRotation(weaponRotation);
}