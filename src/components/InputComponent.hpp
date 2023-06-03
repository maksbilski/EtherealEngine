#pragma once

#include <GLFW/glfw3.h>

class InputComponent {
private:
  GLFWwindow *m_Window;

  double m_MouseX;
  double m_MouseY;

  bool m_SpaceKeyPressed;
  bool m_wKeyPressed;
  bool m_sKeyPressed;
  bool m_dKeyPressed;
  bool m_aKeyPressed;

public:
  InputComponent(GLFWwindow *window);
  ~InputComponent();
  void controlMouseInput();
  void controlKeyboardInput();
  void update();
  double getTargetLookAngleX() const;
  double getTargetLookAngleY() const;
  float getJumpTimer() const;
  bool getIfSpaceKeyPressed() const;
  bool getIfwKeyPressed() const;
  bool getIfsKeyPressed() const;
  bool getIfdKeyPressed() const;
  bool getIfaKeyPressed() const;
};