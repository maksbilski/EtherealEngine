#pragma once

#include "../engine/Shader.hpp"
#include <memory>

class ShaderComponent {
public:
  std::shared_ptr<Shader> m_shader;

  ShaderComponent(std::shared_ptr<Shader> shader) : m_shader(shader){};

  void setShader(Shader *newShader);
};
