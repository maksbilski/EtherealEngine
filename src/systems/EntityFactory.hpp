#pragma once

#include "EntityManager.hpp"
#include "ResourceManager.hpp"

enum class EntityType { TERRAIN };

class EntityFactory {
private:
  EntityManager &m_EntityManager;
  ResourceManager &m_ResourceManager;
  Entity m_NextEntity = 0;

  Entity getNewEntityId();

public:
  EntityFactory(EntityManager &entityManager, ResourceManager &resourceManager);
  Entity createRenderableEntity(EntityType entityType);
};