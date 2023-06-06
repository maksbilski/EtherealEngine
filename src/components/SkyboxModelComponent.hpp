#pragma once

#include "../engine/SkyboxModel.hpp"
#include <memory>

class SkyboxModelComponent {
public:
  std::shared_ptr<SkyboxModel> m_SkyboxModel;

  SkyboxModelComponent(std::shared_ptr<SkyboxModel> skyboxModel)
      : m_SkyboxModel(skyboxModel){};

  void setSkyboxModel(SkyboxModel *newSkyboxModel) {
    m_SkyboxModel.reset(newSkyboxModel);
  }
};
