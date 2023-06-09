#include "src/systems/CollisionSystem.hpp"
#include "src/systems/EnemyAISystem.hpp"
#include "src/systems/EntityFactory.hpp"
#include "src/systems/EntityManager.hpp"
#include "src/systems/InputSystem.hpp"
#include "src/systems/RenderSystem.hpp"

#include "src/gl_facade/Mesh.hpp"
#include "src/gl_facade/Shader.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id,
//                                 GLenum severity, GLsizei length,
//                                 const GLchar *message, const void *userParam)
//                                 {
//   fprintf(stderr,
//           "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
//           (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type,
//           severity, message);
// }

// void InitOpenGLDebug() {
//   glEnable(GL_DEBUG_OUTPUT);

//   glDebugMessageCallback(MessageCallback, 0);
// }

int main(void) {
  GLFWwindow *window;

  if (!glfwInit()) {
    return -1;
  }

  window = glfwCreateWindow(800, 600, "Game", NULL, NULL);
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
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  // InitOpenGLDebug();
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  ResourceManager resourceManager;
  EntityManager entityManager;
  EntityFactory entityFactory(entityManager, resourceManager);
  entityFactory.createPlayerEntity(glm::vec3(0.0, 14.0, 20.0), glm::vec3(0.0),
                                   glm::vec3(1.0));

  glm::vec3 terrainPosition = glm::vec3(0.0, 0.0, 0.0);
  glm::vec3 terrainRotation = glm::vec3(0.0, 0.0, 0.0);
  glm::vec3 terrainScale = glm::vec3(3.0);

  entityFactory.createRenderableEntity(EntityType::TERRAIN, terrainPosition,
                                       terrainRotation, terrainScale);
  entityFactory.createSkyboxEntity();
  entityFactory.createRandomRenderableEntities(EntityType::FLOATING_ROCK, 200);
  entityFactory.createRandomEnemyEntities(EntityType::EYEBEAST, 10);

  RenderSystem renderSystem(entityManager);

  InputSystem inputSystem(window, entityManager);

  CollisionSystem collisionSystem(entityManager);

  EnemyAISystem enemyAISystem(entityManager);

  sf::Music backgroundMusic;

  if (!backgroundMusic.openFromFile("resources/sounds/music.wav"))
    std::cout << "Error! Music not opened!" << std::endl;

  backgroundMusic.setLoop(true);
  backgroundMusic.play();

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    collisionSystem.update();
    inputSystem.update();
    enemyAISystem.update();
    renderSystem.update();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}