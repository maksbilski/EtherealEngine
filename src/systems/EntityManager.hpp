#pragma once
#include "../components/CameraComponent.hpp"
#include "../components/ModelComponent.hpp"
#include "../components/ShaderComponent.hpp"
#include "../components/TransformComponent.hpp"
#include "../components/WeaponComponent.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

typedef uint32_t Entity;

class EntityManager {
private:
  std::unique_ptr<CameraComponent> m_CameraComponent;

  std::unordered_map<Entity, std::unique_ptr<ShaderComponent>>
      m_ShaderComponents;

  std::unordered_map<Entity, std::unique_ptr<ModelComponent>> m_ModelComponents;

  std::unordered_map<Entity, std::unique_ptr<TransformComponent>>
      m_TransformComponents;

  std::unordered_map<Entity, std::unique_ptr<WeaponComponent>>
      m_WeaponComponents;

  std::vector<Entity> m_RenderableEntities;

  Entity m_CurrentWeapon;

  Entity m_nextEntity = 0;

public:
  void addCameraComponent(CameraComponent cameraComponent);

  CameraComponent &getCameraComponent() const;

  template <typename ComponentType>
  void addComponent(Entity entity, ComponentType component);

  Entity getCurrentWeaponEntity() const;

  void setCurrentWeaponEntity(Entity newEntity);

  template <typename ComponentType> ComponentType &getComponent(Entity entity);

  template <typename ComponentType>
  std::unordered_map<Entity, std::unique_ptr<ComponentType>> &getComponentMap();

  void addRenderableEntity(Entity newRenderableEntity) {
    m_RenderableEntities.push_back(newRenderableEntity);
  }

  std::vector<Entity> getEntitesToRender() const;
};

// Template function implementations
template <typename ComponentType>
void EntityManager::addComponent(Entity entity, ComponentType component) {
  std::unordered_map<Entity, std::unique_ptr<ComponentType>> &componentMap =
      getComponentMap<ComponentType>();
  componentMap[entity] = std::make_unique<ComponentType>(std::move(component));
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
  static_assert(std::is_same<ComponentType, ModelComponent>::value ||
                    std::is_same<ComponentType, TransformComponent>::value ||
                    std::is_same<ComponentType, ShaderComponent>::value,
                "Unsupported component type");

  throw std::logic_error("Unsupported component type. This line should never "
                         "be executed. It's here to prevent compiler errors.");
}

template <>
inline std::unordered_map<Entity, std::unique_ptr<ShaderComponent>> &
EntityManager::getComponentMap<ShaderComponent>() {
  return m_ShaderComponents;
}

template <>
inline std::unordered_map<Entity, std::unique_ptr<ModelComponent>> &
EntityManager::getComponentMap<ModelComponent>() {
  return m_ModelComponents;
}

template <>
inline std::unordered_map<Entity, std::unique_ptr<TransformComponent>> &
EntityManager::getComponentMap<TransformComponent>() {
  return m_TransformComponents;
}

template <>
inline std::unordered_map<Entity, std::unique_ptr<WeaponComponent>> &
EntityManager::getComponentMap<WeaponComponent>() {
  return m_WeaponComponents;
}
