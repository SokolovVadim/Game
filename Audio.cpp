#include "Audio.h"


namespace au {


	Audio::Audio()
		//buffer_(sf::SoundBuffer())
	{}

	//-------------------------------------------------------------------------

	Audio::Audio(std::size_t size) :
		size_(size)
	{
		//std::vector<sf::Sound>::iterator		itS;
		while (size--)
		{
			v_sounds_.push_back(*(new sf::Sound()));
			//itS++;
		}

		//std::vector<sf::SoundBuffer>::iterator itSB = v_buffers_.begin();

		size = size_;

		while (size--/*itSB != v_buffers_.end()*/)
		{
			v_buffers_.push_back(*(new sf::SoundBuffer()));

			//itSB++;
		}

	}

	//-------------------------------------------------------------------------

	Audio::~Audio()
	{}

	//-------------------------------------------------------------------------

	void Audio::loadSounds(std::vector<std::string> & strVec)
	{
		//v_sounds_.push_back(*(new sf::Sound()));

		std::vector<std::string>::iterator		itStr	= strVec.begin();
		std::vector<sf::Sound>::iterator		itS		= v_sounds_.begin();
		std::vector<sf::SoundBuffer>::iterator	itSB	= v_buffers_.begin();

		for (; itSB != v_buffers_.end(); itSB++, itStr++, itS++)
		{
			if (!itSB->loadFromFile("Music/" + *itStr))
			{
				std::cout << "Audio loading error!" << std::endl;
			}
			itS->setBuffer(*itSB);
		}
		
	}

	//-------------------------------------------------------------------------

	void Audio::playSound(int number)
	{
		v_sounds_[number].play();
	}

	//-------------------------------------------------------------------------

	void Audio::playAllSounds()
	{
		std::vector<sf::Sound>::iterator		itS = v_sounds_.begin();
		while (itS != v_sounds_.end())
		{
			itS->play();
			itS++;
		}
	}

}