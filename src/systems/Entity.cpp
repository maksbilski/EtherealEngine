// #include "Entity.hpp"

// template <typename T> void Entity::addComponent(std::unique_ptr<T> component)
// {
//   components[typeid(T).name()] = std::move(component);
// }

// template <typename T> T *Entity::getComponent() {
//   auto it = components.find(typeid(T).name());
//   if (it == components.end()) {
//     throw std::runtime_error("Component doesn't exist");
//   }
//   return static_cast<T *>(it->second.get());
// }
