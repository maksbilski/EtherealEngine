#include "src/systems/EntityFactory.hpp"
#include "src/systems/EntityManager.hpp"
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

  Mesh mesh(positions, 20, indices, 6);

  CameraComponent camera(glm::vec3(0.0f, 2.0f, 0.0f));
  EntityManager entity_manager;
  entity_manager.addCameraComponent(camera);
  EntityFactory entity_factory(entity_manager);
  Entity terrain = entity_factory.createRenderableEntity(
      "resources/shaders/basic.shader", "resources/textures/senti.png", mesh);
  RenderSystem render_system(entity_manager);

  InputSystem input_system(window, entity_manager);

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