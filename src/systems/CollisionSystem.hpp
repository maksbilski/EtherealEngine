#pragma once

#include "../vendor/glm/glm.hpp"
#include "EntityManager.hpp"
#include <memory>

class CollisionSystem {
private:
  EntityManager &m_entityManager;

  void transformCylinder(Cylinder &cylinder, const glm::vec3 &m_Position,
                         const glm::vec3 &m_Scale) const;

  std::optional<glm::vec3> checkCylinderCollision(const Cylinder &cylinder1,
                                                  const Cylinder &cylinder2,
                                                  Entity entity1,
                                                  Entity entity2) const;

  void handleCollision(const glm::vec3 &overlap, Entity entity1,
                       Entity entity2) const;

public:
  CollisionSystem(EntityManager &EntityManger);
  ~CollisionSystem();
  void update() const;
};