#pragma once

#include "../engine/Model.hpp"
#include "../engine/Shader.hpp"
#include <map>
#include <memory>

enum class EntityType {
  TERRAIN,
  SHOTGUN
  // Dodaj więcej typów zasobów, jeśli są potrzebne
};

enum class ShaderType { BASIC_SHADER };

class ResourceManager {
private:
  std::unordered_map<EntityType, std::shared_ptr<Model>> m_Models;
  std::unordered_map<ShaderType, std::shared_ptr<Shader>> m_Shaders;

  void loadResources();

public:
  ResourceManager();
  ~ResourceManager();

  std::shared_ptr<Model> getModel(EntityType type);
  std::shared_ptr<Shader> getShader(ShaderType type);
};
