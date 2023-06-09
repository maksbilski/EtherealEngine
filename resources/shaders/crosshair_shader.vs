#version 330 core

layout (location = 0) in vec3 aPosition;
uniform mat4 mvpMatrix;
out vec3 FragPos;

void main()
{
    gl_Position = mvpMatrix * vec4(aPosition, 1.0);
    FragPos = aPosition;
}
