#pragma once

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"

class TransformComponent {
  /**
   * @class TransformComponent
   * @brief Represents a component that holds the transformation properties of
   * an entity.
   *
   * The TransformComponent class manages the position, rotation, and scale of
   * an entity in a 3D world. It provides methods to retrieve and update these
   * transformation properties. The position is represented by a 3D vector,
   * indicating the entity's position in the world. The rotation is also
   * represented by a 3D vector, defining the entity's rotation in each axis.
   * The scale is represented by a 3D vector, specifying the entity's size in
   * each axis.
   *
   * The component allows retrieving and updating these transformation
   * properties individually or as a whole. Additionally, it provides a method
   * to create a transformation matrix using the transformation properties. This
   * matrix can be used to transform the entity's vertices during rendering,
   * applying translation, rotation, and scaling.
   *
   * Note: The class uses the glm library for mathematical operations and matrix
   * transformations.
   */
private:
  glm::vec3 m_position;
  glm::vec3 m_rotation;
  glm::vec3 m_scale;

public:
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
  glm::mat4 createTransformMatrix() const;
};
