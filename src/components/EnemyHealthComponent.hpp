#pragma once

class EnemyHealthComponent {
private:
  int m_maxHealth;
  int m_currentHealth;

  bool m_isAlive;
  bool m_isOnCrosshair;

public:
  EnemyHealthComponent(int maxHealth);
  int getMaxHealth() const;
  int getCurrentHealth() const;
  bool isAlive() const;
  bool isOnCrosshair() const;

  void updateCurrentHealth(int value);
  void setMaxHealth(int newMaxHealth);
  void setCurrentHealth(int newCurrentHealth);
  void setIfIsOnCrosshair(bool state);
};