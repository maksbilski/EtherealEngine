#include "EntityFactory.hpp"
#include "../components/CameraComponent.hpp"
#include "../components/ModelComponent.hpp"
#include "../components/ShaderComponent.hpp"
#include "../components/SkyboxModelComponent.hpp"
#include "../components/TextureComponent.hpp"
#include "../components/TransformComponent.hpp"
#include "ResourceManager.hpp"
#include <random>

EntityFactory::EntityFactory(EntityManager &entityManager,
                             ResourceManager &resourceManager)
    : m_entityManager(entityManager), m_resourceManager(resourceManager) {}

Entity EntityFactory::getNewEntityId() { return m_nextEntity++; }

Entity EntityFactory::createRenderableEntity(EntityType entityType,
                                             glm::vec3 position,
                                             glm::vec3 rotation,
                                             glm::vec3 scale) {
  Entity newEntity = getNewEntityId();

  std::shared_ptr<Model> model;
  std::shared_ptr<Shader> shader;

  switch (entityType) {
  case EntityType::SHOTGUN:
    model = m_resourceManager.getModel(EntityType::SHOTGUN);
    shader = m_resourceManager.getShader(EntityType::SHOTGUN);
    break;
  case EntityType::TERRAIN:
    model = m_resourceManager.getModel(EntityType::TERRAIN);
    shader = m_resourceManager.getShader(EntityType::TERRAIN);
    break;
  case EntityType::FLOATING_ROCK:
    model = m_resourceManager.getModel(EntityType::FLOATING_ROCK);
    shader = m_resourceManager.getShader(EntityType::FLOATING_ROCK);
    break;
  case EntityType::EYEBEAST:
    model = m_resourceManager.getModel(EntityType::EYEBEAST);
    shader = m_resourceManager.getShader(EntityType::EYEBEAST);
    break;
  }

  m_entityManager.addComponent<ModelComponent>(newEntity,
                                               ModelComponent(model));
  m_entityManager.addComponent<ShaderComponent>(newEntity,
                                                ShaderComponent(shader));
  m_entityManager.addComponent<TransformComponent>(
      newEntity, TransformComponent(position, rotation, scale));
  m_entityManager.addRenderableEntity(newEntity);

  return newEntity;
}

void EntityFactory::createSkyboxEntity() {

  Entity newEntity = getNewEntityId();
  m_entityManager.addComponent<TextureComponent>(
      newEntity,
      TextureComponent(m_resourceManager.getTexture(EntityType::SKYBOX)));
  m_entityManager.addComponent<ShaderComponent>(
      newEntity,
      ShaderComponent(m_resourceManager.getShader(EntityType::SKYBOX)));
  m_entityManager.addComponent<SkyboxModelComponent>(
      newEntity, m_resourceManager.getSkyboxModel());
  m_entityManager.addSkyboxEntity(newEntity);
};

Entity EntityFactory::createWeaponEntity(EntityType entityType,
                                         glm::vec3 scale) {

  Entity weaponEntity = createRenderableEntity(entityType);
  m_entityManager.addComponent<WeaponComponent>(weaponEntity,
                                                WeaponComponent());
  m_entityManager.addComponent<SoundComponent>(
      weaponEntity,
      SoundComponent(m_resourceManager.getSoundBuffer(entityType), 50));
  m_entityManager.addComponent<DamageComponent>(weaponEntity,
                                                DamageComponent(100));
  m_entityManager.setCurrentWeaponEntity(weaponEntity);
  return weaponEntity;
}

Entity EntityFactory::createPlayerEntity(glm::vec3 position, glm::vec3 rotation,
                                         glm::vec3 scale) {
  Entity playerEntity = getNewEntityId();
  m_entityManager.setPlayerEntity(playerEntity);
  m_entityManager.addCameraComponent(CameraComponent(position));
  m_entityManager.addComponent<ModelComponent>(
      playerEntity, m_resourceManager.getModel(EntityType::PLAYER));
  m_entityManager.addComponent<TransformComponent>(
      playerEntity, TransformComponent(position, rotation, scale));
  m_entityManager.addComponent<HealthComponent>(playerEntity,
                                                HealthComponent(200));
  createWeaponEntity(EntityType::SHOTGUN);
  m_entityManager.addCollidableEntity(playerEntity);
  return playerEntity;
}

Entity EntityFactory::createEnemyEntity(EntityType entityType,
                                        glm::vec3 position, glm::vec3 scale) {
  Entity enemyEntity =
      createRenderableEntity(entityType, position, glm::vec3(0.0), scale);
  switch (entityType) {
  case EntityType::EYEBEAST:
    m_entityManager.addComponent<HealthComponent>(enemyEntity,
                                                  HealthComponent(200));
    m_entityManager.addComponent<DamageComponent>(enemyEntity,
                                                  DamageComponent(40));
  }
  m_entityManager.addCollidableEntity(enemyEntity);
  m_entityManager.addEnemyEntity(enemyEntity);
  return enemyEntity;
}

void EntityFactory::createRandomRenderableEntities(EntityType entityType,
                                                   unsigned int amount) {
  for (unsigned int i = 0; i < amount; i++) {
    float randomPositionX = generateRandomFloat(-2000.0f, 2000.0f);
    float randomPositionY = generateRandomFloat(
        m_entityManager.getCameraComponent().getPosition().y + 200.0f, 2000.0f);
    float randomPositionZ = generateRandomFloat(-2000.0f, 2000.0f);
    float scale = generateRandomFloat(150.0f, 200.0f);
    float randomRotationX = generateRandomFloat(-180.0f, 180.0f);
    float randomRotationY = generateRandomFloat(-180.0f, 180.0f);
    float randomRotationZ = generateRandomFloat(-180.0f, 180.0f);
    createRenderableEntity(
        entityType,
        glm::vec3(randomPositionX, randomPositionY, randomPositionZ),
        glm::vec3(randomRotationX, randomRotationY, randomRotationZ),
        glm::vec3(scale));
  }
}

void EntityFactory::createRandomEnemyEntities(EntityType entityType,
                                              unsigned int amount) {
  CameraComponent &camera = m_entityManager.getCameraComponent();
  glm::vec3 playerPosition =
      m_entityManager
          .getComponent<TransformComponent>(m_entityManager.getPlayerEntity())
          .getPosition();
  for (unsigned int i = 0; i < amount; i++) {
    float offsetX = generateRandomFloat(-2000.0f, 2000.0f);
    float offsetZ = generateRandomFloat(1000.0f, 2000.0f);

    glm::vec3 enemyPosition =
        playerPosition - offsetZ * glm::normalize(camera.getCameraForwardVec());

    enemyPosition += offsetX * camera.getCameraSidewayVec();

    enemyPosition.y += generateRandomFloat(50.0f, 100.0f);

    createEnemyEntity(entityType, enemyPosition, glm::vec3(2.0f));
  }
}

float EntityFactory::generateRandomFloat(float lower, float upper) {
  static std::random_device rd;
  static std::mt19937 engine(rd());
  std::uniform_real_distribution<float> dist(lower, upper);
  return dist(engine);
}