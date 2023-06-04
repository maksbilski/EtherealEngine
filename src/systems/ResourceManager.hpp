#pragma once

#include "../engine/Mesh.hpp"
#include "../engine/Model.hpp"
#include "../engine/Shader.hpp"
#include <map>
#include <memory>

class ResourceManager {
public:
  ResourceManager();
  ~ResourceManager();

  std::shared_ptr<Mesh> getMesh(const std::string &name);
  std::shared_ptr<Texture> getTexture(const std::string &name);
  std::pair<std::shared_ptr<Shader>, std::shared_ptr<Shader>>
  getShader(const std::string &name);

private:
  std::unordered_map<std::string, std::shared_ptr<Mesh>> m_Meshes;
  std::unordered_map<std::string, std::shared_ptr<Texture>> m_Textures;
  std::unordered_map<
      std::string, std::pair<std::shared_ptr<Shader>, std::shared_ptr<Shader>>>
      m_Shaders;

  void loadResources();
};

// ResourceManager.cpp
ResourceManager::ResourceManager() { loadResources(); }

ResourceManager::~ResourceManager() {
  // Zasoby zostaną automatycznie usunięte, gdy ostatni shared_ptr zostanie
  // zniszczony
}

std::shared_ptr<Mesh> ResourceManager::getMesh(const std::string &name) {
  return m_Meshes[name];
}

std::shared_ptr<Texture> ResourceManager::getTexture(const std::string &name) {
  return m_Textures[name];
}

std::pair<std::shared_ptr<Shader>, std::shared_ptr<Shader>>
ResourceManager::getShader(const std::string &name) {
  return m_Shaders[name];
}

void ResourceManager::loadResources() {
  // Tutaj załaduj zasoby i przechowaj je jako shared_ptr w odpowiednich mapach.
  // ...
}