#include "SkyboxModelComponent.hpp"

void SkyboxModelComponent::setSkyboxModel(SkyboxModel *newSkyboxModel) {
  m_skyboxModel.reset(newSkyboxModel);
}