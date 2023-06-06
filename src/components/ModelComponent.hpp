#pragma once

#include "../engine/Model.hpp"
#include <memory>

class ModelComponent {
public:
  std::shared_ptr<Model> m_Model;

  ModelComponent(std::shared_ptr<Model> model) : m_Model(model){};
  void setModel(Model *newModel) { m_Model.reset(newModel); }
};