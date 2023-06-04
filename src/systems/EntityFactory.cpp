#include "EntityFactory.hpp"

EntityFactory::EntityFactory(EntityManager &entityManager)
    : m_EntityManager(entityManager) {}

Entity EntityFactory::createEntity() { return m_NextEntity++; }

Entity EntityFactory::createRenderableEntity(const std::string &shaderPath,
                                             const std::string &texturePath,
                                             Mesh mesh) {
  Entity newEntity = createEntity();
  Shader shader(shaderPath);
  Texture texture(texturePath);

  m_EntityManager.addComponent<GraphicsComponent>(
      newEntity, GraphicsComponent(mesh, texture, shader));
  m_EntityManager.addComponent<TransformComponent>(newEntity,
                                                   TransformComponent());
  return newEntity;
}