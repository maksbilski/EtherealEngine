#pragma once

#include "../engine/Model.hpp"
#include <memory>

class ModelComponent {
public:
  std::shared_ptr<Model> m_model;

  ModelComponent(std::shared_ptr<Model> model) : m_model(model){};
  void setModel(Model *newModel) { m_model.reset(newModel); }
};