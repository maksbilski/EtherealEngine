#pragma once

#include "../engine/Mesh.hpp"
#include "../engine/Shader.hpp"
#include "../engine/Texture.hpp"

class GraphicsComponent {
public:
  // Referencje do meshu, tekstury i shadera
  Mesh &m_Mesh;
  Texture &m_Texture;
  Shader &m_Shader;

  // Konstruktor, który przyjmuje referencje do meshu, tekstury i shadera
  GraphicsComponent(Mesh &mesh, Texture &texture, Shader &shader)
      : m_Mesh(mesh), m_Texture(texture), m_Shader(shader) {}

  // Setter functions
  void setMesh(Mesh &newMesh) { m_Mesh = newMesh; }

  void setTexture(Texture &newTexture) { m_Texture = newTexture; }

  void setShader(Shader &newShader) { m_Shader = newShader; }
};
