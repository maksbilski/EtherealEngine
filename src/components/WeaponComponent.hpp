#pragma once
#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtx/rotate_vector.hpp"

const float WEAPON_ANIMATION_TIME = 1.0f;

class WeaponComponent {
private:
  bool m_weaponRecoilFinished;
  bool m_triggerPressed;
  float m_weaponRecoilTime;
  float m_weaponRecoilAmount;
  float m_weaponBob;
  float m_weaponBobAmount;

public:
  WeaponComponent();
  bool isTriggerPressed() const;
  bool hasWeaponRecoilFinished() const;
  float getWeaponRecoilTime() const;
  float getWeaponRecoilAmount() const;
  float getWeaponBob() const;
  float getWeaponBobAmount() const;

  void setIfWeaponRecoilFinished(bool state);
  void setIfTriggerPressed(bool state);
  void setWeaponRecoilTime(float newRecoilTime);
  void updateRecoilTime(float deltaTime);
  void setWeaponRecoilAmount(float newRecoilAmount);
  void setWeaponBob(float newWeaponBob);
  void updateWeaponBob(float updateValue);
  void setWeaponBobAmount(float newWeaponBobAmount);
};