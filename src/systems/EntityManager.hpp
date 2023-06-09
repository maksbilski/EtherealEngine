#pragma once
#include "../components/CameraComponent.hpp"
#include "../components/EnemyHealthComponent.hpp"
#include "../components/ModelComponent.hpp"
#include "../components/PlayerHealthComponent.hpp"
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
  /**
   * @class EntityManager
   * @brief Manages entities and their components in a game engine.
   *
   * The EntityManager class is responsible for managing entities and their
   * components in a game engine. It provides methods to add and retrieve
   * various components for entities, such as CameraComponent,
   * PlayerHealthComponent, ShaderComponent, ModelComponent, TransformComponent,
   * WeaponComponent, SkyboxModelComponent, TextureComponent, SoundComponent,
   * and EnemyHealthComponent.
   *
   * The class maintains several unordered maps to store the components
   * associated with each entity. It also tracks lists of renderable entities,
   * skybox entities, collidable entities, and enemy entities.
   *
   * The EntityManager allows adding and retrieving components for entities.
   * It provides methods to access the CameraComponent and PlayerHealthComponent
   * for the game. Methods are also available to retrieve the current weapon
   * entity, player entity, and skybox entity. Additionally, the class provides
   * methods to obtain lists of entities to render, collidable entities, and
   * enemy entities.
   */

private:
  std::unique_ptr<CameraComponent> m_cameraComponent;

  std::unique_ptr<PlayerHealthComponent> m_playerHealthComponent;

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

  std::unordered_map<Entity, std::unique_ptr<EnemyHealthComponent>>
      m_enemyHealthComponents;

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
  PlayerHealthComponent &getPlayerHealthComponent() const;
  Entity getCurrentWeaponEntity() const;
  Entity getPlayerEntity() const;
  Entity getCurrentSkyboxEntity() const;
  std::vector<Entity> getEntitesToRender() const;
  std::vector<Entity> getCollidableEntites() const;
  std::vector<Entity> getEnemyEntities() const;
  void removeEnemyEntity(Entity enemyEntity);

  void addCameraComponent(CameraComponent cameraComponent);
  void addPlayerHealthComponent(PlayerHealthComponent playerHealthComponent);
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
inline std::unordered_map<Entity, std::unique_ptr<EnemyHealthComponent>> &
EntityManager::getComponentMap<EnemyHealthComponent>() {
  return m_enemyHealthComponents;
}
