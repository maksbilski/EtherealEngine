#pragma once

class Mesh {
public:
  float *m_Vertices;
  unsigned int *m_Indices;
  unsigned int vertexCount;
  unsigned int indexCount;

  Mesh(float *vertices, unsigned int vertexCount, unsigned int *indices,
       unsigned int indexCount)
      : vertexCount(vertexCount), indexCount(indexCount) {
    m_Vertices = new float[vertexCount];
    std::copy(vertices, vertices + vertexCount, m_Vertices);

    m_Indices = new unsigned int[indexCount];
    std::copy(indices, indices + indexCount, m_Indices);
  }

  ~Mesh() {
    delete[] m_Vertices;
    delete[] m_Indices;
  }
};
