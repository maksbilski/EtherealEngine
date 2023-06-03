#include "../components/CameraComponent.hpp"
#include <GLFW/glfw3.h>
#include <vector>

class InputSystem {
private:
  GLFWwindow *m_Window;
  CameraComponent &m_Camera;

  float m_TargetLookAngleX;
  float m_TargetLookAngleY;

  double m_CursorX;
  double m_CursorY;

  float m_MovementSpeed;
  float m_MouseSensitivity;

  float m_JumpTimer;

public:
  InputSystem(GLFWwindow *window, CameraComponent &camera);
  void update(float deltaTime);
  void controlMouseInput(float deltaTime);
  void controlKeyboardInput(float deltaTime);
};