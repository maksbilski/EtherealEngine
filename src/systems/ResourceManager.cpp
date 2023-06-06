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
  return m_Models[type];
}

std::shared_ptr<Shader> ResourceManager::getShader(EntityType type) {
  return m_Shaders[type];
}

unsigned int ResourceManager::getTexture(EntityType type) {
  return m_Textures[type];
}

std::shared_ptr<SkyboxModel> ResourceManager::getSkyboxModel() {
  return m_SkyboxModel;
}

void ResourceManager::loadResources() {

  Shader shader("resources/shaders/model_loading.vs",
                "resources/shaders/model_loading.fs");
  Shader skyboxShader("resources/shaders/skybox_shader.vs",
                      "resources/shaders/skybox_shader.fs");

  m_Shaders[EntityType::TERRAIN] = std::make_shared<Shader>(shader);

  m_Shaders[EntityType::SHOTGUN] = std::make_shared<Shader>(shader);

  m_Shaders[EntityType::SKYBOX] = std::make_shared<Shader>(skyboxShader);

  m_Models[EntityType::SHOTGUN] =
      std::make_shared<Model>("resources/models/Shotgun/shotgun.obj");

  m_Models[EntityType::TERRAIN] =
      std::make_shared<Model>("resources/models/concrete/concrete.obj");

  std::vector<std::string> faces = {
      "resources/skybox/posx.png", "resources/skybox/negx.png",
      "resources/skybox/posy.png", "resources/skybox/negy.png",
      "resources/skybox/posz.png", "resources/skybox/negz.png"};
  m_Textures[EntityType::SKYBOX] = loadCubemap(faces);

  m_SkyboxModel = std::make_shared<SkyboxModel>();
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