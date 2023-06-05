#include "src/systems/EntityFactory.hpp"
#include "src/systems/EntityManager.hpp"
#include "src/systems/InputSystem.hpp"
#include "src/systems/RenderSystem.hpp"

#include "src/engine/Mesh.hpp"
#include "src/engine/Shader.hpp"

#include "src/components/CameraComponent.hpp"
#include "src/components/GraphicsComponent.hpp"
#include "src/components/TransformComponent.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id,
                                GLenum severity, GLsizei length,
                                const GLchar *message, const void *userParam) {
  fprintf(stderr,
          "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
          (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity,
          message);
}

// Then, in your main function or initialization code:
void InitOpenGLDebug() {
  // Enable the debug output
  glEnable(GL_DEBUG_OUTPUT);

  // Set your callback function
  glDebugMessageCallback(MessageCallback, 0);
}

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
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  InitOpenGLDebug();
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  ResourceManager resource_manager;
  CameraComponent camera(glm::vec3(0.0f, 0.0f, 3.0f));
  EntityManager entity_manager;
  entity_manager.addCameraComponent(camera);
  EntityFactory entity_factory(entity_manager, resource_manager);

  glm::vec3 position4 = glm::vec3(1.0, -1.0, -3.0);
  glm::vec3 rotation4 = glm::vec3(0.0, 0.0, 0.0);
  glm::vec3 scale4 = glm::vec3(0.01);

  entity_factory.createRenderableEntity(EntityType::TERRAIN, position4,
                                        rotation4, scale4);

  RenderSystem render_system(entity_manager);

  InputSystem input_system(window, entity_manager);

  while (!glfwWindowShouldClose(window)) {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Aktualizacja systemów
    input_system.update(deltaTime);
    render_system.update();

    // Rendering

    // Wymiana buforów i obsługa zdarzeń
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}