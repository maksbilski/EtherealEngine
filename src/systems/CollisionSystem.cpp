#include "CollisionSystem.hpp"
#include <algorithm>

const float DISTANCE_VECTOR_SCALE = 0.15f;

CollisionSystem::CollisionSystem(EntityManager &entityManager)
    : m_entityManager(entityManager){};

CollisionSystem::~CollisionSystem() {}

void CollisionSystem::update() {
  controlEntitiesCollision();
  controlRayCollision();
}

void CollisionSystem::controlEntitiesCollision() const {
  std::vector<Entity> collidableEntities =
      m_entityManager.getCollidableEntites();

  for (size_t i = 0; i < collidableEntities.size(); i++) {
    Cylinder cylinder1 =
        m_entityManager.getComponent<ModelComponent>(collidableEntities[i])
            .m_model->getBoundingCylinder();
    TransformComponent transform1 =
        m_entityManager.getComponent<TransformComponent>(collidableEntities[i]);

    transformCylinder(cylinder1, transform1.getPosition(),
                      transform1.getScale());

    for (size_t j = i + 1; j < collidableEntities.size(); j++) {
      Cylinder cylinder2 =
          m_entityManager.getComponent<ModelComponent>(collidableEntities[j])
              .m_model->getBoundingCylinder();
      TransformComponent transform2 =
          m_entityManager.getComponent<TransformComponent>(
              collidableEntities[j]);

      transformCylinder(cylinder2, transform2.getPosition(),
                        transform2.getScale());

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
  cylinder.center += m_Position;
  cylinder.radius *= std::max(m_Scale.x, m_Scale.z);
  cylinder.height *= m_Scale.y;
}

std::optional<glm::vec3>
CollisionSystem::checkCylinderCollision(const Cylinder &cylinder1,
                                        const Cylinder &cylinder2,
                                        Entity entity1, Entity entity2) const {

  glm::vec3 distanceVec = cylinder1.center - cylinder2.center;
  distanceVec.y = 0; // ignore the y component of the distance

  float horizontalDistance = glm::length(distanceVec);

  if (horizontalDistance < (cylinder1.radius + cylinder2.radius)) {
    float verticalDistance = abs(cylinder1.center.y - cylinder2.center.y);
    if (verticalDistance < ((cylinder1.height + cylinder2.height) / 2)) {
      glm::vec3 overlap = distanceVec * DISTANCE_VECTOR_SCALE;
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

void CollisionSystem::controlRayCollision() {
  std::vector<Entity> targetableEntities =
      m_entityManager.getTargetableEntites();

  glm::vec3 rayOrigin = m_entityManager.getCameraComponent().getPosition();
  glm::vec3 rayDirection = glm::normalize(
      m_entityManager.getCameraComponent().getCameraForwardVec());

  Ray ray = {rayOrigin, rayDirection}; // Define your ray

  for (Entity entity : targetableEntities) {
    Sphere sphere = m_entityManager.getComponent<ModelComponent>(entity)
                        .m_model->getBoundingSphere();

    TransformComponent transform =
        m_entityManager.getComponent<TransformComponent>(entity);

    // Transform the bounding sphere to align with the entity's position
    transformSphere(sphere, transform.getPosition(), transform.getScale());

    if (checkRaySphereCollision(ray, sphere)) {
      // Collision detected, handle accordingly
      std::cout << m_rayHitCount++ << std::endl;
      handleRayCollision(ray, entity);
      break; // Break after first collision detected
    }
  }
}

void CollisionSystem::transformSphere(Sphere &sphere,
                                      const glm::vec3 &m_Position,
                                      const glm::vec3 &m_Scale) const {
  sphere.center += m_Position;
  sphere.radius *= std::max(m_Scale.x, m_Scale.z);
};

bool CollisionSystem::checkRaySphereCollision(const Ray &ray,
                                              const Sphere &sphere) const {

  glm::vec3 originToCenter = sphere.center - ray.origin;

  glm::vec3 rayDirectionNormalized = glm::normalize(ray.direction);

  float projectionLength = glm::dot(originToCenter, rayDirectionNormalized);

  if (projectionLength < 0.0f) {
    return false;
  }

  glm::vec3 closestPointOnRay =
      ray.origin + projectionLength * rayDirectionNormalized;
  glm::vec3 centerToRay = sphere.center - closestPointOnRay;
  float rayToCenterOfSphereDistance = glm::length(centerToRay);

  if (rayToCenterOfSphereDistance > sphere.radius) {
    return false;
  }

  return true;
}

void CollisionSystem::handleRayCollision(Ray &ray, Entity entity) const {}