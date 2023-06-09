#pragma once

#include "../vendor/glm/glm.hpp"
#include "EntityManager.hpp"
#include <memory>

struct Ray {
  glm::vec3 origin;
  glm::vec3 direction;
};

class CollisionSystem {
private:
  EntityManager &m_entityManager;

  void transformCylinder(Cylinder &cylinder, const glm::vec3 &m_Position,
                         const glm::vec3 &m_Scale) const;

  void transformSphere(Sphere &sphere, const glm::vec3 &m_Position,
                       const glm::vec3 &m_Scale) const;

  std::optional<glm::vec3> checkCylinderCollision(const Cylinder &cylinder1,
                                                  const Cylinder &cylinder2,
                                                  Entity entity1,
                                                  Entity entity2) const;

  bool checkRaySphereCollision(const Ray &ray, const Sphere &sphere) const;

  void handleCollision(const glm::vec3 &overlap, Entity entity1,
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