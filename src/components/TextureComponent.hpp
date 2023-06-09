#pragma once

#include <memory>

typedef unsigned int TextureID;

class TextureComponent {
private:
  TextureID m_texture;

public:
  TextureComponent(TextureID texture) : m_texture(texture){};

  void setTexture(TextureID newTexture);

  TextureID getTextureID() const;
};
