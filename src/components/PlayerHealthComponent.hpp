#pragma once

class PlayerHealthComponent {
  /**
   * @class PlayerHealthComponent
   * @brief Represents a health component for the player character.
   *
   * The PlayerHealthComponent class manages the health and state of the player character in a game.
   * It provides methods to update the current health, retrieve the maximum health, current health, and other state information.
   * The current health is represented as an integer value, and the maximum health is also an integer value.
   * The component tracks the next damage time, indicating when the player can take damage again.
   * It also tracks whether the player is alive, hit, or healed, indicating their current state.
   * The component allows setting and retrieving these states and health values.
   */
private:
  int m_maxHealth;
  int m_currentHealth;

  float m_nextDamageTime;
  bool m_isAlive;
  bool m_isHit;
  bool m_isHealed;

public:
  PlayerHealthComponent(int maxHealth);
  int getMaxHealth() const;
  int getCurrentHealth() const;
  float getNextDamageTime() const;
  bool isAlive() const;
  bool isHit() const;
  bool isHealed() const;

  void updateCurrentHealth(int value);
  void updateNextDamageTime(float value);
  void setNextDamageTime(float newNextDamageTime);
  void setMaxHealth(int newMaxHealth);
  void setCurrentHealth(int newCurrentHealth);
  void setIfIsHit(bool state);
  void setIfIsHealed(bool state);
};