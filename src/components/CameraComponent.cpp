#include "CameraComponent.hpp"

CameraComponent::CameraComponent(const glm::vec3 &position)
    : m_position(position) {
  m_currentLookAngleX = 0.0f;
  m_currentLookAngleY = 0.0f;
  m_isTouchingGround = false;
  m_isMoving = false;

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
  return m_currentLookAngleX;
}

float CameraComponent::getCurrentLookAngleY() const {
  return m_currentLookAngleY;
}

glm::vec3 CameraComponent::getPosition() const { return m_position; }

glm::vec3 CameraComponent::getMovementForwardVec() const {
  return m_movementForwardVec;
}

glm::vec3 CameraComponent::getMovementSidewayVec() const {
  return m_movementSidewayVec;
}

glm::vec3 CameraComponent::getMovementUpVec() const { return m_movementUpVec; }

glm::vec3 CameraComponent::getCameraForwardVec() const {
  return m_cameraForwardVec;
}

glm::vec3 CameraComponent::getCameraSidewayVec() const {
  return m_cameraSidewayVec;
}

glm::vec3 CameraComponent::getCameraUpVec() const { return m_cameraUpVec; }

glm::vec3 CameraComponent::getCameraLookVec() const { return m_cameraLookVec; }

bool CameraComponent::getIfIsTouchingGround() const {
  return m_isTouchingGround;
}

bool CameraComponent::getIfIsMoving() const { return m_isMoving; }

void CameraComponent::setCurrentLookAngleX(float newCurrentLookAngleX) {
  m_currentLookAngleX = newCurrentLookAngleX;
}

void CameraComponent::setCurrentLookAngleY(float newCurrentLookAngleY) {
  m_currentLookAngleY = newCurrentLookAngleY;
}

void CameraComponent::updatePosition(glm::vec3 movementVector) {
  m_position += movementVector;
}

void CameraComponent::setPosition(glm::vec3 newPosition) {
  m_position = newPosition;
}

void CameraComponent::setMovementForwardVec(glm::vec3 newMovementForwardVec) {
  m_movementForwardVec = newMovementForwardVec;
}

void CameraComponent::setMovementSidewayVec(glm::vec3 newMovementSidewayVec) {
  m_movementSidewayVec = newMovementSidewayVec;
}

void CameraComponent::setMovementUpVec(glm::vec3 newMovementUpVec) {
  m_movementUpVec = newMovementUpVec;
}

void CameraComponent::setCameraForwardVec(glm::vec3 newCameraForwardVec) {
  m_cameraForwardVec = newCameraForwardVec;
}

void CameraComponent::setCameraSidewayVec(glm::vec3 newCameraSidewayVec) {
  m_cameraSidewayVec = newCameraSidewayVec;
}

void CameraComponent::setCameraUpVec(glm::vec3 newCameraUpVec) {
  m_cameraUpVec = newCameraUpVec;
}

void CameraComponent::setCameraLookVec(glm::vec3 newCameraLookVec) {
  m_cameraLookVec = newCameraLookVec;
}

void CameraComponent::setIfIsTouchingGround(bool state) {
  m_isTouchingGround = state;
}

void CameraComponent::setIfIsMoving(bool state) { m_isMoving = state; }