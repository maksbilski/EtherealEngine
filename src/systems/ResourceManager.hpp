#pragma once

#include "../engine/Model.hpp"
#include "../engine/Shader.hpp"
#include "../engine/SkyboxModel.hpp"
#include <map>
#include <memory>
#include <vector>

enum class EntityType { TERRAIN, SHOTGUN, SKYBOX, FLOATING_ROCK, EYEBEAST };

typedef unsigned int TextureID;
class ResourceManager {
private:
  std::unordered_map<EntityType, std::shared_ptr<Model>> m_models;
  std::unordered_map<EntityType, std::shared_ptr<Shader>> m_shaders;
  std::unordered_map<EntityType, TextureID> m_textures;
  std::shared_ptr<SkyboxModel> m_skyboxModel;

  void loadResources();
  unsigned int loadCubemap(std::vector<std::string> faces);

public:
  ResourceManager();
  ~ResourceManager();

  std::shared_ptr<Model> getModel(EntityType type);
  std::shared_ptr<Shader> getShader(EntityType type);
  TextureID getTexture(EntityType type);
  std::shared_ptr<SkyboxModel> getSkyboxModel();
};
