#include "WeaponComponent.hpp"

WeaponComponent::WeaponComponent(const glm::vec3 &position)
    : m_Position(position) {}

glm::vec3 WeaponComponent::getWeaponPosition() const { return m_Position; }

void WeaponComponent::setWeaponPosition(glm::vec3 newPosition) {
  m_Position = newPosition;
}