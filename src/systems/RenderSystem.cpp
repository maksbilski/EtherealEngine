#include "RenderSystem.hpp"
#include "../components/CameraComponent.hpp"
#include "../components/ModelComponent.hpp"
#include "../components/ShaderComponent.hpp"
#include "../components/TransformComponent.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"

RenderSystem::RenderSystem(EntityManager &entityManager)
    : m_EntityManager(entityManager) {
  float fov = glm::radians(45.0f);
  float aspectRatio = 1920.0f / 1080.0f;
  float near = 0.1f;
  float far = 300.0f;
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
  auto entity_model =
      m_EntityManager.getComponent<ModelComponent>(entity).m_Model;
  auto entity_shader =
      m_EntityManager.getComponent<ShaderComponent>(entity).m_Shader;
  auto transform = m_EntityManager.getComponent<TransformComponent>(entity);

  glm::mat4 model;
  glm::mat4 view;

  if (entity == m_EntityManager.getCurrentWeaponEntity()) {
    model = transform.getWeaponTransformMatrix();
    view = m_ViewMatrix;
    view[3] = glm::vec4(0.0, 0.0, 0.0, 1.0);
  } else {
    model = transform.createTransformMatrix();
    view = m_ViewMatrix;
  }
  graphics.m_Shader->use();
  // Create MVP
  // Set the MVP matrix in the shader program
  entity_shader->setMat4("projection", m_ProjectionMatrix);
  entity_shader->setMat4("view", m_ViewMatrix);
  entity_shader->setMat4("model", model_matrix);

  // Now draw the model
  entity_model->Draw(*entity_shader);
}

void RenderSystem::updateViewMatrix() {
  m_ViewMatrix =
      glm::lookAt(m_EntityManager.getCameraComponent().getPosition(),
                  m_EntityManager.getCameraComponent().getCameraLookVec(),
                  glm::vec3(0.0f, 1.0f, 0.0f));
}
