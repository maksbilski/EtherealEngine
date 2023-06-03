#pragma once

#include <glm/glm.hpp>
#include <vector>

class Mesh {
public:
  std::vector<glm::vec3> vertices;
  std::vector<unsigned int> indices;

  Mesh(const std::vector<glm::vec3> &vertices,
       const std::vector<unsigned int> &indices)
      : vertices(vertices), indices(indices) {}
};
