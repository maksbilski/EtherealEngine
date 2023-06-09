#pragma once

#include <memory>

typedef unsigned int TextureID;

class TextureComponent {
  /**
   * @class TextureComponent
   * @brief Represents a component that holds a texture for rendering.
   *
   * The TextureComponent class is used to associate a texture with skybox. It
   * stores a texture ID, which is an unsigned integer representing the
   * identifier of the texture used for rendering. The component allows setting
   * and retrieving the texture associated with the rendering component.
   */
private:
  TextureID m_texture;

public:
  TextureComponent(TextureID texture) : m_texture(texture){};

  void setTexture(TextureID newTexture);

  TextureID getTextureID() const;
};
