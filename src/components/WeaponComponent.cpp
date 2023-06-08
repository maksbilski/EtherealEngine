#include "WeaponComponent.hpp"

const float WEAPON_ANIMATION_TIME = 1.0f;

WeaponComponent::WeaponComponent() {
  m_weaponRecoilFinished = false;
  m_triggerPressed = false;
  m_weaponRecoilTime = WEAPON_ANIMATION_TIME;
  m_weaponRecoilAmount = 0.0f;
  m_weaponBob = 0.0f;
  m_weaponBobAmount = 0.0f;
}

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

float WeaponComponent::getWeaponBob() const { return m_weaponBob; }

float WeaponComponent::getWeaponBobAmount() const { return m_weaponBobAmount; }

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

void WeaponComponent::setWeaponBob(float newWeaponBob) {
  m_weaponBob = newWeaponBob;
}

void WeaponComponent::updateWeaponBob(float updateValue) {
  m_weaponBob += updateValue;
}

void WeaponComponent::setWeaponBobAmount(float newWeaponBobAmount) {
  m_weaponBobAmount = newWeaponBobAmount;
}