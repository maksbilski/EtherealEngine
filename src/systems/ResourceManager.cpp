#include "ResourceManager.hpp"
#include "../vendor/stb_image/stb_image.h"

#include <string>
#include <vector>

ResourceManager::ResourceManager() { loadResources(); }

ResourceManager::~ResourceManager() {
  // Zasoby zostaną automatycznie usunięte, gdy ostatni shared_ptr zostanie
  // zniszczony
}

std::shared_ptr<Model> ResourceManager::getModel(EntityType type) {
  return m_models[type];
}

std::shared_ptr<Shader> ResourceManager::getShader(EntityType type) {
  return m_shaders[type];
}

std::shared_ptr<std::vector<sf::SoundBuffer>>
ResourceManager::getSoundBuffers(EntityType type) {
  return m_soundBuffers[type];
}

unsigned int ResourceManager::getTexture(EntityType type) {
  return m_textures[type];
}

std::shared_ptr<SkyboxModel> ResourceManager::getSkyboxModel() {
  return m_skyboxModel;
}

void ResourceManager::loadResources() {
  loadShaders();
  loadModels();
  loadSounds();
}

void ResourceManager::loadShaders() {
  Shader shader("resources/shaders/model_loading.vs",
                "resources/shaders/model_loading.fs");
  Shader skyboxShader("resources/shaders/skybox_shader.vs",
                      "resources/shaders/skybox_shader.fs");
  Shader crosshairShader("resources/shaders/skybox_shader.vs",
                         "resources/shaders/skybox_shader.fs");

  m_shaders[EntityType::TERRAIN] = std::make_shared<Shader>(shader);

  m_shaders[EntityType::SHOTGUN] = std::make_shared<Shader>(shader);

  m_shaders[EntityType::FLOATING_ROCK] = std::make_shared<Shader>(shader);

  m_shaders[EntityType::SKYBOX] = std::make_shared<Shader>(skyboxShader);

  m_shaders[EntityType::EYEBEAST] = std::make_shared<Shader>(shader);

  m_shaders[EntityType::CROSSHAIR] = std::make_shared<Shader>(crosshairShader);
}

void ResourceManager::loadModels() {
  m_models[EntityType::PLAYER] =
      std::make_shared<Model>("resources/models/player/player.obj");

  m_models[EntityType::PLAYER]->calculateBoundingShapes();

  m_models[EntityType::SHOTGUN] =
      std::make_shared<Model>("resources/models/Shotgun/shotgun.obj");

  m_models[EntityType::TERRAIN] =
      std::make_shared<Model>("resources/models/concrete/concrete.obj");

  m_models[EntityType::FLOATING_ROCK] =
      std::make_shared<Model>("resources/models/space_rock/space_rock.obj");

  m_models[EntityType::EYEBEAST] =
      std::make_shared<Model>("resources/models/enemy/enemy.obj");

  m_models[EntityType::EYEBEAST]->calculateBoundingShapes();

  std::vector<std::string> faces = {
      "resources/skybox/right.png", "resources/skybox/left.png",
      "resources/skybox/top.png",   "resources/skybox/bottom.png",
      "resources/skybox/front.png", "resources/skybox/back.png"};
  m_textures[EntityType::SKYBOX] = loadCubemap(faces);

  m_skyboxModel = std::make_shared<SkyboxModel>();
}

void ResourceManager::loadSounds() {
  std::vector<sf::SoundBuffer> weaponSoundBuffers;
  sf::SoundBuffer weaponShotBuffer;
  weaponShotBuffer.loadFromFile("resources/sounds/shotgun.wav");
  weaponSoundBuffers.push_back(weaponShotBuffer);

  m_soundBuffers[EntityType::SHOTGUN] =
      std::make_shared<std::vector<sf::SoundBuffer>>(weaponSoundBuffers);

  std::vector<sf::SoundBuffer> playerSoundBuffers;

  sf::SoundBuffer playerDamage1;
  playerDamage1.loadFromFile("resources/sounds/damage1.wav");
  playerSoundBuffers.push_back(playerDamage1);

  sf::SoundBuffer playerDamage2;
  playerDamage2.loadFromFile("resources/sounds/damage2.wav");
  playerSoundBuffers.push_back(playerDamage2);

  sf::SoundBuffer playerDamage3;
  playerDamage3.loadFromFile("resources/sounds/damage3.wav");
  playerSoundBuffers.push_back(playerDamage3);

  sf::SoundBuffer playerDamage4;
  playerDamage4.loadFromFile("resources/sounds/damage4.wav");
  playerSoundBuffers.push_back(playerDamage4);

  sf::SoundBuffer playerDamage5;
  playerDamage5.loadFromFile("resources/sounds/damage5.wav");
  playerSoundBuffers.push_back(playerDamage5);

  sf::SoundBuffer playerDamage6;
  playerDamage6.loadFromFile("resources/sounds/damage6.wav");
  playerSoundBuffers.push_back(playerDamage6);

  sf::SoundBuffer playerDamage7;
  playerDamage7.loadFromFile("resources/sounds/damage7.wav");
  playerSoundBuffers.push_back(playerDamage7);

  sf::SoundBuffer playerDamage8;
  playerDamage8.loadFromFile("resources/sounds/damage8.wav");
  playerSoundBuffers.push_back(playerDamage8);
  m_soundBuffers[EntityType::PLAYER] =
      std::make_shared<std::vector<sf::SoundBuffer>>(playerSoundBuffers);

  std::vector<sf::SoundBuffer> enemySoundBuffers;
  sf::SoundBuffer enemyDamage1;
  enemyDamage1.loadFromFile("resources/sounds/enemydamage1.wav");
  enemySoundBuffers.push_back(enemyDamage1);

  sf::SoundBuffer enemyDamage2;
  enemyDamage2.loadFromFile("resources/sounds/enemydamage2.wav");
  enemySoundBuffers.push_back(enemyDamage2);

  sf::SoundBuffer enemyDamage3;
  enemyDamage3.loadFromFile("resources/sounds/enemydamage3.wav");
  enemySoundBuffers.push_back(enemyDamage3);

  sf::SoundBuffer enemyDamage4;
  enemyDamage4.loadFromFile("resources/sounds/enemydamage4.wav");
  enemySoundBuffers.push_back(enemyDamage4);

  sf::SoundBuffer enemyDamage5;
  enemyDamage5.loadFromFile("resources/sounds/enemydamage5.wav");
  enemySoundBuffers.push_back(enemyDamage5);

  m_soundBuffers[EntityType::EYEBEAST] =
      std::make_shared<std::vector<sf::SoundBuffer>>(enemySoundBuffers);
}

unsigned int ResourceManager::loadCubemap(std::vector<std::string> faces) {
  unsigned int textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

  int width, height, nrChannels;
  for (unsigned int i = 0; i < faces.size(); i++) {
    unsigned char *data =
        stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
    if (data) {
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height,
                   0, GL_RGB, GL_UNSIGNED_BYTE, data);
      stbi_image_free(data);
    } else {
      std::cout << "Cubemap texture failed to load at path: " << faces[i]
                << std::endl;
      stbi_image_free(data);
    }
  }
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  return textureID;
}