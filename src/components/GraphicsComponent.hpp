#pragma once

#include "../engine/Mesh.hpp"
#include "../engine/Shader.hpp"
#include "../engine/Texture.hpp"

class GraphicsComponent {
public:
  // Referencje do meshu, tekstury i shadera
  Mesh &mesh;
  Texture &texture;
  Shader &shader;

  // Konstruktor, który przyjmuje referencje do meshu, tekstury i shadera
  GraphicsComponent(Mesh &mesh, Texture &texture, Shader &shader)
      : mesh(mesh), texture(texture), shader(shader) {}

  // Setter functions
  void setMesh(Mesh &newMesh) { mesh = newMesh; }

  void setTexture(Texture &newTexture) { texture = newTexture; }

  void setShader(Shader &newShader) { shader = newShader; }
};
