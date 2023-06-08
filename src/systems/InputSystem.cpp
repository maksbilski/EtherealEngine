#include "InputSystem.hpp"
#include "../vendor/glm/gtc/quaternion.hpp"
#include "../vendor/glm/gtx/quaternion.hpp"

const float WEAPON_RECOIL_ANIMATION_TIME = 1.0f;

const float JUMP_ACCELERATION_TIME = 0.01f;

const float JUMP_STRENGTH = 10000.0f;

const float GRAVITY_STRENGTH = 200.0f;

const float WEAPON_BOB_SPEED = 9.0f;

InputSystem::InputSystem(GLFWwindow *window, EntityManager &entityManager)
    : m_window(window), m_entityManager(entityManager) {
  m_targetLookAngleX = 0.0f;
  m_targetLookAngleY = 0.0f;

  m_mouseSensitivity = 0.001f;
  m_movementSpeed = 120.0f;
  m_jumpTimer = 0.0f;
  m_gravity = 0.0f;

  glfwGetCursorPos(window, &m_cursorX, &m_cursorY);
}

void InputSystem::update(float deltaTime) {
  controlMouseInput();
  controlButtonsInput(deltaTime);
  controlWeaponBobbing(deltaTime);
  controlWeaponRecoil(deltaTime);
}

void InputSystem::controlMouseInput() {
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

  m_entityManager.getCameraComponent().setIfIsMoving(false);

  if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS) {
    movementVector +=
        m_entityManager.getCameraComponent().getMovementForwardVec() *
        m_movementSpeed * deltaTime;
    m_entityManager.getCameraComponent().setIfIsMoving(true);
  }

  if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS) {
    movementVector -=
        m_entityManager.getCameraComponent().getMovementForwardVec() *
        m_movementSpeed * deltaTime;
    m_entityManager.getCameraComponent().setIfIsMoving(true);
  }

  if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS) {
    movementVector +=
        m_entityManager.getCameraComponent().getMovementSidewayVec() *
        m_movementSpeed * deltaTime;
    m_entityManager.getCameraComponent().setIfIsMoving(true);
  }

  if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS) {
    movementVector -=
        m_entityManager.getCameraComponent().getMovementSidewayVec() *
        m_movementSpeed * deltaTime;
    m_entityManager.getCameraComponent().setIfIsMoving(true);
  }

  if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS &&
      m_entityManager.getCameraComponent().getIfIsTouchingGround()) {
    m_jumpTimer = JUMP_ACCELERATION_TIME;
  }
  if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    if (!currentWeapon.isTriggerPressed() &&
        currentWeapon.hasWeaponRecoilFinished()) {
      currentWeapon.setWeaponRecoilTime(0.0f);
      currentWeapon.setIfTriggerPressed(true);
      m_entityManager
          .getComponent<SoundComponent>(
              m_entityManager.getCurrentWeaponEntity())
          .playSound();
    }
  } else {
    currentWeapon.setIfTriggerPressed(false);
  }

  if (m_jumpTimer > 0.0) {
    m_gravity =
        (JUMP_STRENGTH * (m_jumpTimer / JUMP_ACCELERATION_TIME) * deltaTime);
  }
  m_jumpTimer -= deltaTime;

  m_gravity -= GRAVITY_STRENGTH * deltaTime;

  movementVector += m_entityManager.getCameraComponent().getMovementUpVec() *
                    m_gravity * deltaTime;

  m_entityManager
      .getComponent<TransformComponent>(m_entityManager.getPlayerEntity())
      .updatePosition(movementVector);
  m_entityManager.getCameraComponent().setPosition(
      m_entityManager
          .getComponent<TransformComponent>(m_entityManager.getPlayerEntity())
          .getPosition());

  if (m_entityManager
          .getComponent<TransformComponent>(m_entityManager.getPlayerEntity())
          .getPosition()
          .y < 14.0f) {
    m_entityManager
        .getComponent<TransformComponent>(m_entityManager.getPlayerEntity())
        .setPositionY(14.0f);
    m_gravity = 0.0f;
    m_entityManager.getCameraComponent().setIfIsTouchingGround(true);
  } else {
    m_entityManager.getCameraComponent().setIfIsTouchingGround(false);
  }

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

void InputSystem::controlWeaponBobbing(float deltaTime) {
  WeaponComponent &currentWeapon =
      m_entityManager.getComponent<WeaponComponent>(
          m_entityManager.getCurrentWeaponEntity());
  if (m_entityManager.getCameraComponent().getIfIsMoving() &&
      m_entityManager.getCameraComponent().getIfIsTouchingGround()) {
    currentWeapon.updateWeaponBob(WEAPON_BOB_SPEED * deltaTime);
    currentWeapon.setWeaponBobAmount(cos(currentWeapon.getWeaponBob()));
  } else {
    currentWeapon.setWeaponBob(0.0f);
    currentWeapon.setWeaponBobAmount(0.0f);
  }
}