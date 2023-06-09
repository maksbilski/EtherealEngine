#pragma once

#include "EntityManager.hpp"

class EnemyAISystem {
  /**
   * @class EnemyAISystem
   * @brief Manages the AI behavior for enemy entities in a game.
   *
   * The EnemyAISystem class is responsible for managing the AI behavior of
   * enemy entities in a game. It utilizes the EntityManager to access and
   * manipulate enemy entities.
   *
   * The class provides a method to update the AI system, which triggers the AI
   * behavior for each enemy entity. The updateEnemy method is called for each
   * enemy entity, allowing customization and logic specific to each enemy.
   */

private:
  EntityManager &m_entityManager;

  void updateEnemy(Entity enemyEntity);

public:
  EnemyAISystem(EntityManager &entityManager);
  ~EnemyAISystem();
  void update();
};