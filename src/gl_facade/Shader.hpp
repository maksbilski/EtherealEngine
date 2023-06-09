#pragma once

#include "../vendor/glm/glm.hpp"
#include <GL/glew.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader {
  /**
   * @class Shader
   * @brief Represents a shader program used for rendering.
   *
   * The Shader class encapsulates the functionality of a shader program used
   * for rendering in OpenGL. It provides methods to load and use shader
   * programs, as well as set uniform values for the shaders.
   *
   * The class requires paths to vertex and fragment shader files for
   * initialization. Optionally, a geometry shader path can be provided as well.
   *
   * The class provides methods to activate and use the shader program for
   * rendering. It also includes methods to set various types of uniform values,
   * such as booleans, integers, floats, vectors (2D, 3D, and 4D), and matrices
   * (2x2, 3x3, and 4x4).
   *
   * Note: The class assumes the usage of the GLEW library for OpenGL-related
   * functionality. It relies on the glm library for mathematical operations and
   * matrix transformations. The shader files are expected to be written in GLSL
   * (OpenGL Shading Language).
   */

public:
  unsigned int m_ID;
  Shader(const char *vertexPath, const char *fragmentPath,
         const char *geometryPath = nullptr);
  void use();
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setVec2(const std::string &name, const glm::vec2 &value) const;
  void setVec2(const std::string &name, float x, float y) const;
  void setVec3(const std::string &name, const glm::vec3 &value) const;
  void setVec3(const std::string &name, float x, float y, float z) const;
  void setVec4(const std::string &name, const glm::vec4 &value) const;
  void setVec4(const std::string &name, float x, float y, float z,
               float w) const;
  void setMat2(const std::string &name, const glm::mat2 &mat) const;
  void setMat3(const std::string &name, const glm::mat3 &mat) const;
  void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
  void checkCompileErrors(GLuint shader, std::string type);
};
