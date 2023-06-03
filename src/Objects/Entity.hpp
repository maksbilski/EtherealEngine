#pragma once
#include "../engine/Shader.hpp"
#include "../vendor/glm/glm.hpp"
#include <memory>
#include <string>
#include <vector>

class Entity {
public:
  Entity() {}

  template <typename T> void addComponent(std::unique_ptr<T> component);

  template <typename T> T *getComponent();

private:
  std::unordered_map<std::string, std::unique_ptr<void>> components;
};
