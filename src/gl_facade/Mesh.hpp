#pragma once

#include <GL/glew.h>

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"

#include "Shader.hpp"

#include <string>
#include <vector>

#define MAX_BONE_INFLUENCE 4

struct Vertex {
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 texCoords;
  glm::vec3 tangent;
  glm::vec3 bitangent;
  int m_boneIDs[MAX_BONE_INFLUENCE];
  float m_weights[MAX_BONE_INFLUENCE];
};

struct Texture {
  unsigned int id;
  std::string type;
  std::string path;
};

class Mesh {
public:
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;
  unsigned int VAO;

  Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
       std::vector<Texture> textures);
  void draw(Shader &shader);

private:
  unsigned int VBO, EBO;

  void setupMesh();
};
