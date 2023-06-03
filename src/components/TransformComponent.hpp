#pragma once

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"

class TransformComponent {
public:
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;

  // Konstruktor, który ustawia pozycję, obrót i skalę
  TransformComponent(const glm::vec3 &position = glm::vec3(0.0f),
                     const glm::vec3 &rotation = glm::vec3(0.0f),
                     const glm::vec3 &scale = glm::vec3(1.0f))
      : position(position), rotation(rotation), scale(scale) {}

  // Metoda do tworzenia macierzy transformacji
  glm::mat4 createTransformMatrix() const;
};
