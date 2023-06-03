#pragma once

class Mesh {
public:
  float *m_Vertices;
  unsigned int *m_Indices;

  Mesh(float *vertices, unsigned int *indices)
      : m_Vertices(vertices), m_Indices(indices) {}
};
