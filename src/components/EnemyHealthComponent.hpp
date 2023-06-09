#pragma once

class EnemyHealthComponent {
private:
  int m_maxHealth;
  int m_currentHealth;

  bool m_isAlive;
  bool m_isOnCrosshair;
  float m_distanceFromPlayer;

  void updateCurrentHealth(int value);

public:
  EnemyHealthComponent(int maxHealth);
  int getMaxHealth() const;
  int getCurrentHealth() const;
  bool isAlive() const;
  bool isOnCrosshair() const;

  void setDistanceFromPlayer(float hitDistance);
  void setMaxHealth(int newMaxHealth);
  void setCurrentHealth(int newCurrentHealth);
  void setIfIsOnCrosshair(bool state);
};