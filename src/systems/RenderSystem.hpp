#pragma once

#include "Entity.hpp"
#include <memory>
#include <vector>

class RenderSystem {
private:
  std::vector<std::shared_ptr<Entity>> entities;

  void render(const std::shared_ptr<Entity> &entity);

public:
  void addEntity(const std::shared_ptr<Entity> &entity);
  void removeEntity(const std::shared_ptr<Entity> &entity);
  void update(float deltaTime);
};
