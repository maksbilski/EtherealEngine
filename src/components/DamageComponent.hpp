#pragma once

class DamageComponent {
private:
  int m_damage;

public:
  DamageComponent(int damage);
  int getDamage() const;
  void setDamage(int newDamage);
};