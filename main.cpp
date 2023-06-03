#include "src/systems/Entity.hpp"
#include "src/systems/InputSystem.hpp"
#include "src/systems/RenderSystem.hpp"

#include "src/engine/IndexBuffer.hpp"
#include "src/engine/Mesh.hpp"
#include "src/engine/Renderer.hpp"
#include "src/engine/Shader.hpp"
#include "src/engine/Texture.hpp"
#include "src/engine/VertexArray.hpp"
#include "src/engine/VertexBuffer.hpp"
#include "src/engine/VertexBufferLayout.hpp"

#include "src/components/CameraComponent.hpp"
#include "src/components/GraphicsComponent.hpp"
#include "src/components/TransformComponent.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void) {
  GLFWwindow *window;

  if (!glfwInit()) {
    return -1;
  }

  window = glfwCreateWindow(1920, 1080, "Game", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  glfwSwapInterval(1);

  if (glewInit() != GLEW_OK) {
    std::cout << "Error!" << std::endl;
  }
  // clang-format off
  float positions[] = {
    -50.0f, +0.0f, +50.0f, +0.0f, +0.0f,
    +50.0f, +0.0f, +50.0f, +1.0f, +0.0f,
    +50.0f, +0.0f, -50.0f, +1.0f, +1.0f,
    -50.0f, +0.0f, -50.0f, +0.0f, +1.0f
  };

  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
  };

  // clang-format on

  auto terrain = std::make_shared<Entity>();
  Texture texture("resources/textures/senti.png");
  Shader shader("resources/shaders/basic.shader");
  Mesh mesh(positions, indices);
  auto ter_graph_compon_ptr =
      std::make_unique<GraphicsComponent>(mesh, texture, shader);
  terrain->addComponent<GraphicsComponent>(std::move(ter_graph_compon_ptr));

  auto player = std::make_shared<Entity>();
  auto camera_comp_ptr =
      std::make_unique<CameraComponent>(glm::vec3(0.0f, 2.0f, 0.0f));
  player->addComponent<CameraComponent>(std::move(camera_comp_ptr));

  RenderSystem render_system(player);

  InputSystem input_system(window, player);

  render_system.addEntity(terrain);

  while (!glfwWindowShouldClose(window)) {
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
    float currentFrame = glfwGetTime();
    auto lastFrame = currentFrame;
    float deltaTime = currentFrame - lastFrame;

    // Aktualizacja systemów
    input_system.update(deltaTime);
    render_system.update();

    // Rendering
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Wymiana buforów i obsługa zdarzeń
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}