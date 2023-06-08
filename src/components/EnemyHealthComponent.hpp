#pragma once

class EnemyHealthComponent {
private:
  int m_maxHealth;
  int m_currentHealth;

  bool m_isAlive;
  bool m_isShot;

public:
  EnemyHealthComponent(int maxHealth);
  int getMaxHealth() const;
  int getCurrentHealth() const;
  bool isAlive() const;
  bool isShot() const;

  void updateCurrentHealth(int value);
  void setMaxHealth(int newMaxHealth);
  void setCurrentHealth(int newCurrentHealth);
  void setIfIsShot(bool state);
};