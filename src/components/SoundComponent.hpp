#pragma once
#include <SFML/Audio.hpp>
#include <memory>
class SoundComponent {
private:
  std::shared_ptr<sf::SoundBuffer> m_soundBuffer;
  sf::Sound m_sound;
  unsigned int m_volume;

public:
  SoundComponent(std::shared_ptr<sf::SoundBuffer> soundBuffer,
                 unsigned int volume = 100);
  void playSound();
};