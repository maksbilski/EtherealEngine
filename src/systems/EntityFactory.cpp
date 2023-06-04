#include "EntityFactory.hpp"
#include "../components/GraphicsComponent.hpp"
#include "../components/TransformComponent.hpp"
#include "ResourceManager.hpp";

EntityFactory::EntityFactory(EntityManager &entityManager,
                             ResourceManager &resourceManager)
    : m_EntityManager(entityManager), m_ResourceManager(resourceManager) {}

Entity EntityFactory::getNewEntityId() { return m_NextEntity++; }

Entity EntityFactory::createRenderableEntity(EntityType entityType) {
  Entity newEntity = getNewEntityId();

  std::shared_ptr<Model> model;
  std::shared_ptr<Shader> shader;

  switch (entityType) {
  case EntityType::TERRAIN:
    model = m_ResourceManager.getModel(EntityType::TERRAIN);
    shader = m_ResourceManager.getShader(EntityType::TERRAIN);
    break;
  }

  m_EntityManager.addComponent<GraphicsComponent>(
      newEntity, GraphicsComponent(model, shader));
  m_EntityManager.addComponent<TransformComponent>(newEntity,
                                                   TransformComponent());
  m_EntityManager.addRenderableEntity(newEntity);

  return newEntity;
}