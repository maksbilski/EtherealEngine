#include "../components/CameraComponent.hpp"
#include "EntityManager.hpp"
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

class InputSystem {
private:
  GLFWwindow *m_Window;
  EntityManager &m_EntityManager;

  float m_TargetLookAngleX;
  float m_TargetLookAngleY;

  double m_CursorX;
  double m_CursorY;

  float m_MovementSpeed;
  float m_MouseSensitivity;

  float m_JumpTimer;

public:
  InputSystem(GLFWwindow *window, EntityManager &entityManager);
  void update(float deltaTime);
  void controlMouseInput(float deltaTime);
  void controlKeyboardInput(float deltaTime);
  void updateWeaponTransform();
};