#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "src/engine/IndexBuffer.hpp"
#include "src/engine/Renderer.hpp"
#include "src/engine/Shader.hpp"
#include "src/engine/Texture.hpp"
#include "src/engine/VertexArray.hpp"
#include "src/engine/VertexBuffer.hpp"
#include "src/engine/VertexBufferLayout.hpp"

#include "src/engine/IndexBuffer.hpp"
#include "src/engine/Renderer.hpp"
#include "src/engine/Shader.hpp"
#include "src/engine/Texture.hpp"
#include "src/engine/VertexArray.hpp"
#include "src/engine/VertexBuffer.hpp"
#include "src/engine/VertexBufferLayout.hpp"

#include "src/vendor/glm/glm.hpp"
#include "src/vendor/glm/gtc/matrix_transform.hpp"
#include "src/vendor/imgui/imgui.h"
#include "src/vendor/imgui/imgui_impl_glfw_gl3.h"

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
    {
        return -1;
    }

    window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
    if (!window) {
      glfwTerminate();
      return -1;
    }

    // clang-format off
    float positions[] = {-50.0f, -50.0f, +0.0f, +0.0f,
                         +50.0f, -50.0f, +1.0f, +0.0f,
                         +50.0f, +50.0f, +1.0f, +1.0f,
                         -50.0f, +50.0f, +0.0f, 1.0f};

    // clang-format on

    unsigned int indices[] = {0, 1, 2, 2, 3, 0};

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    glm::mat4 proj = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    Shader shader("resources/shaders/basic.shader");
    shader.Bind();

    shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

    Texture texture("resources/textures/senti.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    va.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();

    Renderer renderer;

    glm::vec3 translationA(200, 200, 0);
    glm::vec3 translationB(400, 200, 0);

    while (!glfwWindowShouldClose(window)) {
    }

    glfwTerminate();
    return 0;
}
