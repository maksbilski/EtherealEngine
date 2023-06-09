#include "SoundComponent.hpp"
#include <random>

SoundComponent::SoundComponent(
    std::shared_ptr<std::vector<sf::SoundBuffer>> soundBuffer,
    unsigned int volume)
    : m_soundBuffers(soundBuffer), m_volume(volume) {
  m_sound.setBuffer((*m_soundBuffers)[0]);
  m_sound.setVolume(volume);
}

void SoundComponent::playSound() { m_sound.play(); }

void SoundComponent::playRandomSound() {
  m_sound.setBuffer((*m_soundBuffers)[getRandomInt((*m_soundBuffers).size())]);
  playSound();
}

int SoundComponent::getRandomInt(int upperBound) const {
  static std::random_device rd;
  static std::mt19937 gen(rd());

  std::uniform_int_distribution<> distr(0, upperBound);

  return distr(gen);
}