#pragma once
#include "../engine/Shader.hpp"
#include "../vendor/glm/glm.hpp"
#include <any>
#include <memory>
#include <string>
#include <typeindex>
#include <vector>

class Entity {
public:
  Entity() {}

  template <typename T> void addComponent(T component) {
    components[std::type_index(typeid(T))] = std::any(component);
  }

  template <typename T> T getComponent() {
    auto it = components.find(std::type_index(typeid(T)));
    if (it == components.end()) {
      throw std::runtime_error("Component doesn't exist");
    }
    return std::any_cast<T>(it->second);
  }

private:
  std::unordered_map<std::type_index, std::any> components;
};