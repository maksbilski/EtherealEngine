#include "EntityFactory.hpp"
#include "../components/GraphicsComponent.hpp"
#include "../components/TransformComponent.hpp"
#include "ResourceManager.hpp"

EntityFactory::EntityFactory(EntityManager &entityManager,
                             ResourceManager &resourceManager)
    : m_EntityManager(entityManager), m_ResourceManager(resourceManager) {}

Entity EntityFactory::getNewEntityId() { return m_NextEntity++; }

Entity EntityFactory::createRenderableEntity(EntityType entityType,
                                             ShaderType shaderType,
                                             glm::vec3 position,
                                             glm::vec3 rotation,
                                             glm::vec3 scale) {
  Entity newEntity = getNewEntityId();

  std::shared_ptr<Model> model;
  std::shared_ptr<Shader> shader;

  switch (entityType) {
  case EntityType::SHOTGUN:
    model = m_ResourceManager.getModel(EntityType::SHOTGUN);
    break;
  }

  switch (shaderType) {
  case ShaderType::BASIC_SHADER:
    shader = m_ResourceManager.getShader(ShaderType::BASIC_SHADER);
    break;
  }

  m_EntityManager.addComponent<GraphicsComponent>(
      newEntity, GraphicsComponent(model, shader));
  m_EntityManager.addComponent<TransformComponent>(
      newEntity, TransformComponent(position, rotation, scale));
  m_EntityManager.addRenderableEntity(newEntity);

  return newEntity;
}