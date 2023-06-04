#include "Mesh.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

Mesh::Mesh(const std::string &filepath) { loadFromFile(filepath); }

void Mesh::loadFromFile(const std::string &filepath) {
  std::ifstream file(filepath);

  if (!file.is_open()) {
    std::cerr << "Failed to open mesh file: " << filepath << std::endl;
    return;
  }

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string type;
    iss >> type;

    if (type == "v") {
      for (int i = 0; i < 5; i++) {
        float value;
        iss >> value;
        m_Vertices.push_back(value);
      }
    } else if (type == "f") {
      for (int i = 0; i < 3; i++) {
        unsigned int index;
        iss >> index;
        m_Indices.push_back(index - 1);
      }
    }
  }
  file.close();
}