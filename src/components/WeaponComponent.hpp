#pragma once
#include "../../vendor/glm/glm.hpp"
#include "../../vendor/glm/gtx/rotate_vector.hpp"

class WeaponComponent {
private:
  glm::vec3 m_Position;

public:
  WeaponComponent(const glm::vec3 &position);
  glm::vec3 getWeaponPosition() const;
  void setWeaponPosition(glm::vec3 newPosition);
};