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

  float m_jumpTimer;
  float m_jumpVelocity;

public:
  InputSystem(GLFWwindow *window, EntityManager &entityManager);
  void update(float deltaTime);
  void controlMouseInput();
  void controlButtonsInput(float deltaTime);
  void controlWeaponRecoil(float deltaTime);
  void controlWeaponBobbing(float deltaTime);
};