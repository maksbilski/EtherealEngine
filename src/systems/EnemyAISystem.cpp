#include "EnemyAISystem.hpp"

const float ENEMY_MOVEMENT_SPEED = 175.0f;

const float ONE_FRAME = 1.0f / 70.0f;

EnemyAISystem::EnemyAISystem(EntityManager &entityManager)
    : m_entityManager(entityManager) {}

EnemyAISystem::~EnemyAISystem() {}

void EnemyAISystem::update() {
  for (auto entity : m_entityManager.getEnemyEntities()) {
    updateEnemy(entity);
  }
}

void EnemyAISystem::updateEnemy(Entity enemyEntity) {
  glm::vec3 movementVector(0.0f);
  TransformComponent &player = m_entityManager.getComponent<TransformComponent>(
      m_entityManager.getPlayerEntity());
  TransformComponent &enemy =
      m_entityManager.getComponent<TransformComponent>(enemyEntity);

  glm::vec3 enemyMovementDirection =
      glm::normalize(player.getPosition() - enemy.getPosition());

  movementVector += enemyMovementDirection * ENEMY_MOVEMENT_SPEED * ONE_FRAME;

  float enemyRotationAngle =
      atan2f(enemyMovementDirection.z, enemyMovementDirection.x);

  enemyRotationAngle = glm::degrees(enemyRotationAngle);

  enemy.setRotation(-glm::vec3(0.0f, enemyRotationAngle - 90.0f, 0.0f));

  enemy.updatePosition(movementVector);
}
