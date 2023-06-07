#include "WeaponComponent.hpp"

const float WEAPON_ANIMATION_TIME = 1.0f;

WeaponComponent::WeaponComponent() {
  m_weaponRecoilFinished = false;
  m_triggerPressed = false;
  m_weaponRecoilTime = WEAPON_ANIMATION_TIME;
  m_weaponRecoilAmount = 0.0f;
}

glm::vec3 WeaponComponent::getWeaponPosition() const { return m_position; }

bool WeaponComponent::isTriggerPressed() const { return m_triggerPressed; }

bool WeaponComponent::hasWeaponRecoilFinished() const {
  return m_weaponRecoilFinished;
}

float WeaponComponent::getWeaponRecoilTime() const {
  return m_weaponRecoilTime;
}

float WeaponComponent::getWeaponRecoilAmount() const {
  return m_weaponRecoilAmount;
}

void WeaponComponent::setWeaponPosition(glm::vec3 newPosition) {
  m_position = newPosition;
}

void WeaponComponent::setIfTriggerPressed(bool state) {
  m_triggerPressed = state;
}

void WeaponComponent::setIfWeaponRecoilFinished(bool state) {
  m_weaponRecoilFinished = state;
}

void WeaponComponent::setWeaponRecoilTime(float newRecoilTime) {
  m_weaponRecoilTime = newRecoilTime;
}

void WeaponComponent::updateRecoilTime(float deltaTime) {
  m_weaponRecoilTime += deltaTime;
}

void WeaponComponent::setWeaponRecoilAmount(float newRecoilAmount) {
  m_weaponRecoilAmount = newRecoilAmount;
}