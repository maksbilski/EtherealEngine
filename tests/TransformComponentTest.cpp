#define CATCH_CONFIG_MAIN

#include "../src/components/TransformComponent.hpp"
#include "../src/vendor/glm/glm.hpp"
#include "catch.hpp"

TEST_CASE("Transform Component Tests", "[TransformComponent]") {
  glm::vec3 initialPosition(0.0f, 0.0f, 0.0f);
  glm::vec3 initialRotation(0.0f, 0.0f, 0.0f);
  glm::vec3 initialScale(1.0f, 1.0f, 1.0f);

  TransformComponent t(initialPosition, initialRotation, initialScale);

  SECTION("Initial values") {
    REQUIRE(t.getPosition() == initialPosition);
    REQUIRE(t.getRotation() == initialRotation);
    REQUIRE(t.getScale() == initialScale);
  }

  SECTION("Setting and getting position") {
    t.setPosition(glm::vec3(1.0f, 2.0f, 3.0f));
    REQUIRE(t.getPosition() == glm::vec3(1.0f, 2.0f, 3.0f));
  }

  SECTION("Setting and getting rotation") {
    t.setRotation(glm::vec3(90.0f, 180.0f, 270.0f));
    REQUIRE(t.getRotation() == glm::vec3(90.0f, 180.0f, 270.0f));
  }

  SECTION("Setting and getting scale") {
    t.setScale(glm::vec3(2.0f, 3.0f, 4.0f));
    REQUIRE(t.getScale() == glm::vec3(2.0f, 3.0f, 4.0f));
  }

  SECTION("Updating position") {
    t.updatePosition(glm::vec3(1.0f, 1.0f, 1.0f));
    REQUIRE(t.getPosition() == glm::vec3(1.0f, 1.0f, 1.0f));
  }

  SECTION("Creating transform matrix") {
    glm::mat4 transform = t.createTransformMatrix();
    glm::mat4 expectedTransform = glm::mat4(1.0f);

    for (int i = 0; i < 4; ++i)
      for (int j = 0; j < 4; ++j)
        REQUIRE(transform[i][j] == Approx(expectedTransform[i][j]));
  }
}
