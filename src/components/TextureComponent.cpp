#include "TextureComponent.hpp"

void TextureComponent::setTexture(TextureID newTexture) {
  m_texture = newTexture;
};

TextureID TextureComponent::getTextureID() const { return m_texture; };