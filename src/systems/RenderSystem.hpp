#pragma once

#include "Entity.hpp"
#include <memory>
#include <vector>

class RenderSystem {
private:
  std::vector<std::shared_ptr<Entity>> entities;
  std::shared_ptr<Entity> m_Player;
  glm::mat4 m_ProjectionMatrix;
  glm::mat4 m_ViewMatrix;

  void render(const std::shared_ptr<Entity> &entity);
  void updateViewMatrix();

public:
  RenderSystem(std::shared_ptr<Entity> player);
  ~RenderSystem();
  void addEntity(const std::shared_ptr<Entity> &entity);
  void removeEntity(const std::shared_ptr<Entity> &entity);
  void update();
};
