#pragma once

#include "EntityManager.hpp"
#include <memory>
#include <vector>

class RenderSystem {
private:
  EntityManager &m_entityManager;
  glm::mat4 m_projectionMatrix;
  glm::mat4 m_viewMatrix;

  glm::mat4 m_weaponTransformMatrix;

  void renderSkybox(Entity entity);
  void renderModel(Entity entity);
  void updateViewMatrix();
  void updateWeaponTransformMatrix();

public:
  RenderSystem(EntityManager &EntityManager);
  ~RenderSystem();
  void update();
};
