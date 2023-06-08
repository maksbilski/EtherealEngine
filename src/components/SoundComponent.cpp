#include "SoundComponent.hpp"

SoundComponent::SoundComponent(std::shared_ptr<sf::SoundBuffer> soundBuffer,
                               unsigned int volume)
    : m_soundBuffer(soundBuffer), m_volume(volume) {
  m_sound.setBuffer(*soundBuffer);
  m_sound.setVolume(volume);
}

void SoundComponent::playSound() { m_sound.play(); }