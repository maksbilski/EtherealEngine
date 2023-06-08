#include "EntityManager.hpp"

void EntityManager::addCameraComponent(CameraComponent cameraComponent) {
  m_cameraComponent =
      std::make_unique<CameraComponent>(std::move(cameraComponent));
}

void EntityManager::addPlayerHealthComponent(
    PlayerHealthComponent playerHealthComponent) {
  m_playerHealthComponent =
      std::make_unique<PlayerHealthComponent>(std::move(playerHealthComponent));
}

CameraComponent &EntityManager::getCameraComponent() const {
  return *m_cameraComponent;
}

PlayerHealthComponent &EntityManager::getPlayerHealthComponent() const {
  return *m_playerHealthComponent;
}

Entity EntityManager::getCurrentWeaponEntity() const { return m_currentWeapon; }

Entity EntityManager::getPlayerEntity() const { return m_playerEntity; }

void EntityManager::setCurrentWeaponEntity(Entity newEntity) {
  m_currentWeapon = newEntity;
}

void EntityManager::setPlayerEntity(Entity newPlayerEntity) {
  m_playerEntity = newPlayerEntity;
}

std::vector<Entity> EntityManager::getEntitesToRender() const {
  return m_renderableEntities;
}

std::vector<Entity> EntityManager::getCollidableEntites() const {
  return m_collidableEntities;
};

std::vector<Entity> EntityManager::getEnemyEntities() const {
  return m_enemyEntities;
}

Entity EntityManager::getCurrentSkyboxEntity() const { return m_currentSkybox; }

void EntityManager::addRenderableEntity(Entity newRenderableEntity) {
  m_renderableEntities.push_back(newRenderableEntity);
}

void EntityManager::addCollidableEntity(Entity newCollidableEntity) {
  m_collidableEntities.push_back(newCollidableEntity);
}

void EntityManager::addSkyboxEntity(Entity newSkyboxEntity) {
  m_skyboxEntities.push_back(newSkyboxEntity);
  m_currentSkybox = newSkyboxEntity;
}

void EntityManager::addEnemyEntity(Entity newEnemyEntity) {
  m_enemyEntities.push_back(newEnemyEntity);
}