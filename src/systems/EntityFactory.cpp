#include "EntityFactory.hpp"
#include "../components/GraphicsComponent.hpp"
#include "../components/TransformComponent.hpp"
#include "ResourceManager.hpp"

EntityFactory::EntityFactory(EntityManager &entityManager,
                             ResourceManager &resourceManager)
    : m_EntityManager(entityManager), m_ResourceManager(resourceManager) {}

Entity EntityFactory::getNewEntityId() { return m_NextEntity++; }

Entity EntityFactory::createRenderableEntity(EntityType entityType,
                                             glm::vec3 position,
                                             glm::vec3 rotation,
                                             glm::vec3 scale) {
  Entity newEntity = getNewEntityId();

  std::shared_ptr<Model> model;
  std::shared_ptr<Shader> shader;

  switch (entityType) {
  case EntityType::SHOTGUN:
    model = m_ResourceManager.getModel(EntityType::SHOTGUN);
    shader = m_ResourceManager.getShader(EntityType::SHOTGUN);
    break;
  case EntityType::TERRAIN:
    model = m_ResourceManager.getModel(EntityType::TERRAIN);
    shader = m_ResourceManager.getShader(EntityType::TERRAIN);
    break;
  }

  m_EntityManager.addComponent<GraphicsComponent>(
      newEntity, GraphicsComponent(model, shader));
  m_EntityManager.addComponent<TransformComponent>(
      newEntity, TransformComponent(position, rotation, scale));
  m_EntityManager.addRenderableEntity(newEntity);

  return newEntity;
}

Entity EntityFactory::createWeaponEntity(EntityType entityType,
                                         glm::vec3 scale) {
  glm::vec3 weaponPosition = m_EntityManager.getCameraComponent().getPosition();
  weaponPosition.x += 2.0f;
  weaponPosition.y -= 3.0f;
  weaponPosition.z -= 12.0f;
  glm::vec3 weaponRotation = glm::vec3(0.0f, -90.0f, 0.0f);
  glm::vec3 weaponScale = glm::vec3(0.05f);
  Entity weaponEntity = createRenderableEntity(entityType, weaponPosition,
                                               weaponRotation, weaponScale);
  m_EntityManager.addComponent<WeaponComponent>(
      weaponEntity, WeaponComponent(weaponPosition));
  m_EntityManager.setCurrentWeaponEntity(weaponEntity);
  return weaponEntity;
}