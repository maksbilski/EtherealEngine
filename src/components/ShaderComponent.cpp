#include "ShaderComponent.hpp"

void ShaderComponent::setShader(Shader *newShader) {
  m_shader.reset(newShader);
}