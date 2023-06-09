#include "EnemySpawnSystem.hpp"

EnemySpawnSystem::EnemySpawnSystem(EntityManager &entityManager,
                                   EntityFactory &entityfactory)
    : m_entityManager(entityManager), m_entityFactory(entityfactory) {
  m_maxEnemyAmount = 8;
}

void EnemySpawnSystem::update(float timeFromBeginning) {
  m_maxEnemyAmount = ((int)timeFromBeginning / 60.0f) + 8;
  if (m_entityManager.getEnemyEntities().size() < m_maxEnemyAmount) {
    m_entityFactory.createRandomEnemyEntities(
        EntityType::EYEBEAST,
        m_maxEnemyAmount - m_entityManager.getEnemyEntities().size());
  }
}