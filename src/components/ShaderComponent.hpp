#pragma once

#include "../engine/Shader.hpp"
#include <memory>

class ShaderComponent {
public:
  std::shared_ptr<Shader> m_Shader;

  ShaderComponent(std::shared_ptr<Shader> shader) : m_Shader(shader){};

  void setShader(Shader *newShader) { m_Shader.reset(newShader); }
};
