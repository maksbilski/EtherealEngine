#pragma once

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"

class TransformComponent {
public:
  glm::vec3 m_Position;
  glm::vec3 m_Rotation;
  glm::vec3 m_Scale;

  // Konstruktor, który ustawia pozycję, obrót i skalę
  TransformComponent(const glm::vec3 &position, const glm::vec3 &rotation,
                     const glm::vec3 &scale)
      : m_Position(position), m_Rotation(rotation), m_Scale(scale) {}

  // Metoda do tworzenia macierzy transformacji
  glm::mat4 createTransformMatrix() const;
};
