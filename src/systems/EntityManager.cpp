#include "EntityManager.hpp"

void EntityManager::addCameraComponent(CameraComponent cameraComponent) {
  m_CameraComponent =
      std::make_unique<CameraComponent>(std::move(cameraComponent));
}

CameraComponent &EntityManager::getCameraComponent() const {
  return *m_CameraComponent;
}

std::vector<Entity> EntityManager::getEntitesToRender() const {
  std::vector<Entity> validEntities;

  for (auto &unorderedMapPair : m_GraphicsComponents) {
    if (m_TransformComponents.count(unorderedMapPair.first) > 0)
      validEntities.push_back(unorderedMapPair.first);
  }
  return validEntities;
}
