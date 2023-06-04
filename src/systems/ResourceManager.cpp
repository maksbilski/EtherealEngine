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
  // Tutaj załaduj zasoby i przechowaj je jako shared_ptr w odpowiednich mapach.
  // Na przykład:
  // m_Meshes[EntityType::TERRAIN] = std::make_shared<Mesh>("terrain.obj");
  // m_Textures[EntityType::TERRAIN] = std::make_shared<Texture>("terrain.png");
  // m_Shaders[EntityType::TERRAIN] =
  // std::make_pair(std::make_shared<Shader>("terrainVS.glsl"),
  // std::make_shared<Shader>("terrainFS.glsl"));
  // ...
}
