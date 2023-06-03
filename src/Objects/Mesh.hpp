#pragma once
#include "../engine/IndexBuffer.hpp"
#include "../engine/Shader.hpp"
#include "../engine/Texture.hpp"
#include "../engine/VertexArray.hpp"
#include "../engine/VertexBuffer.hpp"

class Mesh {
private:
  VertexArray m_VertexArray;
  VertexBuffer m_VertexBuffer;
  IndexBuffer m_IndexBuffer;
  Shader m_Shader;
  Texture m_Texture;

public:
  Mesh(const std::string& verticesFilepath, const std::string& textureFilePath, const Shader& shader);
  ~Mesh();

  
};