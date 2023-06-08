#include "HealthComponent.hpp"

HealthComponent::HealthComponent(int maxHealth) : m_maxHealth(maxHealth) {
  m_currentHealth = maxHealth;
  m_isAlive = true;
}

int HealthComponent::getMaxHealth() const { return m_maxHealth; }

int HealthComponent::getCurrentHealth() const { return m_currentHealth; }

bool HealthComponent::isAlive() const { return m_isAlive; }

void HealthComponent::updateCurrentHealth(int value) {
  m_currentHealth += value;

  if (m_currentHealth > m_maxHealth) {
    m_currentHealth = m_maxHealth;
  } else if (m_currentHealth < 0) {
    m_currentHealth = 0;
    m_isAlive = false;
  }
}

void HealthComponent::setMaxHealth(int newMaxHealth) {
  m_maxHealth = newMaxHealth;
}

void HealthComponent::setCurrentHealth(int newCurrentHealth) {
  m_currentHealth = newCurrentHealth;
}