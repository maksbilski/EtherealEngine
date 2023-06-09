#pragma once
#include "EntityManager.hpp"

class HealthSystem {
  /**
   * @class HealthSystem
   * @brief Manages health-related functionality for entities in a game.
   *
   * The HealthSystem class is responsible for managing health-related
   * functionality for entities in a game. It utilizes the EntityManager to
   * access and manipulate entities.
   *
   * The class provides a method to update the health system, which triggers
   * health-related logic for each relevant entity. The updateEnemyHealth method
   * is called for each enemy entity, allowing customization and logic specific
   * to each enemy's health. The updatePlayerHealth method is called to update
   * the player's health.
   *
   * The update method should be called regularly to update the health-related
   * functionality of entities.
   */

private:
  EntityManager &m_entityManager;

  void updateEnemyHealth(Entity enemyEntity);
  void updatePlayerHealth();

public:
  HealthSystem(EntityManager &entityManager);
  void update();
};