#define CATCH_CONFIG_MAIN

#include "../src/components/PlayerHealthComponent.hpp"
#include "catch.hpp"

TEST_CASE("Player Health Component Tests", "[PlayerHealthComponent]") {
  SECTION("Construction") {
    PlayerHealthComponent p(100);
    REQUIRE(p.getMaxHealth() == 100);
    REQUIRE(p.getCurrentHealth() == 100);
    REQUIRE(p.isAlive() == true);
    REQUIRE(p.isHit() == false);
    REQUIRE(p.isHealed() == false);
    REQUIRE(p.getNextDamageTime() == Approx(0.0f));
  }

  SECTION("Setting and getting maximum health") {
    PlayerHealthComponent p(100);
    p.setMaxHealth(150);
    REQUIRE(p.getMaxHealth() == 150);
  }

  SECTION("Setting and getting current health") {
    PlayerHealthComponent p(100);
    p.setCurrentHealth(80);
    REQUIRE(p.getCurrentHealth() == 80);
  }

  SECTION("Updating current health") {
    PlayerHealthComponent p(100);
    p.updateCurrentHealth(-20);
    REQUIRE(p.getCurrentHealth() == 80);
    REQUIRE(p.isAlive() == true);
  }

  SECTION("Killing player") {
    PlayerHealthComponent p(100);
    p.updateCurrentHealth(-100);
    REQUIRE(p.getCurrentHealth() == 0);
    REQUIRE(p.isAlive() == false);
  }

  SECTION("Setting and getting hit status") {
    PlayerHealthComponent p(100);
    p.setIfIsHit(true);
    REQUIRE(p.isHit() == true);
    p.setIfIsHit(false);
    REQUIRE(p.isHit() == false);
  }

  SECTION("Setting and getting healed status") {
    PlayerHealthComponent p(100);
    p.setIfIsHealed(true);
    REQUIRE(p.isHealed() == true);
    p.setIfIsHealed(false);
    REQUIRE(p.isHealed() == false);
  }

  SECTION("Setting and getting next damage time") {
    PlayerHealthComponent p(100);
    p.setNextDamageTime(1.5f);
    REQUIRE(p.getNextDamageTime() == Approx(1.5f));
    p.updateNextDamageTime(0.5f);
    REQUIRE(p.getNextDamageTime() == Approx(2.0f));
  }
}
