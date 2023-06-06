#include "EntityManager.hpp"

void EntityManager::addCameraComponent(CameraComponent cameraComponent) {
  m_CameraComponent =
      std::make_unique<CameraComponent>(std::move(cameraComponent));
}

CameraComponent &EntityManager::getCameraComponent() const {
  return *m_CameraComponent;
}

Entity EntityManager::getCurrentWeaponEntity() const { return m_CurrentWeapon; }

void EntityManager::setCurrentWeaponEntity(Entity newEntity) {
  m_CurrentWeapon = newEntity;
}

std::vector<Entity> EntityManager::getEntitesToRender() const {
  return m_RenderableEntities;
}

Entity EntityManager::getCurrentSkyboxEntity() const { return m_CurrentSkybox; }