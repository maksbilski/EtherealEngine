#pragma once

#include "../gl_facade/Model.hpp"
#include <memory>

class ModelComponent {
  /**
   * @class ModelComponent
   * @brief Represents a component that holds a 3D model for an entity.
   *
   * The ModelComponent class is used to associate a 3D model with an entity in
   * a game or simulation. It holds a shared pointer to a Model object, which
   * represents the 3D model. The component allows setting and retrieving the
   * model associated with the entity. The model represents the visual
   * representation of the entity in the 3D world.
   */
public:
  std::shared_ptr<Model> m_model;

  ModelComponent(std::shared_ptr<Model> model) : m_model(model){};
  void setModel(Model *newModel);
};