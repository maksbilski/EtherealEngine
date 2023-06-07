#pragma once

#include <memory>

typedef unsigned int TextureID;

class TextureComponent {
private:
  TextureID m_texture;

public:
  TextureComponent(TextureID texture) : m_texture(texture){};

  void setTexture(TextureID newTexture) { m_texture = newTexture; };

  TextureID getTextureID() const { return m_texture; };
};
