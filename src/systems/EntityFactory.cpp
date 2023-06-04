#include "EntityFactory.hpp"

EntityFactory::EntityFactory(EntityManager &entityManager)
    : m_EntityManager(entityManager) {}

Entity EntityFactory::createEntity() { return m_NextEntity++; }

Entity EntityFactory::createRenderableEntity(const std::string &meshPath,
                                             const std::string &texturePath,
                                             const std::string &shaderPath) {
  Entity newEntity = createEntity();
  Mesh mesh(meshPath);
  Texture texture(texturePath);
  Shader shader(shaderPath);

  m_EntityManager.addComponent<GraphicsComponent>(
      newEntity, GraphicsComponent(mesh, texture, shader));
  m_EntityManager.addComponent<TransformComponent>(newEntity,
                                                   TransformComponent());
  m_EntityManager.addRenderableEntity(newEntity);
  return newEntity;
}