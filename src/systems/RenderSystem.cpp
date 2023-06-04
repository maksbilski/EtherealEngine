#include "RenderSystem.hpp"
#include "../components/CameraComponent.hpp"
#include "../components/GraphicsComponent.hpp"
#include "../components/TransformComponent.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"

RenderSystem::RenderSystem(EntityManager &entityManager)
    : m_EntityManager(entityManager) {
  float fov = glm::radians(45.0f);
  float aspectRatio = 1920.0f / 1080.0f;
  float near = 0.1f;
  float far = 100.0f;
  m_ProjectionMatrix = glm::perspective(fov, aspectRatio, near, far);
}

RenderSystem::~RenderSystem() {}

void RenderSystem::update() {
  updateViewMatrix();
  for (auto entity : m_EntityManager.getEntitesToRender()) {
    render(entity);
  }
}

void RenderSystem::render(Entity entity) {
  // Retrieve components
  auto graphics = m_EntityManager.getComponent<GraphicsComponent>(entity);
  auto transform = m_EntityManager.getComponent<TransformComponent>(entity);

  // Create MVP
  glm::mat4 model = transform.createTransformMatrix();
  glm::mat4 MVP = m_ProjectionMatrix * m_ViewMatrix * model; // Global variables

  // Set the MVP matrix in the shader program
  graphics.m_Shader->use();
  graphics.m_Shader->setMat4("MVP", MVP);

  // Now draw the model
  graphics.m_Model->Draw(*graphics.m_Shader);
}

void RenderSystem::updateViewMatrix() {
  m_ViewMatrix =
      glm::lookAt(m_EntityManager.getCameraComponent().getPosition(),
                  m_EntityManager.getCameraComponent().getCameraLookVec(),
                  glm::vec3(0.0f, 1.0f, 0.0f));
}
