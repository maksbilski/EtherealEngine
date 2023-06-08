#include "CollisionSystem.hpp"
#include <algorithm>

CollisionSystem::CollisionSystem(EntityManager &entityManager)
    : m_entityManager(entityManager){};

CollisionSystem::~CollisionSystem() {}

void CollisionSystem::update() {
  controlEntitiesCollision();
  // controlRayCollision();
}

void CollisionSystem::controlEntitiesCollision() const {
  std::vector<Entity> collidableEntities =
      m_entityManager.getCollidableEntites();

  for (size_t i = 0; i < collidableEntities.size(); i++) {
    // Get Cylinder and TransformComponent of the first entity
    Cylinder cylinder1 =
        m_entityManager.getComponent<ModelComponent>(collidableEntities[i])
            .m_model->getBoundingCylinder();
    TransformComponent transform1 =
        m_entityManager.getComponent<TransformComponent>(collidableEntities[i]);

    // Transform the bounding cylinder of the first entity
    transformCylinder(cylinder1, transform1.getPosition(),
                      transform1.getScale());

    for (size_t j = i + 1; j < collidableEntities.size(); j++) {
      // Get Cylinder and TransformComponent of the second entity
      Cylinder cylinder2 =
          m_entityManager.getComponent<ModelComponent>(collidableEntities[j])
              .m_model->getBoundingCylinder();
      TransformComponent transform2 =
          m_entityManager.getComponent<TransformComponent>(
              collidableEntities[j]);

      // Transform the bounding cylinder of the second entity
      transformCylinder(cylinder2, transform2.getPosition(),
                        transform2.getScale());

      // Check for collision between the two bounding cylinders
      std::optional<glm::vec3> overlap = checkCylinderCollision(
          cylinder1, cylinder2, collidableEntities[i], collidableEntities[j]);
      if (overlap) {
        handleCollision(*overlap, collidableEntities[i], collidableEntities[j]);
      }
    }
  }
}

void CollisionSystem::transformCylinder(Cylinder &cylinder,
                                        const glm::vec3 &m_Position,
                                        const glm::vec3 &m_Scale) const {
  // Translation
  cylinder.center += m_Position;

  // Scaling
  cylinder.radius *= std::max(m_Scale.x, m_Scale.z); // Assuming uniform scaling
  cylinder.height *= m_Scale.y;                      // Assuming uniform scaling
}

std::optional<glm::vec3>
CollisionSystem::checkCylinderCollision(const Cylinder &cylinder1,
                                        const Cylinder &cylinder2,
                                        Entity entity1, Entity entity2) const {
  // Calculate the distance between the centers of the two cylinders in the x-z
  // plane
  glm::vec3 distanceVec = cylinder1.center - cylinder2.center;
  distanceVec.y = 0; // ignore the y component of the distance

  float horizontalDistance = glm::length(distanceVec);

  // Check if the distance is less than the sum of their radii (for horizontal
  // collision)
  if (horizontalDistance < (cylinder1.radius + cylinder2.radius)) {
    // Check if the vertical distance is less than the sum of their half heights
    // (for vertical collision)
    float verticalDistance = abs(cylinder1.center.y - cylinder2.center.y);
    if (verticalDistance < ((cylinder1.height + cylinder2.height) / 2)) {
      // Calculate overlap
      glm::vec3 overlap =
          distanceVec * 0.15f; // Assuming no overlap in z direction
      return overlap;
    }
  }

  return std::nullopt;
};

void CollisionSystem::handleCollision(const glm::vec3 &overlap, Entity entity1,
                                      Entity entity2) const {
  TransformComponent &transform1 =
      m_entityManager.getComponent<TransformComponent>(entity1);
  TransformComponent &transform2 =
      m_entityManager.getComponent<TransformComponent>(entity2);

  // Move each entity half the overlap distance in opposite directions
  transform1.setPosition(transform1.getPosition() + overlap / 2.0f);
  transform2.setPosition(transform2.getPosition() - overlap / 2.0f);
}

// void CollisionSystem::controlRayCollision() const {

// }