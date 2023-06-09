#define CATCH_CONFIG_MAIN

#include "../src/components/EnemyHealthComponent.hpp"
#include "catch.hpp"

TEST_CASE("Enemy Health Component Tests", "[EnemyHealthComponent]") {
  SECTION("Construction") {
    EnemyHealthComponent e(100);
    REQUIRE(e.getMaxHealth() == 100);
    REQUIRE(e.getCurrentHealth() == 100);
    REQUIRE(e.isAlive() == true);
    REQUIRE(e.isOnCrosshair() == false);
    REQUIRE(e.getDistanceFromPlayer() == Approx(0.0f));
  }

  SECTION("Setting and getting maximum health") {
    EnemyHealthComponent e(100);
    e.setMaxHealth(150);
    REQUIRE(e.getMaxHealth() == 150);
  }

  SECTION("Setting and getting current health") {
    EnemyHealthComponent e(100);
    e.setCurrentHealth(80);
    REQUIRE(e.getCurrentHealth() == 80);
  }

  SECTION("Updating current health") {
    EnemyHealthComponent e(100);
    e.updateCurrentHealth(-20);
    REQUIRE(e.getCurrentHealth() == 80);
    REQUIRE(e.isAlive() == true);
  }

  SECTION("Killing enemy") {
    EnemyHealthComponent e(100);
    e.updateCurrentHealth(-100);
    REQUIRE(e.getCurrentHealth() == 0);
    REQUIRE(e.isAlive() == false);
  }

  SECTION("Setting and getting crosshair status") {
    EnemyHealthComponent e(100);
    e.setIfIsOnCrosshair(true);
    REQUIRE(e.isOnCrosshair() == true);
    e.setIfIsOnCrosshair(false);
    REQUIRE(e.isOnCrosshair() == false);
  }

  SECTION("Setting and getting distance from player") {
    EnemyHealthComponent e(100);
    e.setDistanceFromPlayer(15.0f);
    REQUIRE(e.getDistanceFromPlayer() == Approx(15.0f));
  }
}
