#pragma once

#include <GL/glew.h>

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../vendor/stb_image/stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "Mesh.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

unsigned int TextureFromFile(const char *path, const std::string &directory);

struct Cylinder {
  glm::vec3 center;
  glm::vec3 axis;
  float radius;
  float height;
};

struct Sphere {
  glm::vec3 center;
  float radius;
};

class Model {
  /**
   * @class Model
   * @brief Represents a 3D model loaded from a file.
   *
   * The Model class represents a 3D model loaded from a file using the Assimp
   * library. It stores the textures and meshes associated with the model, along
   * with information about the model's directory and gamma correction. The
   * class provides methods to draw the model, calculate bounding shapes
   * (cylinder and sphere), and load model data from a file.
   *
   * The model can consist of multiple meshes, each represented by the `Mesh`
   * class. Textures associated with the model are stored in the
   * `m_texturesLoaded` vector.
   *
   * The class allows drawing the model using a given shader and provides
   * methods to calculate the bounding cylinder and sphere of the model. It also
   * includes functions to calculate the bounding boxes and centers of the
   * model's meshes.
   *
   * Note: The class assumes the usage of the GLEW library for OpenGL-related
   * functionality. It relies on the glm library for mathematical operations and
   * matrix transformations. The class expects the filepath to a '.obj' file
   * which is in the same directory as mtl file with proper paths to textures.
   * The model loading functionality relies on the Assimp library for importing
   * model data.
   */

public:
  std::vector<Texture> m_texturesLoaded;
  std::vector<Mesh> m_meshes;
  std::string m_directory;
  bool m_gammaCorrection;

  Model(std::string const &filepath, bool gamma = false);
  void draw(Shader &shader);
  Cylinder getBoundingCylinder() const;
  Sphere getBoundingSphere() const;
  void calculateBoundingBoxes();
  void calculateBoundingShapes();

private:
  void loadModel(std::string const &path);
  std::optional<Cylinder> m_boundingCylinder;
  std::optional<Sphere> m_boundingSphere;
  glm::vec3 calculateCenter() const;
  void calculateBoundingShapesCenters();
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene *scene);
  std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                            std::string typeName);
};