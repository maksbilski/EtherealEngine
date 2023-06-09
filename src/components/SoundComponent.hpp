#pragma once
#include <SFML/Audio.hpp>
#include <memory>
class SoundComponent {
private:
  /**
   * @class SoundComponent
   * @brief Represents a component for playing sounds.
   *
   * The SoundComponent class is used to manage the playback of sounds in a game
   * or application. It holds a shared pointer to a vector of sound buffers,
   * which represent the audio data of the entity. The component allows playing
   * individual sounds or playing a random sound from the sound buffers. The
   * volume of the played sounds can be adjusted using the provided volume
   * parameter.
   */
  std::shared_ptr<std::vector<sf::SoundBuffer>> m_soundBuffers;
  sf::Sound m_sound;
  unsigned int m_volume;

public:
  SoundComponent(std::shared_ptr<std::vector<sf::SoundBuffer>> soundBuffers,
                 unsigned int volume = 100);
  void playSound();
  void playRandomSound();
  void playZeroSound();
  int getRandomInt(int lowerBound, int upperBound) const;
};