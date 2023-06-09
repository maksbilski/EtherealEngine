#include "../components/CameraComponent.hpp"
#include "EntityManager.hpp"
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

class InputSystem {
  /**
   * @class InputSystem
   * @brief Handles input and updating player and camera movement in a game.
   *
   * The InputSystem class is responsible for handling input and controlling
   * player in a game. It utilizes the GLFW library for window and input
   * management and the EntityManager to access and manipulate entities.
   *
   * The class provides methods to update the input system and control various
   * aspects of the entities. The update method should be called regularly to
   * handle input and update entity controls.
   *
   * The class manages mouse input to control the camera's look angles.
   * It also handles button inputs, such as jumping, and controls related to
   * shooting, weapon recoil and bobbing.
   */

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
  void update();
  void controlMouseInput();
  void controlButtonsInput();
  void controlWeaponRecoil();
  void controlWeaponBobbing();
};