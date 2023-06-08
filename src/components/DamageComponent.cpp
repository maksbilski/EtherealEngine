#include "DamageComponent.hpp"

DamageComponent::DamageComponent(int damage) : m_damage(damage) {}

int DamageComponent::getDamage() const { return m_damage; }

void DamageComponent::setDamage(int newDamage) { m_damage = newDamage; }