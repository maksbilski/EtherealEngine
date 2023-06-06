#pragma once

#include "../../vendor/glm/glm.hpp"
#include "../../vendor/glm/gtx/rotate_vector.hpp"

class CameraComponent {
private:
  float m_CurrentLookAngleX;
  float m_CurrentLookAngleY;

  glm::vec3 m_Position;
  glm::vec3 m_MovementForwardVec;
  glm::vec3 m_MovementSidewayVec;
  glm::vec3 m_MovementUpVec;

  glm::vec3 m_CameraForwardVec;
  glm::vec3 m_CameraSidewayVec;
  glm::vec3 m_CameraUpVec;
  glm::vec3 m_CameraLookVec;

public:
  CameraComponent(const glm::vec3 &position);
  ~CameraComponent();
  void computeWalkVectors();
  void computeCameraOrientation();

  float getCurrentLookAngleX() const;
  float getCurrentLookAngleY() const;
  glm::vec3 getPosition() const;
  glm::vec3 getRotation() const;
  glm::vec3 getMovementForwardVec() const;
  glm::vec3 getMovementSidewayVec() const;
  glm::vec3 getMovementUpVec() const;
  glm::vec3 getCameraForwardVec() const;
  glm::vec3 getCameraSidewayVec() const;
  glm::vec3 getCameraUpVec() const;
  glm::vec3 getCameraLookVec() const;

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
};