#pragma once

#include "../gl_facade/Shader.hpp"
#include <memory>

class ShaderComponent {
  /**
   * @class ShaderComponent
   * @brief Represents a component that holds a shader for rendering.
   *
   * The ShaderComponent class is used to associate a shader with a rendering component or entity in a game or simulation.
   * It holds a shared pointer to a Shader object, which represents the shader used for rendering.
   * The component allows setting and retrieving the shader associated with the rendering component.
   * The shader defines the rendering behavior, including vertex transformations, fragment coloring, and other effects.
   */
public:
  std::shared_ptr<Shader> m_shader;

  ShaderComponent(std::shared_ptr<Shader> shader) : m_shader(shader){};

  void setShader(Shader *newShader);
};
