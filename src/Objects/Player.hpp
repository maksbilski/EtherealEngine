#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Player 
{
private:
    GLFWwindow* window;
    World* world;

    glm::vec3 pos;
    glm::vec3 forwardVec;   //this is for player vertical position
    glm::vec3 sidewayVec;   //this is for player horizontal position
    glm::vec3 upVec;    //this is for player position, to determine position while fe. jumping

    glm::vec3 cameraForward;
    glm::vec3 cameraSideway;
    glm::vec3 cameraUp;
    glm::vec3 camreaLook;

    float jumpTimer;
    float gravity;
    bool isMoving;
    bool isTouchingGround;
public:
    static const float heightOfView;
    Player();

};