#pragma once
#include "../components/CameraComponent.hpp"
#include "../components/DamageComponent.hpp"
#include "../components/HealthComponent.hpp"
#include "../components/ModelComponent.hpp"
#include "../components/ShaderComponent.hpp"
#include "../components/SkyboxModelComponent.hpp"
#include "../components/SoundComponent.hpp"
#include "../components/TextureComponent.hpp"
#include "../components/TransformComponent.hpp"
#include "../components/WeaponComponent.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

typedef uint32_t Entity;

class EntityManager {
private:
  std::unique_ptr<CameraComponent> m_cameraComponent;

  std::unordered_map<Entity, std::unique_ptr<ShaderComponent>>
      m_shaderComponents;

  std::unordered_map<Entity, std::unique_ptr<ModelComponent>> m_modelComponents;

  std::unordered_map<Entity, std::unique_ptr<TransformComponent>>
      m_transformComponents;

  std::unordered_map<Entity, std::unique_ptr<WeaponComponent>>
      m_weaponComponents;

  std::unordered_map<Entity, std::unique_ptr<SkyboxModelComponent>>
      m_skyboxModelComponents;

  std::unordered_map<Entity, std::unique_ptr<TextureComponent>>
      m_textureComponents;

  std::unordered_map<Entity, std::unique_ptr<SoundComponent>> m_soundComponents;

  std::unordered_map<Entity, std::unique_ptr<HealthComponent>>
      m_healthComponents;

  std::unordered_map<Entity, std::unique_ptr<DamageComponent>>
      m_damageComponents;

  std::vector<Entity> m_renderableEntities;

  std::vector<Entity> m_skyboxEntities;

  std::vector<Entity> m_collidableEntities;

  std::vector<Entity> m_enemyEntities;

  Entity m_currentWeapon;

  Entity m_playerEntity;

  Entity m_currentSkybox;

  Entity m_nextEntity = 0;

public:
  template <typename ComponentType>
  std::unordered_map<Entity, std::unique_ptr<ComponentType>> &getComponentMap();
  template <typename ComponentType> ComponentType &getComponent(Entity entity);
  CameraComponent &getCameraComponent() const;
  Entity getCurrentWeaponEntity() const;
  Entity getPlayerEntity() const;
  Entity getCurrentSkyboxEntity() const;
  std::vector<Entity> getEntitesToRender() const;
  std::vector<Entity> getCollidableEntites() const;
  std::vector<Entity> getEnemyEntities() const;

  void addCameraComponent(CameraComponent cameraComponent);
  void setCurrentWeaponEntity(Entity newEntity);
  void setPlayerEntity(Entity newPlayerEntity);
  template <typename ComponentType>
  void addComponent(Entity entity, ComponentType component);

  void addRenderableEntity(Entity newRenderableEntity);
  void addCollidableEntity(Entity newCollidableEntity);
  void addSkyboxEntity(Entity newSkyboxEntity);
  void addEnemyEntity(Entity newEnemyEntity);
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

// template <typename ComponentType>
// std::unordered_map<Entity, std::unique_ptr<ComponentType>> &
// EntityManager::getComponentMap() {
//   static_assert(std::is_same<ComponentType, ModelComponent>::value ||
//                     std::is_same<ComponentType, TransformComponent>::value ||
//                     std::is_same<ComponentType, ShaderComponent>::value ||
//                     std::is_same<ComponentType, TextureComponent>::value ||
//                     std::is_same<ComponentType, SkyboxModelComponent>::value,
//                 "Unsupported component type");

//   throw std::logic_error("Unsupported component type. This line should never
//   "
//                          "be executed. It's here to prevent compiler
//                          errors.");
// }

template <>
inline std::unordered_map<Entity, std::unique_ptr<ShaderComponent>> &
EntityManager::getComponentMap<ShaderComponent>() {
  return m_shaderComponents;
}

template <>
inline std::unordered_map<Entity, std::unique_ptr<ModelComponent>> &
EntityManager::getComponentMap<ModelComponent>() {
  return m_modelComponents;
}

template <>
inline std::unordered_map<Entity, std::unique_ptr<TransformComponent>> &
EntityManager::getComponentMap<TransformComponent>() {
  return m_transformComponents;
}

template <>
inline std::unordered_map<Entity, std::unique_ptr<WeaponComponent>> &
EntityManager::getComponentMap<WeaponComponent>() {
  return m_weaponComponents;
}

template <>
inline std::unordered_map<Entity, std::unique_ptr<TextureComponent>> &
EntityManager::getComponentMap<TextureComponent>() {
  return m_textureComponents;
}

template <>
inline std::unordered_map<Entity, std::unique_ptr<SkyboxModelComponent>> &
EntityManager::getComponentMap<SkyboxModelComponent>() {
  return m_skyboxModelComponents;
}

template <>
inline std::unordered_map<Entity, std::unique_ptr<SoundComponent>> &
EntityManager::getComponentMap<SoundComponent>() {
  return m_soundComponents;
}

template <>
inline std::unordered_map<Entity, std::unique_ptr<HealthComponent>> &
EntityManager::getComponentMap<HealthComponent>() {
  return m_healthComponents;
}

template <>
inline std::unordered_map<Entity, std::unique_ptr<DamageComponent>> &
EntityManager::getComponentMap<DamageComponent>() {
  return m_damageComponents;
}
