#pragma once
#include "../../vendor/glm/glm.hpp"
#include "../../vendor/glm/gtx/rotate_vector.hpp"

class WeaponComponent {
private:
  glm::vec3 m_position;

  bool m_weaponRecoilFinished;
  bool m_triggerPressed;
  float m_weaponRecoilTime;
  float m_weaponRecoilAmount;

public:
  WeaponComponent();
  glm::vec3 getWeaponPosition() const;
  bool isTriggerPressed() const;
  bool hasWeaponRecoilFinished() const;
  float getWeaponRecoilTime() const;
  float getWeaponRecoilAmount() const;

  void setIfWeaponRecoilFinished(bool state);
  void setIfTriggerPressed(bool state);
  void setWeaponRecoilTime(float newRecoilTime);
  void updateRecoilTime(float deltaTime);
  void setWeaponPosition(glm::vec3 newPosition);
  void setWeaponRecoilAmount(float newRecoilAmount);
};