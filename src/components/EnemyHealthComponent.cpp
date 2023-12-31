#include "EnemyHealthComponent.hpp"
#include <iostream>

EnemyHealthComponent::EnemyHealthComponent(int maxHealth)
    : m_maxHealth(maxHealth) {
  m_currentHealth = maxHealth;
  m_isAlive = true;
  m_isOnCrosshair = false;
}

int EnemyHealthComponent::getMaxHealth() const { return m_maxHealth; }

int EnemyHealthComponent::getCurrentHealth() const { return m_currentHealth; }

bool EnemyHealthComponent::isAlive() const { return m_isAlive; }

bool EnemyHealthComponent::isOnCrosshair() const { return m_isOnCrosshair; }

void EnemyHealthComponent::updateCurrentHealth(int value) {
  m_currentHealth += value;
  if (m_currentHealth > m_maxHealth) {
    m_currentHealth = m_maxHealth;
  } else if (m_currentHealth <= 0) {
    m_currentHealth = 0;
    m_isAlive = false;
  }
}

float EnemyHealthComponent::getDistanceFromPlayer() const {
  return m_distanceFromPlayer;
}

void EnemyHealthComponent::setMaxHealth(int newMaxHealth) {
  m_maxHealth = newMaxHealth;
}

void EnemyHealthComponent::setCurrentHealth(int newCurrentHealth) {
  m_currentHealth = newCurrentHealth;
}

void EnemyHealthComponent::setIfIsOnCrosshair(bool state) {
  m_isOnCrosshair = state;
}

void EnemyHealthComponent::setDistanceFromPlayer(float hitDistance) {
  m_distanceFromPlayer = hitDistance;
}
