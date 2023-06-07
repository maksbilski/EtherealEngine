#include "../components/CameraComponent.hpp"
#include "EntityManager.hpp"
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

class InputSystem {
private:
  GLFWwindow *m_window;
  EntityManager &m_entityManager;

  float m_targetLookAngleX;
  float m_targetLookAngleY;

  double m_cursorX;
  double m_cursorY;

  float m_movementSpeed;
  float m_mouseSensitivity;

  float m_jumpTimer;

public:
  InputSystem(GLFWwindow *window, EntityManager &entityManager);
  void update(float deltaTime);
  void controlMouseInput(float deltaTime);
  void controlButtonsInput(float deltaTime);
  void controlWeaponRecoil(float deltaTime);
};