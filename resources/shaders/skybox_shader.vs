#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;  // Add the model uniform

void main()
{
    TexCoords = aPos;
    mat4 rotation = mat4(mat3(model));  // Convert the model matrix to a 3x3 matrix, removing the translation.
    vec4 pos = projection * view * rotation * vec4(aPos, 1.0); // Multiply with rotation matrix for scaling
    gl_Position = pos.xyww;
}
