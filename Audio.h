#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

namespace au {
	class Audio
	{
	public:

		Audio();
		Audio(std::size_t size);
		~Audio();

		void loadSounds(std::vector<std::string> & strVec);
		void playSound(int number);
		void playAllSounds();

	private:
		std::size_t size_;
		std::vector<sf::SoundBuffer> v_buffers_;
		std::vector<sf::Sound> v_sounds_;

	};
}