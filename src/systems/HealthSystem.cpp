#include "HealthSystem.hpp"

HealthSystem::HealthSystem(EntityManager &entityManager)
    : m_entityManager(entityManager) {}

void HealthSystem::update() {
  updatePlayerHealth();
  for (auto entity : m_entityManager.getEnemyEntities()) {
    updateEnemyHealth(entity);
  }
}

void HealthSystem::updateEnemyHealth(Entity enemyEntity) {
  EnemyHealthComponent &enemy =
      m_entityManager.getComponent<EnemyHealthComponent>(enemyEntity);
  if (enemy.isShot()) {
    return;
  }
}