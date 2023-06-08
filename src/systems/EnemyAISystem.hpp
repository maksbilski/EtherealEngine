#pragma once

#include "EntityManager.hpp"

class EnemyAISystem {
private:
  EntityManager &m_entityManager;

  void updateEnemy(Entity enemyEntity);

public:
  EnemyAISystem(EntityManager &entityManager);
  ~EnemyAISystem();
  void update();
};