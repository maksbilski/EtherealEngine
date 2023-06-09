#pragma once

class EnemyHealthComponent {
  /**
   * @class EnemyHealthComponent
   * @brief Represents a health component for an enemy character.
   *
   * The EnemyHealthComponent class manages the health and state of an enemy
   * character in a game. It provides methods to update the current health,
   * retrieve the maximum health, current health, and other state information.
   * The current health is represented as an integer value, and the maximum
   * health is also an integer value. The component tracks whether the enemy is
   * alive, whether it is on the player's crosshair, and the distance from the
   * player. The distance from the player is used to calculate the damage that
   * the player deals to the enemy. The "is on crosshair" state indicates that a
   * ray collision has occurred between the player's crosshair and enemy.
   */
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