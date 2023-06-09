#define CATCH_CONFIG_MAIN
#include "../components/WeaponComponent.hpp"
#include "catch.hpp"

TEST_CASE("Weapon Component Tests", "[WeaponComponent]") {
  WeaponComponent wc;

  SECTION("Initial values") {
    REQUIRE(wc.isTriggerPressed() == false);
    REQUIRE(wc.hasWeaponRecoilFinished() == false);
    REQUIRE(wc.getWeaponRecoilTime() == Approx(WEAPON_ANIMATION_TIME));
    REQUIRE(wc.getWeaponRecoilAmount() == Approx(0.0f));
    REQUIRE(wc.getWeaponBob() == Approx(0.0f));
    REQUIRE(wc.getWeaponBobAmount() == Approx(0.0f));
  }

  SECTION("Setting and getting trigger pressed") {
    wc.setIfTriggerPressed(true);
    REQUIRE(wc.isTriggerPressed() == true);
  }

  SECTION("Setting and getting weapon recoil finished") {
    wc.setIfWeaponRecoilFinished(true);
    REQUIRE(wc.hasWeaponRecoilFinished() == true);
  }

  SECTION("Setting and getting weapon recoil time") {
    wc.setWeaponRecoilTime(2.0f);
    REQUIRE(wc.getWeaponRecoilTime() == Approx(2.0f));
  }

  SECTION("Updating recoil time") {
    wc.updateRecoilTime(1.0f);
    REQUIRE(wc.getWeaponRecoilTime() == Approx(WEAPON_ANIMATION_TIME + 1.0f));
  }

  SECTION("Setting and getting weapon recoil amount") {
    wc.setWeaponRecoilAmount(1.5f);
    REQUIRE(wc.getWeaponRecoilAmount() == Approx(1.5f));
  }

  SECTION("Setting and getting weapon bob") {
    wc.setWeaponBob(2.5f);
    REQUIRE(wc.getWeaponBob() == Approx(2.5f));
  }

  SECTION("Updating weapon bob") {
    wc.updateWeaponBob(1.5f);
    REQUIRE(wc.getWeaponBob() == Approx(1.5f));
  }

  SECTION("Setting and getting weapon bob amount") {
    wc.setWeaponBobAmount(3.0f);
    REQUIRE(wc.getWeaponBobAmount() == Approx(3.0f));
  }
}
