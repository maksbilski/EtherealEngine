#include "RenderSystem.hpp"
#include "../components/CameraComponent.hpp"
#include "../components/ModelComponent.hpp"
#include "../components/ShaderComponent.hpp"
#include "../components/SkyboxModelComponent.hpp"
#include "../components/TransformComponent.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"

RenderSystem::RenderSystem(EntityManager &entityManager)
    : m_EntityManager(entityManager) {
  float fov = glm::radians(45.0f);
  float aspectRatio = 1920.0f / 1080.0f;
  float near = 0.1f;
  float far = 10000.0f;
  m_ProjectionMatrix = glm::perspective(fov, aspectRatio, near, far);
}

RenderSystem::~RenderSystem() {}

void RenderSystem::update() {
  updateWeaponTransformMatrix();
  updateViewMatrix();
  for (auto entity : m_EntityManager.getEntitesToRender()) {
    renderModel(entity);
  }
  renderSkybox(m_EntityManager.getCurrentSkyboxEntity());
}

void RenderSystem::renderModel(Entity entity) {
  // Retrieve components
  auto entity_model =
      m_EntityManager.getComponent<ModelComponent>(entity).m_Model;
  auto entity_shader =
      m_EntityManager.getComponent<ShaderComponent>(entity).m_Shader;
  auto transform = m_EntityManager.getComponent<TransformComponent>(entity);

  glm::mat4 model;
  glm::mat4 view;

  if (entity == m_EntityManager.getCurrentWeaponEntity()) {
    model = m_WeaponTransformMatrix;
    view = m_ViewMatrix;
    view[3] = glm::vec4(0.0, 0.0, 0.0, 1.0);
  } else {
    model = transform.createTransformMatrix();
    view = m_ViewMatrix;
  }
  entity_shader->use();
  // Create MVP
  // Set the MVP matrix in the shader program
  entity_shader->setMat4("projection", m_ProjectionMatrix);
  entity_shader->setMat4("view", m_ViewMatrix);
  entity_shader->setMat4("model", model);

  // Now draw the model
  entity_model->Draw(*entity_shader);
}

void RenderSystem::renderSkybox(Entity renderedSkyboxEntity) {
  auto skybox_shader =
      m_EntityManager.getComponent<ShaderComponent>(renderedSkyboxEntity)
          .m_Shader;
  auto skybox_model =
      m_EntityManager.getComponent<SkyboxModelComponent>(renderedSkyboxEntity)
          .m_SkyboxModel;
  auto skybox_texture =
      m_EntityManager.getComponent<TextureComponent>(renderedSkyboxEntity)
          .getTextureID();
  glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when
                          // values are equal to depth buffer's content

  glm::vec3 cameraPos = m_EntityManager.getCameraComponent().getPosition();
  float scaleSize = 1000.0f; // Adjust as needed for your skybox size

  glm::mat4 model = glm::mat4(1.0f);        // Initialize to identity
  model = glm::translate(model, cameraPos); // Translate to camera position
  model = glm::scale(model, glm::vec3(scaleSize)); // Scale to a large size
  skybox_shader->use();

  skybox_shader->setMat4("view", m_ViewMatrix);
  skybox_shader->setMat4("projection", m_ProjectionMatrix);

  skybox_model->draw(skybox_model->getSkyboxVAOid(), skybox_texture);
};

void RenderSystem::updateViewMatrix() {
  m_ViewMatrix =
      glm::lookAt(m_EntityManager.getCameraComponent().getPosition(),
                  m_EntityManager.getCameraComponent().getCameraLookVec(),
                  glm::vec3(0.0f, 1.0f, 0.0f));
}

void RenderSystem::updateWeaponTransformMatrix() {
  const glm::vec3 weaponPositionBaseOffset = glm::vec3(5.0f, -7.0f, 11.0f);
  auto weaponPosition =
      (m_EntityManager.getCameraComponent().getCameraForwardVec() *
       weaponPositionBaseOffset.z) +
      (m_EntityManager.getCameraComponent().getCameraSidewayVec() *
       weaponPositionBaseOffset.x) +
      (m_EntityManager.getCameraComponent().getCameraUpVec() *
       weaponPositionBaseOffset.y) +
      m_EntityManager.getCameraComponent().getPosition();

  glm::mat4 weaponTransformMatrix;
  weaponTransformMatrix[0] = glm::vec4(
      m_EntityManager.getCameraComponent().getCameraSidewayVec(), 0.0);
  weaponTransformMatrix[1] =
      glm::vec4(m_EntityManager.getCameraComponent().getCameraUpVec(), 0.0);
  weaponTransformMatrix[2] = glm::vec4(
      m_EntityManager.getCameraComponent().getCameraForwardVec(), 0.0f);
  weaponTransformMatrix[3] = glm::vec4(weaponPosition, 1.0f);

  weaponTransformMatrix = glm::scale(weaponTransformMatrix, glm::vec3(1.2f));

  weaponTransformMatrix = glm::rotate(weaponTransformMatrix, glm::radians(0.0f),
                                      glm::vec3(0.0, 1.0, 0.0));

  m_WeaponTransformMatrix = weaponTransformMatrix;
}