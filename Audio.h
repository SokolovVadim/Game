#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace au {
	class Audio
	{
	public:

		Audio();
		~Audio();


		void loadSounds(std::vector<std::string> & strVec);



	private:
		std::vector<sf::SoundBuffer> v_buffers_;
		std::vector<sf::Sound> v_sounds_;

	};
}