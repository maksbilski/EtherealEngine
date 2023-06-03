#pragma once

#include "../../vendor/glm/glm.hpp"
#include "InputComponent.hpp"

class CameraComponent {
private:
  glm::vec3 m_Position;
  glm::vec3 m_MovementForwardVec;
  glm::vec3 m_MovementSidewayVec;
  glm::vec3 m_MovementUpVec;

  glm::vec3 m_CameraForwardVec;
  glm::vec3 m_CameraSidewayVec;
  glm::vec3 m_CameraUpVec;
  glm::vec3 m_CameraLookVec;

  float m_CurrentLookAngleX;
  float m_CurrentLookAngleY;

public:
  CameraComponent(const glm::vec3 &position);
  ~CameraComponent();
  void computeWalkVectors();
  void computeCameraOrientation();
  void update(float deltaTime, const InputComponent &userInput);
  glm::vec3 getPosition() const;
  glm::vec3 getMovementForwardVec() const;
  glm::vec3 getMovementSidewayVec() const;
  glm::vec3 getMovementUpVec() const;
  glm::vec3 getCameraForwardVec() const;
  glm::vec3 getCameraSidewayVec() const;
  glm::vec3 getCameraUpVec() const;
  glm::vec3 getCameraUpVec() const;
};