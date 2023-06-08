#include "PlayerHealthComponent.hpp"

PlayerHealthComponent::PlayerHealthComponent(int maxHealth)
    : m_maxHealth(maxHealth) {
  m_currentHealth = maxHealth;
  m_nextDamageTime = 0.0f;
  m_isAlive = true;
  m_isHit = false;
  m_isHealed = false;
}

int PlayerHealthComponent::getMaxHealth() const { return m_maxHealth; }

int PlayerHealthComponent::getCurrentHealth() const { return m_currentHealth; }

float PlayerHealthComponent::getNextDamageTime() const {
  return m_nextDamageTime;
}

bool PlayerHealthComponent::isAlive() const { return m_isAlive; }

bool PlayerHealthComponent::isHit() const { return m_isHit; }

bool PlayerHealthComponent::isHealed() const { return m_isHealed; }

void PlayerHealthComponent::updateCurrentHealth(int value) {
  m_currentHealth += value;
}

void PlayerHealthComponent::updateNextDamageTime(float value) {
  m_nextDamageTime += value;
}

void PlayerHealthComponent::setNextDamageTime(float newNextDamageTime) {
  m_nextDamageTime = newNextDamageTime;
}

void PlayerHealthComponent::setMaxHealth(int newMaxHealth) {
  m_maxHealth = newMaxHealth;
}

void PlayerHealthComponent::setCurrentHealth(int newCurrentHealth) {
  m_currentHealth = newCurrentHealth;
}

void PlayerHealthComponent::setIfIsHit(bool state) { m_isHit = state; }

void PlayerHealthComponent::setIfIsHealed(bool state) { m_isHealed = state; }