#pragma once

#include <string>
#include <vector>

class Mesh {
public:
  std::string m_Filepath;
  std::vector<float> m_Vertices;
  std::vector<unsigned int> m_Indices;

  Mesh(const std::string &filepath);

private:
  void loadFromFile(const std::string &filepath);
};
