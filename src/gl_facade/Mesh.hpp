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
  /**
   * @class Mesh
   * @brief Represents a 3D mesh used for rendering.
   *
   * The Mesh class encapsulates the data and functionality related to a 3D
   * mesh, which is used for rendering objects in a 3D scene. It stores the
   * vertex data, index data, and texture data associated with the mesh. The
   * class provides a method to draw the mesh using a given shader.
   *
   * The vertex structure, defined as `Vertex`, stores the position, normal,
   * texture coordinates, tangent, bitangent, and bone influence information of
   * each vertex in the mesh.
   *
   * The texture structure, defined as `Texture`, stores the ID, type, and file
   * path of each texture associated with the mesh.
   *
   * The Mesh class creates and manages the necessary vertex buffer object
   * (VBO), element buffer object (EBO), and vertex array object (VAO) for
   * rendering the mesh efficiently. It also provides a method to draw the mesh
   * using a given shader, applying the appropriate transformations and
   * textures.
   *
   * Note: The class assumes the usage of the GLEW library for OpenGL-related
   * functionality. It relies on the glm library for mathematical operations and
   * matrix transformations. The `Shader` class is expected to be provided for
   * rendering the mesh.
   */

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
