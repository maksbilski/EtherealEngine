#pragma once

#include "../gl_facade/SkyboxModel.hpp"
#include <memory>

class SkyboxModelComponent {
  /**
   * @class SkyboxModelComponent
   * @brief Represents a component that holds a skybox model for rendering.
   *
   * The SkyboxModelComponent class is used to associate a skybox model with skybox entity.
   * It holds a shared pointer to a SkyboxModel object, which represents the skybox model used for rendering.
   * The skybox model defines the visual representation of sky surrounding the scene.
   * It is used to create the illusion of a distant background and add realism to the overall rendering.
   */
public:
  std::shared_ptr<SkyboxModel> m_skyboxModel;

  SkyboxModelComponent(std::shared_ptr<SkyboxModel> skyboxModel)
      : m_skyboxModel(skyboxModel){};

  void setSkyboxModel(SkyboxModel *newSkyboxModel);
};
