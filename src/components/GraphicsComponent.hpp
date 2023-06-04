#pragma once

#include "../engine/Model.hpp"
#include "../engine/Shader.hpp"

class GraphicsComponent {
public:
  // Referencje do meshu, tekstury i shadera
  Model &m_Model;
  Shader &m_Shader;

  // Konstruktor, który przyjmuje referencje do meshu, tekstury i shadera
  GraphicsComponent(Model &model, Shader &shader)
      : m_Model(model), m_Shader(shader) {}

  // Setter functions

  void setModel(Model &newModel) { m_Model = newModel; }

  void setShader(Shader &newShader) { m_Shader = newShader; }
};
