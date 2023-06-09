#pragma once

#include "EntityFactory.hpp"
#include "EntityManager.hpp"

class EnemySpawnSystem {
  /**
   * @class EnemySpawnSystem
   * @brief Manages the spawning of enemy entities in a game.
   *
   * The EnemySpawnSystem class is responsible for managing the spawning of
   * enemy entities in a game. It utilizes the EntityManager and EntityFactory
   * to create and manage entities.
   *
   * The class provides a method to update the spawn system, which calculates
   * the number of enemies to spawn based on the time from the beginning of the
   * game. The update method should be called regularly to update the spawning
   * logic.
   *
   * The amount of enemies to spawn increases over time, resulting in a larger
   * number of enemies each minute. The maximum number of enemies that can be
   * spawned is determined by the linear function (1/60 * timeFromBeginning + 8)
   */

private:
  EntityManager &m_entityManager;
  EntityFactory &m_entityFactory;
  unsigned int m_maxEnemyAmount;

public:
  EnemySpawnSystem(EntityManager &entityManager, EntityFactory &entityfactory);
  void update(float timeFromBeginning);
};