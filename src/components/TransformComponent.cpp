#include "TransformComponent.hpp"

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"

glm::mat4 TransformComponent::createTransformMatrix() const {
  glm::mat4 transform = glm::mat4(1.0f);

  transform = glm::translate(transform, position);
  transform =
      glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1, 0, 0));
  transform =
      glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0, 1, 0));
  transform =
      glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0, 0, 1));
  transform = glm::scale(transform, scale);

  return transform;
}