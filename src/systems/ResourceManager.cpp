#include "ResourceManager.hpp"

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

void ResourceManager::loadResources() {

  Shader shader("resources/shaders/model_loading.vs",
                "resources/shaders/model_loading.fs");

  m_Shaders[EntityType::TERRAIN] = std::make_shared<Shader>(shader);

  m_Shaders[EntityType::SHOTGUN] = std::make_shared<Shader>(shader);

  m_Models[EntityType::SHOTGUN] =
      std::make_shared<Model>("resources/models/Shotgun/shotgun.obj");

  m_Models[EntityType::TERRAIN] =
      std::make_shared<Model>("resources/models/concrete/concrete.obj");
}
