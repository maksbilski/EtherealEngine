#pragma once

#include "EntityManager.hpp"

class EntityFactory {
private:
  EntityManager &m_EntityManager;
  Entity m_NextEntity = 0;

  Entity createEntity();

public:
  EntityFactory(EntityManager &entityManager);
  Entity createRenderableEntity(const std::string &meshPath,
                                const std::string &texturePath,
                                const std::string &shaderPath);
};