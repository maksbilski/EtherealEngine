#pragma once

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"

class TransformComponent {
private:
  glm::vec3 m_position;
  glm::vec3 m_rotation;
  glm::vec3 m_scale;

public:
  // Konstruktor, który ustawia pozycję, obrót i skalę
  TransformComponent(const glm::vec3 &position, const glm::vec3 &rotation,
                     const glm::vec3 &scale)
      : m_position(position), m_rotation(rotation), m_scale(scale) {}

  glm::vec3 getPosition() const;
  glm::vec3 getRotation() const;
  glm::vec3 getScale() const;

  void setPosition(glm::vec3 newPosition);
  void setPositionX(float newXPosition);
  void setPositionY(float newYPosition);
  void setPositionZ(float newZPosition);
  void updatePosition(glm::vec3 position);
  void setRotation(glm::vec3 newRotation);
  void setScale(glm::vec3 newScale);
  // Metoda do tworzenia macierzy transformacji
  glm::mat4 createTransformMatrix() const;
};
