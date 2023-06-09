#version 330 core

out vec4 FragColor;
in vec3 FragPos;

void main()
{
    float distance = length(FragPos.xy - vec2(0.5, 0.5));
    if (distance < 0.02) {
        FragColor = vec4(1.0, 1.0, 0.0, 1.0);
    } else {
        discard;
    }
}
