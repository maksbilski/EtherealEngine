#include "WeaponComponent.hpp"

WeaponComponent::WeaponComponent() {}

glm::vec3 WeaponComponent::getWeaponPosition() const { return m_Position; }

void WeaponComponent::setWeaponPosition(glm::vec3 newPosition) {
  m_Position = newPosition;
}