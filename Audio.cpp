#include "Audio.h"


namespace au {


	Audio::Audio()
		//buffer_(sf::SoundBuffer())
	{}

	//if (!buffer_.loadFromFile())

	Audio::~Audio()
	{}





	void Audio::loadSounds(std::vector<std::string> & strVec)
	{
		v_sounds_.push_back(*(new sf::Sound()));

		std::vector<std::string>::iterator itStr = strVec.begin();
		std::vector<sf::Sound>::iterator itS = v_sounds_.begin();
		std::vector<sf::SoundBuffer>::iterator itSB = v_buffers_.begin();

		for (; itSB != v_buffers_.end(); itSB++, itStr++, itS++)
		{
			itSB->loadFromFile(*itStr);
			itS->setBuffer(*itSB);
		}

		
	}




}