#include "EntityManager.hpp"

void EntityManager::addCameraComponent(CameraComponent cameraComponent) {
  m_CameraComponent =
      std::make_unique<CameraComponent>(std::move(cameraComponent));
}

CameraComponent &EntityManager::getCameraComponent() const {
  return *m_CameraComponent;
}

std::vector<Entity> EntityManager::getEntitesToRender() const {
  return m_RenderableEntities;
}
