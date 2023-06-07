#include "CameraComponent.hpp"

CameraComponent::CameraComponent(const glm::vec3 &position)
    : m_position(position) {
  m_currentLookAngleX = 0.0f;
  m_currentLookAngleY = 0.0f;

  computeWalkVectors();
  computeCameraOrientation();
}

CameraComponent::~CameraComponent() {}

void CameraComponent::computeWalkVectors() {
  m_movementUpVec = glm::vec3(0.0f, 1.0f, 0.0f);
  m_movementForwardVec = glm::rotate(glm::vec3(0.0f, 0.0f, -1.0f),
                                     m_currentLookAngleY, m_movementUpVec);
  m_movementSidewayVec =
      glm::normalize(glm::cross(m_movementForwardVec, m_movementUpVec));
}

void CameraComponent::computeCameraOrientation() {
  m_cameraForwardVec = glm::rotate(glm::vec3(0.0f, 0.0f, -1.0f),
                                   m_currentLookAngleY, m_movementUpVec);
  m_cameraForwardVec = glm::rotate(m_cameraForwardVec, m_currentLookAngleX,
                                   m_movementSidewayVec);

  m_cameraSidewayVec =
      glm::normalize(glm::cross(m_cameraForwardVec, m_movementUpVec));
  m_cameraUpVec =
      glm::normalize(glm::cross(m_cameraSidewayVec, m_cameraForwardVec));

  m_cameraLookVec = m_position + m_cameraForwardVec;
}

float CameraComponent::getCurrentLookAngleX() const {
  return this->m_currentLookAngleX;
}

float CameraComponent::getCurrentLookAngleY() const {
  return this->m_currentLookAngleY;
}

glm::vec3 CameraComponent::getPosition() const { return this->m_position; }

glm::vec3 CameraComponent::getMovementForwardVec() const {
  return this->m_movementForwardVec;
}

glm::vec3 CameraComponent::getMovementSidewayVec() const {
  return this->m_movementSidewayVec;
}

glm::vec3 CameraComponent::getMovementUpVec() const {
  return this->m_movementUpVec;
}

glm::vec3 CameraComponent::getCameraForwardVec() const {
  return this->m_cameraForwardVec;
}

glm::vec3 CameraComponent::getCameraSidewayVec() const {
  return this->m_cameraSidewayVec;
}

glm::vec3 CameraComponent::getCameraUpVec() const {
  return this->m_cameraUpVec;
}

glm::vec3 CameraComponent::getCameraLookVec() const {
  return this->m_cameraLookVec;
}

void CameraComponent::setCurrentLookAngleX(float newCurrentLookAngleX) {
  this->m_currentLookAngleX = newCurrentLookAngleX;
}

void CameraComponent::setCurrentLookAngleY(float newCurrentLookAngleY) {
  this->m_currentLookAngleY = newCurrentLookAngleY;
}

void CameraComponent::updatePosition(glm::vec3 movementVector) {
  this->m_position += movementVector;
}

void CameraComponent::setPosition(glm::vec3 newPosition) {
  this->m_position = newPosition;
}

void CameraComponent::setMovementForwardVec(glm::vec3 newMovementForwardVec) {
  this->m_movementForwardVec = newMovementForwardVec;
}

void CameraComponent::setMovementSidewayVec(glm::vec3 newMovementSidewayVec) {
  this->m_movementSidewayVec = newMovementSidewayVec;
}

void CameraComponent::setMovementUpVec(glm::vec3 newMovementUpVec) {
  this->m_movementUpVec = newMovementUpVec;
}

void CameraComponent::setCameraForwardVec(glm::vec3 newCameraForwardVec) {
  this->m_cameraForwardVec = newCameraForwardVec;
}

void CameraComponent::setCameraSidewayVec(glm::vec3 newCameraSidewayVec) {
  this->m_cameraSidewayVec = newCameraSidewayVec;
}

void CameraComponent::setCameraUpVec(glm::vec3 newCameraUpVec) {
  this->m_cameraUpVec = newCameraUpVec;
}

void CameraComponent::setCameraLookVec(glm::vec3 newCameraLookVec) {
  this->m_cameraLookVec = newCameraLookVec;
}