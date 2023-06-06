#pragma once

#include "EntityManager.hpp"
#include <memory>
#include <vector>

class RenderSystem {
private:
  EntityManager &m_EntityManager;
  glm::mat4 m_ProjectionMatrix;
  glm::mat4 m_ViewMatrix;

  void renderSkybox(Entity entity);
  void renderModel(Entity entity);
  void updateViewMatrix();

public:
  RenderSystem(EntityManager &EntityManager);
  ~RenderSystem();
  void update();
};
