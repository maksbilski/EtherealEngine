#pragma once

#include "../../vendor/glm/glm.hpp"
#include "../../vendor/glm/gtx/rotate_vector.hpp"

class CameraComponent {
  /**
   * @class CameraComponent
   * @brief Represents a camera component for a 3D scene.
   *
   * The CameraComponent class manages the position, movement, and orientation
   * of a camera in a 3D scene. It provides methods to compute movement vectors,
   * update the camera's position, and set its orientation. The camera's
   * position is represented by a 3D vector, and its orientation is defined by
   * three orthogonal vectors: the forward vector, the sideway vector, and the
   * up vector. The camera component also tracks whether the camera is touching
   * the ground and whether it is currently moving.
   */
private:
  float m_currentLookAngleX;
  float m_currentLookAngleY;

  glm::vec3 m_position;
  glm::vec3 m_movementForwardVec;
  glm::vec3 m_movementSidewayVec;
  glm::vec3 m_movementUpVec;

  glm::vec3 m_cameraForwardVec;
  glm::vec3 m_cameraSidewayVec;
  glm::vec3 m_cameraUpVec;
  glm::vec3 m_cameraLookVec;

  bool m_isTouchingGround;
  bool m_isMoving;

public:
  CameraComponent(const glm::vec3 &position);
  ~CameraComponent();
  void computeWalkVectors();
  void computeCameraOrientation();

  float getCurrentLookAngleX() const;
  float getCurrentLookAngleY() const;
  glm::vec3 getPosition() const;
  glm::vec3 getMovementForwardVec() const;
  glm::vec3 getMovementSidewayVec() const;
  glm::vec3 getMovementUpVec() const;
  glm::vec3 getCameraForwardVec() const;
  glm::vec3 getCameraSidewayVec() const;
  glm::vec3 getCameraUpVec() const;
  glm::vec3 getCameraLookVec() const;
  bool getIfIsTouchingGround() const;
  bool getIfIsMoving() const;

  void setCurrentLookAngleX(float newCurrentLookAngleX);
  void setCurrentLookAngleY(float newCurrentLookAngleX);
  void updatePosition(glm::vec3 movementVector);
  void setPosition(glm::vec3 newPosition);
  void setMovementForwardVec(glm::vec3 newMovementForwardVec);
  void setMovementSidewayVec(glm::vec3 newMovementSidewayVec);
  void setMovementUpVec(glm::vec3 newMovementUpVec);
  void setCameraForwardVec(glm::vec3 newCameraForwardVec);
  void setCameraSidewayVec(glm::vec3 newCameraSidewayVec);
  void setCameraUpVec(glm::vec3 newCameraUpVec);
  void setCameraLookVec(glm::vec3 newCameraLookVec);
  void setIfIsTouchingGround(bool state);
  void setIfIsMoving(bool state);
};