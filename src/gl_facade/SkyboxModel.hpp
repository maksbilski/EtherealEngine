#pragma once

#include <GL/glew.h>

#include "Shader.hpp"

class SkyboxModel {
  /**
   * @class SkyboxModel
   * @brief Represents a skybox model used for rendering.
   *
   * The SkyboxModel class encapsulates the functionality of a skybox model used
   * for rendering a skybox in OpenGL. It provides methods to draw the skybox
   * and retrieve the skybox VAO ID.
   *
   * The class internally manages a VAO (Vertex Array Object) and a VBO (Vertex
   * Buffer Object) for rendering the skybox.
   *
   * The draw method allows rendering the skybox using a given skybox VAO ID and
   * texture ID. The skybox VAO ID should be obtained from the class instance
   * using the `getSkyboxVAOid` method.
   *
   * Note: The class assumes the usage of the GLEW library for OpenGL-related
   * functionality. The `Shader` class is expected to be provided for rendering
   * the skybox.
   */
private:
  unsigned int m_skyboxVAOid, m_skyboxVBOid;

public:
  SkyboxModel();
  ~SkyboxModel();
  void draw(unsigned int skyboxVAOid, unsigned int textureID) const;
  unsigned int getSkyboxVAOid() const;
};