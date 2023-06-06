#include "SkyboxModel.hpp"

SkyboxModel::~SkyboxModel(){};

SkyboxModel::SkyboxModel() {
  // clang-format off
  float skyboxVertices[] = {
    // positions
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    +1.0f, -1.0f, -1.0f,
    +1.0f, -1.0f, -1.0f,
    +1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, +1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, +1.0f, -1.0f,
    -1.0f, +1.0f, -1.0f,
    -1.0f, +1.0f, +1.0f,
    -1.0f, -1.0f, +1.0f,

    +1.0f, -1.0f, -1.0f,
    +1.0f, -1.0f, +1.0f,
    +1.0f, +1.0f, +1.0f,
    +1.0f, +1.0f, +1.0f,
    +1.0f, +1.0f, -1.0f,
    +1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f, +1.0f,
    -1.0f, +1.0f, +1.0f,
    +1.0f, +1.0f, +1.0f,
    +1.0f, +1.0f, +1.0f,
    +1.0f, -1.0f, +1.0f,
    -1.0f, -1.0f, +1.0f,

    -1.0f, +1.0f, -1.0f,
    +1.0f, +1.0f, -1.0f,
    +1.0f, +1.0f, +1.0f,
    +1.0f, +1.0f, +1.0f,
    -1.0f, +1.0f, +1.0f,
    -1.0f, +1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, +1.0f,
    +1.0f, -1.0f, -1.0f,
    +1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, +1.0f,
    +1.0f, -1.0f, +1.0f
  };
  // clang-format on
  glGenVertexArrays(1, &m_SkyboxVAOid);
  glGenBuffers(1, &m_SkyboxVBOid);
  glBindVertexArray(m_SkyboxVAOid);
  glBindBuffer(GL_ARRAY_BUFFER, m_SkyboxVBOid);
  glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices,
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
}

unsigned int SkyboxModel::getSkyboxVAOid() const { return m_SkyboxVAOid; };

void SkyboxModel::draw(unsigned int skyboxVAOid, unsigned int textureID) const {
  glBindVertexArray(skyboxVAOid);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
  glDepthFunc(GL_LESS); // set depth function back to default
};
