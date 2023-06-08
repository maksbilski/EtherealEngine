#include "EntityManager.hpp"

void EntityManager::addCameraComponent(CameraComponent cameraComponent) {
  m_cameraComponent =
      std::make_unique<CameraComponent>(std::move(cameraComponent));
}

CameraComponent &EntityManager::getCameraComponent() const {
  return *m_cameraComponent;
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

<<<<<<< HEAD
std::vector<Entity> EntityManager::getTargetableEntites() const {
  return m_targetableEntities;
};
=======
std::vector<Entity> EntityManager::getEnemyEntities() const {
  return m_enemyEntities;
}
>>>>>>> 1f1d6651dd6dd15ac440f0f8bc77f3ed712fcbcb

Entity EntityManager::getCurrentSkyboxEntity() const { return m_currentSkybox; }

void EntityManager::addRenderableEntity(Entity newRenderableEntity) {
  m_renderableEntities.push_back(newRenderableEntity);
}

<<<<<<< HEAD
void EntityManager::addTargetableEntity(Entity newTargetableEntity) {
  m_targetableEntities.push_back(newTargetableEntity);
=======
void EntityManager::addCollidableEntity(Entity newCollidableEntity) {
  m_collidableEntities.push_back(newCollidableEntity);
>>>>>>> 1f1d6651dd6dd15ac440f0f8bc77f3ed712fcbcb
}

void EntityManager::addSkyboxEntity(Entity newSkyboxEntity) {
  m_skyboxEntities.push_back(newSkyboxEntity);
  m_currentSkybox = newSkyboxEntity;
}

void EntityManager::addEnemyEntity(Entity newEnemyEntity) {
  m_enemyEntities.push_back(newEnemyEntity);
}