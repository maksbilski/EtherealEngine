#pragma once

#include "EntityManager.hpp"

class EntityFactory {
private:
  EntityManager &m_EntityManager;
  Entity m_NextEntity = 0;

  Entity createEntity();

public:
  EntityFactory(EntityManager &entityManager);
  Entity createRenderableEntity(const std::string &shaderPath,
                                const std::string &texturePath, Mesh mesh);
};