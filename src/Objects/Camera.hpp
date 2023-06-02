#pragma once

#include <GLFW/glfw3.h>

#include "../vendor/glm/glm.hpp"

class Camera {
private:
  GLFWwindow *m_Window;

  glm::vec3 m_Position;
  glm::vec3 m_ForwardVec;
  glm::vec3 m_SidewayVec;
  glm::vec3 m_UpVec;

  glm::vec3 m_CameraForward;
  glm::vec3 m_CameraSideway;
  glm::vec3 m_CameraUp;
  glm::vec3 m_CameraLook;

  float m_JumpTimer;
  float m_Gravity;
  bool m_IsMoving;
  bool m_IsTouchingGround;

  double m_OldMouseX;
  double m_OldMouseY;
  float m_TargetLookAngleX;
  float m_TargetLookAngleY;

  float m_LookAngleX;
  float m_LookAngleY;

  void computeWalkVectors();
  void controlMouseInput(float deltaTime);
  void controlMovement(float deltaTime);

public:
  Camera(GLFWwindow *window, glm::vec3 position);
  ~Camera();

  void update(float deltaTime);

  void computeCameraOrientation();

  glm::vec3 getPosition() const;
  void setPosition(glm::vec3 newPosition);

  glm::vec3 getCameraLook() const;
  glm::vec3 getCameraUp() const;
  glm::vec3 getCameraSide() const;

  bool isCameraMoving() const;
};