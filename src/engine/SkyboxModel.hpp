#pragma once

#include <GL/glew.h>

#include "Shader.hpp"

class SkyboxModel {
private:
  unsigned int m_SkyboxVAOid, m_SkyboxVBOid;

public:
  SkyboxModel();
  ~SkyboxModel();
  void draw(unsigned int skyboxVAOid, unsigned int textureID) const;
  unsigned int getSkyboxVAOid() const;
};