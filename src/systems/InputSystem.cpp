#include "InputSystem.hpp"
#include "../vendor/glm/gtc/quaternion.hpp"
#include "../vendor/glm/gtx/quaternion.hpp"

const float WEAPON_RECOIL_ANIMATION_TIME = 1.0f;

InputSystem::InputSystem(GLFWwindow *window, EntityManager &entityManager)
    : m_window(window), m_entityManager(entityManager) {
  m_targetLookAngleX = 0.0f;
  m_targetLookAngleY = 0.0f;

  m_mouseSensitivity = 0.001f;
  m_movementSpeed = 50.0f;
  m_jumpTimer = 0.0f;

  glfwGetCursorPos(window, &m_cursorX, &m_cursorY);
}

void InputSystem::update(float deltaTime) {
  controlMouseInput(deltaTime);
  controlButtonsInput(deltaTime);
  controlWeaponRecoil(deltaTime);
}

void InputSystem::controlMouseInput(float deltaTime) {
  double newCursorX;
  double newCursorY;
  float maxLookPitch = 1.5707963f - 0.01f;

  glfwGetCursorPos(m_window, &newCursorX, &newCursorY);

  m_targetLookAngleX -= (newCursorY - m_cursorY) * m_mouseSensitivity;
  m_targetLookAngleY -= (newCursorX - m_cursorX) * m_mouseSensitivity;

  if (m_targetLookAngleX > maxLookPitch)
    m_targetLookAngleX = maxLookPitch;
  if (m_targetLookAngleX < -maxLookPitch)
    m_targetLookAngleX = -maxLookPitch;

  m_cursorX = newCursorX;
  m_cursorY = newCursorY;

  m_entityManager.getCameraComponent().setCurrentLookAngleX(m_targetLookAngleX);
  m_entityManager.getCameraComponent().setCurrentLookAngleY(m_targetLookAngleY);

  m_entityManager.getCameraComponent().computeCameraOrientation();
  m_entityManager.getCameraComponent().computeWalkVectors();
}

void InputSystem::controlButtonsInput(float deltaTime) {

  glm::vec3 movementVector(0.0f);

  WeaponComponent &currentWeapon =
      m_entityManager.getComponent<WeaponComponent>(
          m_entityManager.getCurrentWeaponEntity());

  if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
    movementVector +=
        m_entityManager.getCameraComponent().getMovementForwardVec() *
        m_movementSpeed * deltaTime;

  if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
    movementVector -=
        m_entityManager.getCameraComponent().getMovementForwardVec() *
        m_movementSpeed * deltaTime;

  if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
    movementVector +=
        m_entityManager.getCameraComponent().getMovementSidewayVec() *
        m_movementSpeed * deltaTime;

  if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
    movementVector -=
        m_entityManager.getCameraComponent().getMovementSidewayVec() *
        m_movementSpeed * deltaTime;

  if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    m_jumpTimer = 0.5f;
  }
  if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    if (!currentWeapon.isTriggerPressed() &&
        currentWeapon.hasWeaponRecoilFinished()) {
      currentWeapon.setWeaponRecoilTime(0.0f);
      currentWeapon.setIfTriggerPressed(true);
    }
  } else {
    currentWeapon.setIfTriggerPressed(false);
  }

  m_entityManager
      .getComponent<TransformComponent>(m_entityManager.getPlayerEntity())
      .updatePosition(movementVector);
  m_entityManager.getCameraComponent().setPosition(
      m_entityManager
          .getComponent<TransformComponent>(m_entityManager.getPlayerEntity())
          .getPosition());
  m_entityManager.getCameraComponent().computeCameraOrientation();
  m_entityManager.getCameraComponent().computeWalkVectors();
}

void InputSystem::controlWeaponRecoil(float deltaTime) {
  float recoilFactor;
  WeaponComponent &currentWeapon =
      m_entityManager.getComponent<WeaponComponent>(
          m_entityManager.getCurrentWeaponEntity());
  currentWeapon.updateRecoilTime(deltaTime);
  currentWeapon.setIfWeaponRecoilFinished(false);

  if (currentWeapon.getWeaponRecoilTime() >= WEAPON_RECOIL_ANIMATION_TIME) {
    currentWeapon.setWeaponRecoilTime(WEAPON_RECOIL_ANIMATION_TIME);
    currentWeapon.setIfWeaponRecoilFinished(true);
  }
  recoilFactor =
      currentWeapon.getWeaponRecoilTime() / WEAPON_RECOIL_ANIMATION_TIME;
  currentWeapon.setWeaponRecoilAmount(
      -((recoilFactor * recoilFactor) - recoilFactor) *
      pow(abs(recoilFactor - 1.0), 3));
}