#include "InputSystem.hpp"
#include "../vendor/glm/gtc/quaternion.hpp"
#include "../vendor/glm/gtx/quaternion.hpp"

const float WEAPON_RECOIL_ANIMATION_TIME = 0.8f;

const float JUMP_ACCELERATION_TIME = 0.001f;

const float JUMP_ACCELERATION = 250.0f;

const float GRAVITY_STRENGTH = 400.0f;

const float WEAPON_BOB_SPEED = 10.0f;

const float MOVEMENT_SPEED = 200.0f;

const float MOUSE_SENSITIVITY = 0.001f;

const float ONE_FRAME = 1.0f / 160.0f;

InputSystem::InputSystem(GLFWwindow *window, EntityManager &entityManager)
    : m_window(window), m_entityManager(entityManager) {
  m_targetLookAngleX = 0.0f;
  m_targetLookAngleY = 0.0f;

  m_jumpTimer = 0.0f;
  m_jumpVelocity = 0.0f;

  glfwGetCursorPos(window, &m_cursorX, &m_cursorY);
}

void InputSystem::update() {
  controlMouseInput();
  controlButtonsInput();
  controlWeaponBobbing();
  controlWeaponRecoil();
}

void InputSystem::controlMouseInput() {
  double newCursorX;
  double newCursorY;
  float maxLookPitch = 1.5707963f - 0.01f;

  glfwGetCursorPos(m_window, &newCursorX, &newCursorY);

  m_targetLookAngleX -= (newCursorY - m_cursorY) * MOUSE_SENSITIVITY;
  m_targetLookAngleY -= (newCursorX - m_cursorX) * MOUSE_SENSITIVITY;

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

void InputSystem::controlButtonsInput() {

  glm::vec3 movementVector(0.0f);

  WeaponComponent &currentWeapon =
      m_entityManager.getComponent<WeaponComponent>(
          m_entityManager.getCurrentWeaponEntity());
  CameraComponent &camera = m_entityManager.getCameraComponent();

  TransformComponent &player = m_entityManager.getComponent<TransformComponent>(
      m_entityManager.getPlayerEntity());

  camera.setIfIsMoving(false);

  if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS) {
    movementVector +=
        camera.getMovementForwardVec() * MOVEMENT_SPEED * ONE_FRAME;
    camera.setIfIsMoving(true);
  }

  if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS) {
    movementVector -=
        camera.getMovementForwardVec() * MOVEMENT_SPEED * ONE_FRAME;
    camera.setIfIsMoving(true);
  }

  if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS) {
    movementVector +=
        camera.getMovementSidewayVec() * MOVEMENT_SPEED * ONE_FRAME;
    camera.setIfIsMoving(true);
  }

  if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS) {
    movementVector -=
        camera.getMovementSidewayVec() * MOVEMENT_SPEED * ONE_FRAME;
    camera.setIfIsMoving(true);
  }

  if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS &&
      camera.getIfIsTouchingGround()) {
    m_jumpTimer = JUMP_ACCELERATION_TIME;
  }
  if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS &&
      !currentWeapon.isTriggerPressed()) {
    if (currentWeapon.hasWeaponRecoilFinished()) {
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
    m_jumpVelocity =
        (JUMP_ACCELERATION * (m_jumpTimer / JUMP_ACCELERATION_TIME));
  }
  m_jumpTimer -= ONE_FRAME;

  m_jumpVelocity -= GRAVITY_STRENGTH * ONE_FRAME;

  movementVector += camera.getMovementUpVec() * m_jumpVelocity * ONE_FRAME;

  player.updatePosition(movementVector);
  camera.setPosition(player.getPosition());

  if (player.getPosition().y < 14.0f) {
    player.setPositionY(14.0f);
    m_jumpVelocity = 0.0f;
    camera.setIfIsTouchingGround(true);
  } else {
    camera.setIfIsTouchingGround(false);
  }

  camera.computeCameraOrientation();
  camera.computeWalkVectors();
}

void InputSystem::controlWeaponRecoil() {
  float recoilFactor;
  WeaponComponent &currentWeapon =
      m_entityManager.getComponent<WeaponComponent>(
          m_entityManager.getCurrentWeaponEntity());
  currentWeapon.updateRecoilTime(ONE_FRAME);
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

void InputSystem::controlWeaponBobbing() {
  WeaponComponent &currentWeapon =
      m_entityManager.getComponent<WeaponComponent>(
          m_entityManager.getCurrentWeaponEntity());
  if (m_entityManager.getCameraComponent().getIfIsMoving() &&
      m_entityManager.getCameraComponent().getIfIsTouchingGround()) {
    currentWeapon.updateWeaponBob(WEAPON_BOB_SPEED * ONE_FRAME);
    currentWeapon.setWeaponBobAmount(cos(currentWeapon.getWeaponBob()));
  } else {
    currentWeapon.setWeaponBob(0.0f);
    currentWeapon.setWeaponBobAmount(0.0f);
  }
}