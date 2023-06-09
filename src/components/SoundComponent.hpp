#pragma once
#include <SFML/Audio.hpp>
#include <memory>
class SoundComponent {
private:
  std::shared_ptr<std::vector<sf::SoundBuffer>> m_soundBuffers;
  sf::Sound m_sound;
  unsigned int m_volume;

public:
  SoundComponent(std::shared_ptr<std::vector<sf::SoundBuffer>> soundBuffers,
                 unsigned int volume = 100);
  void playSound();
  void playRandomSound();
  int getRandomInt(int lowerBound, int upperBound) const;
};