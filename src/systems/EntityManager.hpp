#pragma once
#include "../components/CameraComponent.hpp"
#include "../components/GraphicsComponent.hpp"
#include "../components/TransformComponent.hpp"
#include <memory>
#include <string>
#include <vector>

typedef uint32_t Entity;

class EntityManager {
private:
  std::unique_ptr<CameraComponent> m_CameraComponent;
  std::unordered_map<Entity, std::unique_ptr<GraphicsComponent>>
      m_GraphicsComponents;
  std::unordered_map<Entity, std::unique_ptr<TransformComponent>>
      m_TransformComponents;

  Entity m_nextEntity = 0;

public:
  void addCameraComponent(CameraComponent cameraComponent);

  template <typename ComponentType>
  void addComponent(Entity entity, ComponentType component);

  CameraComponent &getCameraComponent() const;

  template <typename ComponentType> ComponentType &getComponent(Entity entity);

  template <typename ComponentType>
  std::unordered_map<Entity, std::unique_ptr<ComponentType>> &getComponentMap();

  std::vector<Entity> getEntitesToRender() const;
};