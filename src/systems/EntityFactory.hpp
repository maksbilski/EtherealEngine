#pragma once

#include "EntityManager.hpp"
#include "ResourceManager.hpp"

class EntityFactory {
  /**
   * @class EntityFactory
   * @brief Provides functionality to create entities in a game.
   *
   * The EntityFactory class is responsible for creating entities in a game.
   * It utilizes the EntityManager and ResourceManager to manage entities and
   * resources.
   *
   * The class provides methods to create different types of entities, such as
   * renderable entities, weapon entities, player entities, enemy entities, and
   * skybox entities. It also includes methods to create multiple entities at
   * once.
   *
   * The createRenderableEntity method creates a renderable entity of the
   * specified entity type, with the given position, rotation, and scale. The
   * createWeaponEntity method creates a weapon entity of the specified entity
   * type, with the given scale. The createPlayerEntity method creates a player
   * entity with the specified position, rotation, and scale. The
   * createEnemyEntity method creates an enemy entity of the specified entity
   * type, with the given position and scale. The createSkyboxEntity method
   * creates a skybox entity. The createRandomRenderableEntities method creates
   * a specified amount of random renderable entities of the specified entity
   * type. The createRandomEnemyEntities method creates a specified amount of
   * random enemy entities of the specified entity type. The generateRandomFloat
   * method generates a random floating-point number within the specified range.
   */

private:
  EntityManager &m_entityManager;
  ResourceManager &m_resourceManager;
  Entity m_nextEntity = 0;

  Entity getNewEntityId();

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