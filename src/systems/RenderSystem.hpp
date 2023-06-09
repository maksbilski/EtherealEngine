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

  void renderSkybox(const Entity &entity) const;
  void renderModel(const Entity &entity) const;
  void renderWeapon(const Entity &entity) const;
  void updateViewMatrix();
  void updateWeaponTransformMatrix();
  void setupShader(std::shared_ptr<Shader> &shader,
                   const glm::mat4 &modelMatrix) const;

public:
  RenderSystem(EntityManager &EntityManager);
  ~RenderSystem();
  void update();
};
