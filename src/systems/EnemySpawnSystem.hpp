#pragma once

#include "EntityFactory.hpp"
#include "EntityManager.hpp"

class EnemySpawnSystem {
private:
  EntityManager &m_entityManager;
  EntityFactory &m_entityFactory;
  unsigned int m_maxEnemyAmount;

public:
  EnemySpawnSystem(EntityManager &entityManager, EntityFactory &entityfactory);
  void update(float timeFromBeginning);
};