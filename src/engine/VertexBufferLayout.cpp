#include "VertexBufferLayout.hpp"

template <> void VertexBufferLayout::Push<float>(unsigned int count) {
  m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
  m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
}

template <> void VertexBufferLayout::Push<unsigned int>(unsigned int count) {
  m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
  m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
}

template <> void VertexBufferLayout::Push<unsigned char>(unsigned int count) {
  m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
  m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
}
