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

unsigned int ResourceManager::getTexture(EntityType type) {
  return m_textures[type];
}

std::shared_ptr<SkyboxModel> ResourceManager::getSkyboxModel() {
  return m_skyboxModel;
}

void ResourceManager::loadResources() {

  Shader shader("resources/shaders/model_loading.vs",
                "resources/shaders/model_loading.fs");
  Shader skyboxShader("resources/shaders/skybox_shader.vs",
                      "resources/shaders/skybox_shader.fs");

  m_shaders[EntityType::TERRAIN] = std::make_shared<Shader>(shader);

  m_shaders[EntityType::SHOTGUN] = std::make_shared<Shader>(shader);

  m_shaders[EntityType::FLOATING_ROCK] = std::make_shared<Shader>(shader);

  m_shaders[EntityType::SKYBOX] = std::make_shared<Shader>(skyboxShader);

  m_shaders[EntityType::EYEBEAST] = std::make_shared<Shader>(shader);

  m_models[EntityType::PLAYER] =
      std::make_shared<Model>("resources/models/player/player.obj");

  m_models[EntityType::SHOTGUN] =
      std::make_shared<Model>("resources/models/Shotgun/shotgun.obj");

  m_models[EntityType::TERRAIN] =
      std::make_shared<Model>("resources/models/concrete/concrete.obj");

  m_models[EntityType::FLOATING_ROCK] =
      std::make_shared<Model>("resources/models/space_rock/space_rock.obj");

  m_models[EntityType::EYEBEAST] =
      std::make_shared<Model>("resources/models/enemy/enemy.obj");

  std::vector<std::string> faces = {
      "resources/skybox/posx.jpg", "resources/skybox/negx.jpg",
      "resources/skybox/posy.jpg", "resources/skybox/negy.jpg",
      "resources/skybox/posz.jpg", "resources/skybox/negz.jpg"};
  m_textures[EntityType::SKYBOX] = loadCubemap(faces);

  m_skyboxModel = std::make_shared<SkyboxModel>();
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