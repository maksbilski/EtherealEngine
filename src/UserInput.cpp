#include "UserInput.hpp"


bool UserInput::getKey(int key)
{
    return glfwGetKey(window, key);
}

bool UserInput::getMouseButton(int button) 
{
    return glfwGetMouseButton(window, button);
}

void UserInput::getMousePosition(double* x, double* y)
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