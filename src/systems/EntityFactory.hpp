#pragma once

#include "EntityManager.hpp"

enum class EntityType { TERRAIN };

class EntityFactory {
private:
  EntityManager &m_EntityManager;
  Entity m_NextEntity = 0;

  Entity createEntity();

public:
  EntityFactory(EntityManager &entityManager);
  Entity createRenderableEntity(EntityType entityType);
};