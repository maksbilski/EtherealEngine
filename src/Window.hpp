#pragma once


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vendor/stb_image/stb_image.h>

#include "Color.hpp"

#include <iostream>
#include <string>


class Window 
{
private:
    GLFWwindow* window;
    Color backgroundColor;
    unsigned int width, height;
    const std::string& title;
    bool resizeable, vsync, counter;
    float fps, ms;
    double current_time = 0.0;
    double previous_time = 0.0;
    unsigned int frames;

public:
    Window(unsigned int width, unsigned int height, const std::string title, Color backgroundColor, bool fullscreen, bool resizeable, bool vsync, bool counter);
    ~Window();


};