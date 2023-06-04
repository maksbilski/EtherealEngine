#include "EntityFactory.hpp"
#include "ResourceManager.hpp"

enum class EntityType { TERRAIN };

EntityFactory::EntityFactory(EntityManager &entityManager)
    : m_EntityManager(entityManager) {}

Entity EntityFactory::createEntity() { return m_NextEntity++; }

EntityFactory::createRenderableEntity(EntityType entityType) {
  Entity newEntity = createEntity();

  std::shared_ptr<Model> model;
  std::pair<std::shared_ptr<Shader>, std::shared_ptr<Shader>> shader;

  switch (entityType) {
  case EntityType::TERRAIN:
    mesh = ResourceManager::getMesh("terrain");
    texture = ResourceManager::getTexture("terrain");
    shader = ResourceManager::getShader("terrain");
    break;
  }

  m_EntityManager.addComponent<GraphicsComponent>(
      newEntity, GraphicsComponent(model, shader));
  m_EntityManager.addComponent<TransformComponent>(newEntity,
                                                   TransformComponent());
  m_EntityManager.addRenderableEntity(newEntity);

  return newEntity;
}