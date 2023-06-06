#pragma once

#include <memory>

typedef unsigned int TextureID;

class TextureComponent {
private:
  TextureID m_Texture;

public:
  TextureComponent(TextureID texture) : m_Texture(texture){};

  void setTexture(TextureID newTexture) { m_Texture = newTexture; };

  TextureID getTextureID() const { return m_Texture; };
};
