#include "src/systems/CollisionSystem.hpp"
#include "src/systems/EnemyAISystem.hpp"
#include "src/systems/EnemySpawnSystem.hpp"
#include "src/systems/EntityFactory.hpp"
#include "src/systems/EntityManager.hpp"
#include "src/systems/HealthSystem.hpp"
#include "src/systems/InputSystem.hpp"
#include "src/systems/RenderSystem.hpp"

#include "src/gl_facade/Mesh.hpp"
#include "src/gl_facade/Shader.hpp"

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
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  ResourceManager resourceManager;
  EntityManager entityManager;
  EntityFactory entityFactory(entityManager, resourceManager);
  entityFactory.createPlayerEntity(glm::vec3(0.0, 14.0, 0.0), glm::vec3(0.0),
                                   glm::vec3(1.0));

  glm::vec3 terrainPosition = glm::vec3(0.0, 0.0, 0.0);
  glm::vec3 terrainRotation = glm::vec3(0.0, 0.0, 0.0);
  glm::vec3 terrainScale = glm::vec3(3.0);

  entityFactory.createRenderableEntity(EntityType::TERRAIN, terrainPosition,
                                       terrainRotation, terrainScale);
  entityFactory.createSkyboxEntity();
  entityFactory.createRandomRenderableEntities(EntityType::FLOATING_ROCK, 200);

  RenderSystem renderSystem(entityManager);

  InputSystem inputSystem(window, entityManager);

  CollisionSystem collisionSystem(entityManager);

  EnemyAISystem enemyAISystem(entityManager);

  HealthSystem healthSystem(entityManager);

  EnemySpawnSystem enemySpawnSystem(entityManager, entityFactory);

  sf::Music backgroundMusic;

  if (!backgroundMusic.openFromFile("resources/sounds/music.wav"))
    std::cout << "Error! Music not opened!" << std::endl;

  backgroundMusic.setLoop(true);
  backgroundMusic.play();

  double startTime = glfwGetTime();

  while (!glfwWindowShouldClose(window)) {
    double currentTime = glfwGetTime();
    double elapsedTime = currentTime - startTime;
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    collisionSystem.update();
    inputSystem.update();
    enemySpawnSystem.update(elapsedTime);
    enemyAISystem.update();
    healthSystem.update();
    renderSystem.update();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}