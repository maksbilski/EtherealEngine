#pragma once

#include "../vendor/glm/glm.hpp"
#include "EntityManager.hpp"
#include <memory>

struct Ray {
  glm::vec3 origin;
  glm::vec3 direction;
};

class CollisionSystem {
  /**
   * @class CollisionSystem
   * @brief Manages collision detection and response for entities in a game.
   *
   * The CollisionSystem class handles collision detection and response between
   * entities in a game. It utilizes the EntityManager to access and manipulate
   * entities.
   *
   * The class provides methods to update the collision system, which performs
   * collision detection and response calculations. It supports physical
   * collision between entities represented by cylinders and ray collision, if
   * the player targets the collidable entity represented by sphere.
   *
   * The collision system transforms the cylinder and sphere bounding shapes of
   * entities based on their position and scale. It checks for collisions
   * and handles the resulting collision response by resolving overlaps.
   * Additionally, the system handles collisions between rays and spheres,
   * updating the rays and detecting hits.
   *
   * The update method should be called regularly to perform collision detection
   * and response calculations.
   *
   * Note: The class assumes the usage of the glm library for mathematical
   * operations.
   */

private:
  EntityManager &m_entityManager;

  void transformCylinder(Cylinder &cylinder, const glm::vec3 &m_Position,
                         const glm::vec3 &m_Scale) const;

  void transformSphere(Sphere &sphere, const glm::vec3 &m_Position,
                       const glm::vec3 &m_Scale) const;

  std::optional<glm::vec3>
  checkCylinderCollision(const Cylinder &cylinder1,
                         const Cylinder &cylinder2) const;

  bool checkRaySphereCollision(const Ray &ray, const Sphere &sphere) const;

  void handleEntityCollision(const glm::vec3 &overlap, Entity entity1,
                             Entity entity2) const;

  void handleRayCollision(Ray &ray, const Sphere &sphere,
                          const Entity &entity) const;

  void controlEntitiesCollision() const;

  void controlRayCollision();

  unsigned int m_rayHitCount = 0;

public:
  CollisionSystem(EntityManager &EntityManger);
  ~CollisionSystem();
  void update();
};