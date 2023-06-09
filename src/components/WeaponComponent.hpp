#pragma once
#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtx/rotate_vector.hpp"

const float WEAPON_ANIMATION_TIME = 1.0f;

class WeaponComponent {
  /**
   * @class WeaponComponent
   * @brief Represents a component that manages weapon animations and states
   * during the game.
   *
   * The WeaponComponent class is used to handle weapon-related animations and
   * states for a game entity. It provides functionality to manage weapon
   * recoil, trigger presses, weapon bobbing, and related properties. The
   * component tracks various properties, such as whether the weapon recoil
   * animation has finished, whether the trigger is pressed, the duration of the
   * weapon recoil, the amount of recoil applied, the weapon bobbing effect, and
   * the amount of weapon bobbing.
   *
   * The component allows querying and modifying these properties to control the
   * weapon behavior and appearance. It also provides methods to update the
   * recoil time, weapon bobbing, and related properties over time.
   *
   * Note: The constant WEAPON_ANIMATION_TIME represents the default time
   * duration for weapon animations.
   */
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