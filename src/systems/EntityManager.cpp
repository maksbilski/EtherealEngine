#include "EntityManager.hpp"

void EntityManager::addCameraComponent(CameraComponent cameraComponent) {
  m_CameraComponent =
      std::make_unique<CameraComponent>(std::move(cameraComponent));
}

template <typename ComponentType>
void EntityManager::addComponent(Entity entity, ComponentType component) {
  std::unordered_map<Entity, std::unique_ptr<ComponentType>> &componentMap =
      getComponentMap<ComponentType>();
  componentMap[entity] = std::make_unique<ComponentType>(std::move(component));
}

CameraComponent &EntityManager::getCameraComponent() const {
  return *m_CameraComponent;
}

template <typename ComponentType>
ComponentType &EntityManager::getComponent(Entity entity) {
  std::unordered_map<Entity, std::unique_ptr<ComponentType>> &componentMap =
      getComponentMap<ComponentType>();
  return *(componentMap[entity]);
}

template <typename ComponentType>
std::unordered_map<Entity, std::unique_ptr<ComponentType>> &
EntityManager::getComponentMap() {
  static_assert(std::is_same<ComponentType, GraphicsComponent>::value ||
                    std::is_same<ComponentType, TransformComponent>::value,
                "Unsupported component type");

  throw std::logic_error("Unsupported component type. This line should never "
                         "be executed. It's here to prevent compiler errors.");
}

template <>
std::unordered_map<Entity, std::unique_ptr<GraphicsComponent>> &
EntityManager::getComponentMap<GraphicsComponent>() {
  return m_GraphicsComponents;
}

template <>
std::unordered_map<Entity, std::unique_ptr<TransformComponent>> &
EntityManager::getComponentMap<TransformComponent>() {
  return m_TransformComponents;
}

std::vector<Entity> EntityManager::getEntitesToRender() const {
  std::vector<Entity> validEntities;

  for (auto &unorderedMapPair : m_GraphicsComponents) {
    if (m_TransformComponents.count(unorderedMapPair.first) > 0)
      validEntities.push_back(unorderedMapPair.first);
  }
  return validEntities;
}
