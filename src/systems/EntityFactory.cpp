#include "EntityFactory.hpp"
#include "../components/ModelComponent.hpp"
#include "../components/ShaderComponent.hpp"
#include "../components/SkyboxModelComponent.hpp"
#include "../components/TextureComponent.hpp"
#include "../components/TransformComponent.hpp"
#include "ResourceManager.hpp"
#include <random>

EntityFactory::EntityFactory(EntityManager &entityManager,
                             ResourceManager &resourceManager)
    : m_EntityManager(entityManager), m_ResourceManager(resourceManager) {}

Entity EntityFactory::getNewEntityId() { return m_NextEntity++; }

Entity EntityFactory::createRenderableEntity(EntityType entityType,
                                             glm::vec3 position,
                                             glm::vec3 rotation,
                                             glm::vec3 scale) {
  Entity newEntity = getNewEntityId();

  std::shared_ptr<Model> model;
  std::shared_ptr<Shader> shader;

  switch (entityType) {
  case EntityType::SHOTGUN:
    model = m_ResourceManager.getModel(EntityType::SHOTGUN);
    shader = m_ResourceManager.getShader(EntityType::SHOTGUN);
    break;
  case EntityType::TERRAIN:
    model = m_ResourceManager.getModel(EntityType::TERRAIN);
    shader = m_ResourceManager.getShader(EntityType::TERRAIN);
    break;
  }

  m_EntityManager.addComponent<ModelComponent>(newEntity,
                                               ModelComponent(model));
  m_EntityManager.addComponent<ShaderComponent>(newEntity,
                                                ShaderComponent(shader));
  m_EntityManager.addComponent<TransformComponent>(
      newEntity, TransformComponent(position, rotation, scale));
  m_EntityManager.addRenderableEntity(newEntity);

  return newEntity;
}

void EntityFactory::createSkyboxEntity() {

  Entity newEntity = getNewEntityId();
  m_EntityManager.addComponent<TextureComponent>(
      newEntity,
      TextureComponent(m_ResourceManager.getTexture(EntityType::SKYBOX)));
  m_EntityManager.addComponent<ShaderComponent>(
      newEntity,
      ShaderComponent(m_ResourceManager.getShader(EntityType::SKYBOX)));
  m_EntityManager.addComponent<SkyboxModelComponent>(
      newEntity, m_ResourceManager.getSkyboxModel());
  m_EntityManager.addSkyboxEntity(newEntity);
};

Entity EntityFactory::createWeaponEntity(EntityType entityType,
                                         glm::vec3 scale) {

  Entity weaponEntity = createRenderableEntity(entityType);
  m_EntityManager.addComponent<WeaponComponent>(weaponEntity,
                                                WeaponComponent());
  m_EntityManager.setCurrentWeaponEntity(weaponEntity);
  return weaponEntity;
}

void EntityFactory::createRandomRenderableEntities(EntityType entityType,
                                                   unsigned int amount) {
  for (int i = 0; i < amount; i++) {
    float randomPositionX = generateRandomFloat(
        m_EntityManager.getCameraComponent().getPosition().x, 30.0f);
    float randomPositionY = generateRandomFloat(
        m_EntityManager.getCameraComponent().getPosition().y + 5.0f, 70.0f);
    float randomPositionZ = generateRandomFloat(
        m_EntityManager.getCameraComponent().getPosition().z, 30.0f);
    float scale = generateRandomFloat(0.01, 0.09);
    createRenderableEntity(
        entityType,
        glm::vec3(randomPositionX, randomPositionY, randomPositionZ),
        glm::vec3(0.0f), glm::vec3(scale));
  }
}

float EntityFactory::generateRandomFloat(float lower, float upper) {
  static std::random_device rd;
  static std::mt19937 engine(rd());
  std::uniform_real_distribution<float> dist(lower, upper);
  return dist(engine);
}