#pragma once

#include "../engine/Mesh.hpp"
#include "../engine/Model.hpp"
#include "../engine/Shader.hpp"
#include <map>
#include <memory>

enum class EntityType {
    TERRAIN
    // Dodaj więcej typów zasobów, jeśli są potrzebne
};

class ResourceManager {
public:
  ResourceManager();
  ~ResourceManager();

  std::shared_ptr<Mesh> getMesh(EntityType type);
  std::shared_ptr<Texture> getTexture(EntityType type);
  std::pair<std::shared_ptr<Shader>, std::shared_ptr<Shader>> getShader(EntityType type);

private:
  std::unordered_map<EntityType, std::shared_ptr<Mesh>> m_Meshes;
  std::unordered_map<EntityType, std::shared_ptr<Texture>> m_Textures;
  std::unordered_map<EntityType, std::pair<std::shared_ptr<Shader>, std::shared_ptr<Shader>>> m_Shaders;

  void loadResources();
};

// ResourceManager.cpp
ResourceManager::ResourceManager() { loadResources(); }

ResourceManager::~ResourceManager() {
  // Zasoby zostaną automatycznie usunięte, gdy ostatni shared_ptr zostanie zniszczony
}

std::shared_ptr<Mesh> ResourceManager::getMesh(EntityType type) {
  return m_Meshes[type];
}

std::shared_ptr<Texture> ResourceManager::getTexture(EntityType type) {
  return m_Textures[type];
}

std::pair<std::shared_ptr<Shader>, std::shared_ptr<Shader>> ResourceManager::getShader(EntityType type) {
  return m_Shaders[type];
}

void ResourceManager::loadResources() {
  // Tutaj załaduj zasoby i przechowaj je jako shared_ptr w odpowiednich mapach.
  // Na przykład:
  // m_Meshes[EntityType::TERRAIN] = std::make_shared<Mesh>("terrain.obj");
  // m_Textures[EntityType::TERRAIN] = std::make_shared<Texture>("terrain.png");
  // m_Shaders[EntityType::TERRAIN] = std::make_pair(std::make_shared<Shader>("terrainVS.glsl"), std::make_shared<Shader>("terrainFS.glsl"));
  // ...
}