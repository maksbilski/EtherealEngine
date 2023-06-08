#pragma once

class HealthComponent {
private:
  int m_maxHealth;
  int m_currentHealth;

  bool m_isAlive;

public:
  HealthComponent(int maxHealth);
  int getMaxHealth() const;
  int getCurrentHealth() const;
  bool isAlive() const;

  void updateCurrentHealth(int value);
  void setMaxHealth(int newMaxHealth);
  void setCurrentHealth(int newCurrentHealth);
};