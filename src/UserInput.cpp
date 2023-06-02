#include "UserInput.hpp"


bool UserInput::getKey(int key) const
{
    return glfwGetKey(window, key);
}

bool UserInput::getMouseButton(int button) const 
{
    return glfwGetMouseButton(window, button);
}

void UserInput::getMousePosition(double* x, double* y) const
{
    glfwGetCursorPos(window, x, y);
}

void UserInput::setMousePostiion(double x, double y)
{
    glfwSetCursorPos(window, x, y);
}

void UserInput::setMouseVisible(bool visible)
{
    glfwSetInputMode(window, GLFW_CURSOR, !visible ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL);
}