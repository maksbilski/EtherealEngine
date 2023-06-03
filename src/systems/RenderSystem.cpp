#include "RenderSystem.hpp"
#include "../components/GraphicsComponent.hpp"
#include "../components/TransformComponent.hpp"
#include "Entity.hpp"
#include <glm/gtc/matrix_transform.hpp>

void RenderSystem::update(float deltaTime) {
  for (const auto &entity : entities) {
    render(entity);
  }
}

void RenderSystem::render(const std::shared_ptr<Entity> &entity) {
  // Pobierz komponenty
  auto graphics = entity->getComponent<GraphicsComponent>();
  auto transform = entity->getComponent<TransformComponent>();

  // Utwórz MVP
  glm::mat4 model = transform->createTransformMatrix();
  glm::mat4 MVP = projectionMatrix * viewMatrix * model; // zmienne globalne

  // Aktywuj shader
  graphics->shader->use();

  // Prześlij MVP do shadera
  GLint mvpLocation = glGetUniformLocation(graphics->shader->getID(), "MVP");
  glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(MVP));

  // Renderuj obiekt
  graphics->mesh->draw();
}
