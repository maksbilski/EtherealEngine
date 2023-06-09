#pragma once

#include "EntityManager.hpp"
#include "ResourceManager.hpp"

class EntityFactory {
private:
  EntityManager &m_entityManager;
  ResourceManager &m_resourceManager;
  Entity m_nextEntity = 0;

  Entity getNewEntityId();
  Entity createCrosshairEntity();

public:
  EntityFactory(EntityManager &entityManager, ResourceManager &resourceManager);
  Entity createRenderableEntity(EntityType entityType,
                                glm::vec3 position = glm::vec3(0.0f),
                                glm::vec3 rotation = glm::vec3(0.0f),
                                glm::vec3 scale = glm::vec3(1.0f));

  Entity createWeaponEntity(EntityType entityType,
                            glm::vec3 scale = glm::vec3(1.0f));
  Entity createPlayerEntity(glm::vec3 position, glm::vec3 rotation,
                            glm::vec3 scale);
  Entity createEnemyEntity(EntityType entityType, glm::vec3 position,
                           glm::vec3 scale);
  void createSkyboxEntity();
  void createRandomRenderableEntities(EntityType entityType,
                                      unsigned int amount);
  void createRandomEnemyEntities(EntityType entityType, unsigned int amount);
  float generateRandomFloat(float lower, float upper);
};