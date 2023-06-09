#include "RenderSystem.hpp"
#include "../components/CameraComponent.hpp"
#include "../components/ModelComponent.hpp"
#include "../components/ShaderComponent.hpp"
#include "../components/SkyboxModelComponent.hpp"
#include "../components/TransformComponent.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"

const float WEAPON_BOB_AMOUNT = 1.0f;

RenderSystem::RenderSystem(EntityManager &entityManager)
    : m_entityManager(entityManager) {
  float fov = glm::radians(45.0f);
  float aspectRatio = 1920.0f / 1080.0f;
  float near = 0.1f;
  float far = 10000.0f;
  m_projectionMatrix = glm::perspective(fov, aspectRatio, near, far);
}

RenderSystem::~RenderSystem() {}

void RenderSystem::update() {
  updateWeaponTransformMatrix();
  updateViewMatrix();
  for (const auto &entity : m_entityManager.getEntitesToRender()) {
    renderModel(entity);
  }
  renderSkybox(m_entityManager.getCurrentSkyboxEntity());
  renderCrosshairEntity(m_entityManager.getCrosshairEntity());
}

void RenderSystem::renderModel(const Entity &entity) const {
  auto entityModel =
      m_entityManager.getComponent<ModelComponent>(entity).m_model;
  auto entityShader =
      m_entityManager.getComponent<ShaderComponent>(entity).m_shader;
  auto transformComponent =
      m_entityManager.getComponent<TransformComponent>(entity);

  glm::mat4 modelMatrix;
  glm::mat4 viewMatrix;

  if (entity == m_entityManager.getCurrentWeaponEntity()) {
    modelMatrix = m_weaponTransformMatrix;
    viewMatrix = m_viewMatrix;
    viewMatrix[3] = glm::vec4(0.0, 0.0, 0.0, 1.0);
  } else {
    modelMatrix = transformComponent.createTransformMatrix();
    viewMatrix = m_viewMatrix;
  }
  setupShader(entityShader, modelMatrix);

  entityModel->draw(*entityShader);
}

void RenderSystem::renderSkybox(const Entity &renderedSkyboxEntity) const {
  auto skyboxShader =
      m_entityManager.getComponent<ShaderComponent>(renderedSkyboxEntity)
          .m_shader;
  auto skyboxModel =
      m_entityManager.getComponent<SkyboxModelComponent>(renderedSkyboxEntity)
          .m_skyboxModel;
  auto skyboxTexture =
      m_entityManager.getComponent<TextureComponent>(renderedSkyboxEntity)
          .getTextureID();
  glDepthFunc(GL_LEQUAL);

  glm::vec3 cameraPos = m_entityManager.getCameraComponent().getPosition();
  float scaleSize = 1000.0f;

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, cameraPos);
  model = glm::scale(model, glm::vec3(scaleSize));
  setupShader(skyboxShader, model);

  skyboxModel->draw(skyboxModel->getSkyboxVAOid(), skyboxTexture);
};

void RenderSystem::updateViewMatrix() {
  m_viewMatrix =
      glm::lookAt(m_entityManager.getCameraComponent().getPosition(),
                  m_entityManager.getCameraComponent().getCameraLookVec(),
                  glm::vec3(0.0f, 1.0f, 0.0f));
}

void RenderSystem::updateWeaponTransformMatrix() {
  const glm::vec3 weaponPositionBaseOffset = glm::vec3(5.0f, -7.0f, 11.0f);
  auto weaponPosition =
      (m_entityManager.getCameraComponent().getCameraForwardVec() *
       weaponPositionBaseOffset.z) +
      (m_entityManager.getCameraComponent().getCameraSidewayVec() *
       weaponPositionBaseOffset.x) +
      (m_entityManager.getCameraComponent().getCameraUpVec() *
       weaponPositionBaseOffset.y) +
      m_entityManager.getCameraComponent().getPosition();

  weaponPosition += m_entityManager.getCameraComponent().getCameraUpVec() *
                    m_entityManager
                        .getComponent<WeaponComponent>(
                            m_entityManager.getCurrentWeaponEntity())
                        .getWeaponRecoilAmount() *
                    0.6f;
  weaponPosition +=
      (m_entityManager.getCameraComponent().getCameraSidewayVec() *
       m_entityManager
           .getComponent<WeaponComponent>(
               m_entityManager.getCurrentWeaponEntity())
           .getWeaponBobAmount() *
       WEAPON_BOB_AMOUNT) -
      (m_entityManager.getCameraComponent().getCameraUpVec() *
       abs(m_entityManager
               .getComponent<WeaponComponent>(
                   m_entityManager.getCurrentWeaponEntity())
               .getWeaponBobAmount()) *
       WEAPON_BOB_AMOUNT);

  glm::mat4 weaponTransformMatrix;
  weaponTransformMatrix[0] = glm::vec4(
      m_entityManager.getCameraComponent().getCameraSidewayVec(), 0.0);
  weaponTransformMatrix[1] =
      glm::vec4(m_entityManager.getCameraComponent().getCameraUpVec(), 0.0);
  weaponTransformMatrix[2] = glm::vec4(
      m_entityManager.getCameraComponent().getCameraForwardVec(), 0.0f);
  weaponTransformMatrix[3] = glm::vec4(weaponPosition, 1.0f);

  weaponTransformMatrix = glm::scale(weaponTransformMatrix, glm::vec3(1.2f));

  weaponTransformMatrix =
      glm::rotate(weaponTransformMatrix,
                  (m_entityManager
                       .getComponent<WeaponComponent>(
                           m_entityManager.getCurrentWeaponEntity())
                       .getWeaponRecoilAmount() *
                   -25.0f),
                  glm::vec3(1.0, 0.0, 0.0));

  m_weaponTransformMatrix = weaponTransformMatrix;
}

void RenderSystem::setupShader(std::shared_ptr<Shader> &shader,
                               const glm::mat4 &modelMatrix) const {
  shader->use();
  shader->setMat4("model", modelMatrix);
  shader->setMat4("view", m_viewMatrix);
  shader->setMat4("projection", m_projectionMatrix);
};

void RenderSystem::renderCrosshairEntity(Entity crosshairEntity) const {
  float size = 1.5f;
  float vertices[] = {-size, size,  0.0f, size,  size,  0.0f,
                      size,  -size, 0.0f, -size, -size, 0.0f};

  unsigned int indices[] = {0, 1, 2, 0, 2, 3};

  unsigned int vbo, vao, ebo;
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);

  auto crosshairShader =
      m_entityManager.getComponent<ShaderComponent>(crosshairEntity).m_shader;

  crosshairShader->use();
  crosshairShader->setVec2("screenDimensions", glm::vec2(1920.0f, 1080.0f));

  glm::mat4 modelMatrix = glm::translate(
      glm::mat4(1.0f), glm::vec3(1920.0f / 2, 1080.0f / 2, 0.0f));

  glm::mat4 viewMatrix = glm::mat4(1.0f);
  glm::mat4 projectionMatrix =
      glm::ortho(0.0f, 1920.0f, 1080.0f, 0.0f, -1.0f, 1.0f);
  glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
  crosshairShader->setMat4("mvpMatrix", mvpMatrix);

  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  glDeleteBuffers(1, &ebo);
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
}
