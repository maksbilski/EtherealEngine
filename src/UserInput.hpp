#pragma once

#include <GLFW/glfw3.h>

class UserInput 
{
private:
    GLFWwindow* window;

public:
    UserInput(GLFWwindow* window) : window(window) {};

    bool getKey(int key);
    bool getMouseButton(int button);
    void getMousePosition(double* x, double* y);
    void setMousePostiion(double x, double y);
    void setMouseVisible(bool visible);
};