#pragma once

#include "../engine/Model.hpp"
#include "../engine/Shader.hpp"
#include <memory>

class GraphicsComponent {
public:
  // Referencje do meshu, tekstury i shadera
  std::shared_ptr<Model> m_Model;
  std::shared_ptr<Shader> m_Shader;

  GraphicsComponent(std::shared_ptr<Model> model,
                    std::shared_ptr<Shader> shader)
      : m_Model(model), m_Shader(shader){};

  void setModel(Model *newModel) { m_Model.reset(newModel); }

  void setShader(Shader *newShader) { m_Shader.reset(newShader); }
};
