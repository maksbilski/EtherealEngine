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
  updateViewMatrix();
}

RenderSystem::~RenderSystem() {}

void RenderSystem::update() {
  for (auto entity : m_EntityManager.getEntitesToRender()) {
    render(entity);
  }
}

void RenderSystem::render(Entity entity) {
  // Pobierz komponenty
  auto graphics = m_EntityManager.getComponent<GraphicsComponent>(entity);
  auto transform = m_EntityManager.getComponent<TransformComponent>(entity);

  // Utwórz MVP
  glm::mat4 model = transform.createTransformMatrix();
  glm::mat4 MVP = m_ProjectionMatrix * m_ViewMatrix * model; // zmienne globalne

  VertexArray va;
  VertexBuffer vb(graphics.mesh.m_Vertices, 5 * 4 * sizeof(float));

  VertexBufferLayout layout;
  layout.Push<float>(3);
  layout.Push<float>(2);
  va.AddBuffer(vb, layout);

  IndexBuffer ib(graphics.mesh.m_Indices, 6);
  // Aktywuj shader
  graphics.shader.Bind();
  graphics.texture.Bind();

  // Prześlij MVP do shadera
  graphics.shader.SetUniformMat4f("u_MVP", MVP);
  GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
};

void RenderSystem::updateViewMatrix() {
  m_ViewMatrix =
      glm::lookAt(m_EntityManager.getCameraComponent().getPosition(),
                  m_EntityManager.getCameraComponent().getCameraLookVec(),
                  glm::vec3(0.0f, 1.0f, 0.0f));
}
