#pragma once

#include "EntityManager.hpp"
#include <memory>
#include <vector>

class RenderSystem {
  /**
   * @class RenderSystem
   * @brief Renders entities in a game.
   *
   * The RenderSystem class is responsible for rendering entities in a game.
   * It utilizes the EntityManager to access and manipulate entities.
   *
   * The class provides a method to update the rendering system, which triggers
   * the rendering of entities. The update method should be called regularly to
   * update the rendering of entities.
   *
   * The class supports rendering of different types of entities, including
   * skybox, models, and weapons. It utilizes the projection matrix and view
   * matrix for rendering calculations.
   *
   * The rendering system updates the view matrix based on the camera's position
   * and orientation. It also updates the weapon transform matrix for proper
   * weapon rendering. The rendering methods handle the specific rendering logic
   * for each entity type.
   *
   * Note: The class assumes the usage of the EntityManager to access and
   * manipulate entities. The EntityManager class is expected to be provided to
   * access and manipulate entities. The update method should be called
   * regularly to update the rendering of entities.
   */

private:
  EntityManager &m_entityManager;
  glm::mat4 m_projectionMatrix;
  glm::mat4 m_viewMatrix;

  glm::mat4 m_weaponTransformMatrix;

  void renderCrosshairEntity(Entity crosshairEntity) const;
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
