#pragma once

#include "EntityManager.hpp"
#include "ResourceManager.hpp"

class EntityFactory {
private:
  EntityManager &m_EntityManager;
  ResourceManager &m_ResourceManager;
  Entity m_NextEntity = 0;

  Entity getNewEntityId();

public:
  EntityFactory(EntityManager &entityManager, ResourceManager &resourceManager);
  Entity createRenderableEntity(EntityType entityType,
                                glm::vec3 position = glm::vec3(0.0f),
                                glm::vec3 rotation = glm::vec3(0.0f),
                                glm::vec3 scale = glm::vec3(1.0f));
};