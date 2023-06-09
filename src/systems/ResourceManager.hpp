#pragma once

#include "../gl_facade/Model.hpp"
#include "../gl_facade/Shader.hpp"
#include "../gl_facade/SkyboxModel.hpp"
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
  /**
   * @class ResourceManager
   * @brief Manages game resources such as models, shaders, textures, and
   * sounds.
   *
   * The ResourceManager class is responsible for managing game resources such
   * as models, shaders, textures, and sounds. It provides methods to load and
   * retrieve these resources based on the entity type.
   *
   * The class maintains maps to store shared pointers to models, shaders, sound
   * buffers, and texture IDs. It also provides a shared pointer to the skybox
   * model.
   *
   * The ResourceManager loads the necessary resources during construction.
   * It provides methods to retrieve the appropriate resource based on the
   * entity type.
   */

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
