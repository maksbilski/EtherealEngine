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