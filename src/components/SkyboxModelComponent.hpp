#pragma once

#include "../gl_facade/SkyboxModel.hpp"
#include <memory>

class SkyboxModelComponent {
public:
  std::shared_ptr<SkyboxModel> m_skyboxModel;

  SkyboxModelComponent(std::shared_ptr<SkyboxModel> skyboxModel)
      : m_skyboxModel(skyboxModel){};

  void setSkyboxModel(SkyboxModel *newSkyboxModel);
};
