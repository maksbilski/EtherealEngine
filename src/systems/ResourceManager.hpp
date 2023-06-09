#pragma once

#include "../engine/Model.hpp"
#include "../engine/Shader.hpp"
#include "../engine/SkyboxModel.hpp"
#include <SFML/Audio.hpp>
#include <map>
#include <memory>
#include <vector>

enum class EntityType {
  PLAYER,
  TERRAIN,
  SHOTGUN,
  SKYBOX,
  FLOATING_ROCK,
  EYEBEAST
};

typedef unsigned int TextureID;
class ResourceManager {
private:
  std::unordered_map<EntityType, std::shared_ptr<Model>> m_models;
  std::unordered_map<EntityType, std::shared_ptr<Shader>> m_shaders;
  std::unordered_map<EntityType, TextureID> m_textures;
  std::unordered_map<EntityType, std::shared_ptr<std::vector<sf::SoundBuffer>>>
      m_soundBuffers;
  std::shared_ptr<SkyboxModel> m_skyboxModel;

  void loadResources();
  void loadShaders();
  void loadModels();
  void loadSounds();
  unsigned int loadCubemap(std::vector<std::string> faces);

public:
  ResourceManager();
  ~ResourceManager();

  std::shared_ptr<Model> getModel(EntityType type);
  std::shared_ptr<Shader> getShader(EntityType type);
  std::shared_ptr<std::vector<sf::SoundBuffer>>
  getSoundBuffers(EntityType type);
  TextureID getTexture(EntityType type);
  std::shared_ptr<SkyboxModel> getSkyboxModel();
};
