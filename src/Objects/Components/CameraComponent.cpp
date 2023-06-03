#include "CameraComponent.hpp"

CameraComponent::CameraComponent(const glm::vec3 &position)
    : m_Position(position) {
  m_CurrentLookAngleX = 0.0f;
  m_CurrentLookAngleX = 0.0f;

  computeWalkVectors();
  computeCameraOrientation();
}

CameraComponent::~CameraComponent() {}

void CameraComponent::computeWalkVectors() {
  m_MovementUpVec = glm::vec3(0.0f, 1.0f, 0.0f);
  m_MovementForwardVec = glm::rotate(glm::vec3(0.0f, 0.0f, -1.0f),
                                     m_CurrentLookAngleY, m_MovementUpVec);
  m_MovementSidewayVec =
      glm::normalize(glm::cross(m_MovementForwardVec, m_MovementUpVec));
}

void CameraComponent::computeCameraOrientation() {
  m_CameraForwardVec = glm::rotate(glm::vec3(0.0f, 0.0f, -1.0f),
                                   m_CurrentLookAngleY, m_MovementUpVec);
  m_CameraForwardVec = glm::rotate(m_CameraForwardVec, m_CurrentLookAngleX,
                                   m_MovementSidewayVec);

  m_CameraSidewayVec =
      glm::normalize(glm::cross(m_CameraForwardVec, m_MovementUpVec));
  m_CameraUpVec =
      glm::normalize(glm::cross(m_CameraSidewayVec, m_CameraForwardVec));

  m_CameraLookVec = m_Position + m_CameraForwardVec;
}

glm::vec3 CameraComponent::getPosition() const { return this->m_Position; }

glm::vec3 CameraComponent::getMovementForwardVec() const {
  return this->m_MovementForwardVec;
}

glm::vec3 CameraComponent::getMovementSidewayVec() const {
  return this->m_MovementSidewayVec;
}

glm::vec3 CameraComponent::getMovementUpVec() const {
  return this->m_MovementUpVec;
}

glm::vec3 CameraComponent::getCameraForwardVec() const {
  return this->m_CameraForwardVec;
}

glm::vec3 CameraComponent::getCameraSidewayVec() const {
  return this->m_CameraSidewayVec;
}

glm::vec3 CameraComponent::getCameraUpVec() const {
  return this->m_CameraUpVec;
}

glm::vec3 CameraComponent::getCameraLookVec() const {
  return this->m_CameraLookVec;
}

void CameraComponent::setPosition(glm::vec3 newPosition) {
  this->m_Position = newPosition;
}

void CameraComponent::setMovementForwardVec(glm::vec3 newMovementForwardVec) {
  this->m_MovementForwardVec = newMovementForwardVec;
}

void CameraComponent::setMovementSidewayVec(glm::vec3 newMovementSidewayVec) {
  this->m_MovementSidewayVec = newMovementSidewayVec;
}

void CameraComponent::setMovementUpVec(glm::vec3 newMovementUpVec) {
  this->m_MovementUpVec = newMovementUpVec;
}

void CameraComponent::setCameraForwardVec(glm::vec3 newCameraForwardVec) {
  this->m_CameraForwardVec = newCameraForwardVec;
}

void CameraComponent::setCameraSidewayVec(glm::vec3 newCameraSidewayVec) {
  this->m_CameraSidewayVec = newCameraSidewayVec;
}

void CameraComponent::setCameraUpVec(glm::vec3 newCameraUpVec) {
  this->m_CameraUpVec = newCameraUpVec;
}

void CameraComponent::setCameraLookVec(glm::vec3 newCameraLookVec) {
  this->m_CameraLookVec = newCameraLookVec;
}