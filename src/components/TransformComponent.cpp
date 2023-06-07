#include "TransformComponent.hpp"

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"

glm::mat4 TransformComponent::createTransformMatrix() const {
  glm::mat4 transform = glm::mat4(1.0f);

  transform = glm::translate(transform, m_position);
  transform = glm::rotate(transform, glm::radians(m_rotation.x),
                          glm::vec3(1.0f, 0.0f, 0.0f));
  transform = glm::rotate(transform, glm::radians(m_rotation.y),
                          glm::vec3(0.0f, 1.0f, 0.0f));
  transform = glm::rotate(transform, glm::radians(m_rotation.z),
                          glm::vec3(0.0f, 0.0f, 1.0f));
  transform = glm::scale(transform, m_scale);

  return transform;
}

glm::vec3 TransformComponent::getPosition() const { return m_position; }

glm::vec3 TransformComponent::getRotation() const { return m_rotation; }

glm::vec3 TransformComponent::getScale() const { return m_scale; }

void TransformComponent::setPosition(glm::vec3 newPosition) {
  m_position = newPosition;
}

void TransformComponent::updatePosition(glm::vec3 position) {
  m_position += position;
}

void TransformComponent::setRotation(glm::vec3 newRotation) {
  m_rotation = newRotation;
}

void TransformComponent::setScale(glm::vec3 newScale) { m_scale = newScale; }