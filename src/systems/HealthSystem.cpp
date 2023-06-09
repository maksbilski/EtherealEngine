#include "HealthSystem.hpp"

const float MAX_DAMAGE_DISTANCE = 250.0f;
const float MIN_DAMAGE_DISTANCE = 130.0f;
const float ONE_FRAME = 1.0f / 160.0f;

HealthSystem::HealthSystem(EntityManager &entityManager)
    : m_entityManager(entityManager) {}

void HealthSystem::update() {
  updatePlayerHealth();
  for (auto entity : m_entityManager.getEnemyEntities()) {
    updateEnemyHealth(entity);
  }
}

void HealthSystem::updateEnemyHealth(Entity enemyEntity) {
  WeaponComponent &currentWeapon =
      m_entityManager.getComponent<WeaponComponent>(
          m_entityManager.getCurrentWeaponEntity());
  EnemyHealthComponent &enemy =
      m_entityManager.getComponent<EnemyHealthComponent>(enemyEntity);
  if (enemy.isOnCrosshair() && currentWeapon.isTriggerPressed() &&
      enemy.getDistanceFromPlayer() <= MAX_DAMAGE_DISTANCE) {
    float damageValue;
    damageValue = 100.0f * MIN_DAMAGE_DISTANCE / enemy.getDistanceFromPlayer();
    if (damageValue >= 100.0f)
      damageValue = 100.0f;
    enemy.updateCurrentHealth((int)-damageValue);
    m_entityManager.getComponent<SoundComponent>(enemyEntity).playRandomSound();
    enemy.setIfIsOnCrosshair(false);
  }
  if (!enemy.isAlive()) {
    m_entityManager.removeEnemyEntity(enemyEntity);
  }
}

void HealthSystem::updatePlayerHealth() {
  PlayerHealthComponent &player = m_entityManager.getPlayerHealthComponent();
  player.updateNextDamageTime(-ONE_FRAME);
  if (player.isHit() && player.getNextDamageTime() <= 0) {
    player.updateCurrentHealth(-40);
    m_entityManager
        .getComponent<SoundComponent>(m_entityManager.getPlayerEntity())
        .playRandomSound();
    player.setNextDamageTime(1.0f);
    player.setIfIsHit(false);
  }
}