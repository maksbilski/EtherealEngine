#include "EntityManager.hpp"

void EntityManager::addCameraComponent(CameraComponent cameraComponent) {
  m_cameraComponent =
      std::make_unique<CameraComponent>(std::move(cameraComponent));
}

CameraComponent &EntityManager::getCameraComponent() const {
  return *m_cameraComponent;
}

Entity EntityManager::getCurrentWeaponEntity() const { return m_currentWeapon; }

void EntityManager::setCurrentWeaponEntity(Entity newEntity) {
  m_currentWeapon = newEntity;
}

std::vector<Entity> EntityManager::getEntitesToRender() const {
  return m_renderableEntities;
}

Entity EntityManager::getCurrentSkyboxEntity() const { return m_currentSkybox; }