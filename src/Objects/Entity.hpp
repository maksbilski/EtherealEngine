#pragma once
#include "../engine/Shader.hpp"
#include "../vendor/glm/glm.hpp"
#include "Mesh.hpp"
#include <string>
#include <vector>

class Entity {
private:
  std::vector<Mesh> m_Meshes;
  glm::vec3 m_Position;
  glm::vec3 m_Scale;
  glm::vec3 m_Rotation;

public:
  Entity(const std::string &path); // wczytaj model z pliku

  void SetPosition(const glm::vec3 &position) { this->m_Position = position; }
  void SetScale(const glm::vec3 &scale) { this->m_Scale = scale; }
  void SetRotation(const glm::vec3 &rotation) { this->m_Rotation = rotation; }

  void Draw();
};
