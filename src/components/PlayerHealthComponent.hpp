#pragma once

class PlayerHealthComponent {
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