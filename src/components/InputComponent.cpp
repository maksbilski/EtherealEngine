#include "InputComponent.hpp"

InputComponent::InputComponent(GLFWwindow *window) : m_Window(window) {

  m_SpaceKeyPressed = false;
  m_wKeyPressed = false;
  m_sKeyPressed = false;
  m_dKeyPressed = false;
  m_aKeyPressed = false;

  glfwGetCursorPos(window, &m_MouseX, &m_MouseY);
}

InputComponent::~InputComponent() {}