#pragma once

#include "EntityManager.hpp"
#include <memory>
#include <vector>

class RenderSystem {
private:
  EntityManager &m_EntityManager;
  glm::mat4 m_ProjectionMatrix;
  glm::mat4 m_ViewMatrix;

  glm::mat4 m_WeaponTransformMatrix;

  void renderSkybox(Entity entity);
  void renderModel(Entity entity);
  void updateViewMatrix();
  void updateWeaponTransformMatrix();

public:
  RenderSystem(EntityManager &EntityManager);
  ~RenderSystem();
  void update();
};
