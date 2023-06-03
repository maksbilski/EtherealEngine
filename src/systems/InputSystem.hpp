#include "../components/CameraComponent.hpp"
#include "Entity.hpp"
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

class InputSystem {
private:
  GLFWwindow *m_Window;
  std::shared_ptr<Entity> &m_Player;

  float m_TargetLookAngleX;
  float m_TargetLookAngleY;

  double m_CursorX;
  double m_CursorY;

  float m_MovementSpeed;
  float m_MouseSensitivity;

  float m_JumpTimer;

public:
  InputSystem(GLFWwindow *window, std::shared_ptr<Entity> player);
  void update(float deltaTime);
  void controlMouseInput(float deltaTime);
  void controlKeyboardInput(float deltaTime);
};