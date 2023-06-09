#pragma once

class EnemyHealthComponent {
private:
  int m_maxHealth;
  int m_currentHealth;

  bool m_isAlive;
  bool m_isOnCrosshair;
  float m_distanceFromPlayer;

public:
  EnemyHealthComponent(int maxHealth);
  int getMaxHealth() const;
  int getCurrentHealth() const;
  bool isAlive() const;
  bool isOnCrosshair() const;
  float getDistanceFromPlayer() const;

  void updateCurrentHealth(int value);
  void setDistanceFromPlayer(float hitDistance);
  void setMaxHealth(int newMaxHealth);
  void setCurrentHealth(int newCurrentHealth);
  void setIfIsOnCrosshair(bool state);
};