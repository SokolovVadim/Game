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

		size = size_;

		while (size--)
		{
			v_bools_.push_back(false);
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

	void Audio::setPlay(const int number, const bool isPlay)
	{
		v_bools_[number] = isPlay;
	}

	//-------------------------------------------------------------------------

	const bool Audio::isPlay(const int number) const
	{
		return v_bools_[number];
	}

	//-------------------------------------------------------------------------

	bool Audio::isPlay()
	{
		for (int i(0); i < this->size_; ++i)
		{
			if (v_sounds_[i].getStatus() == sf::Sound::Playing)
				return true;
		}
		return false;
	}

	//-------------------------------------------------------------------------

	void Audio::playSound(int number)
	{
		//v_sounds_[number].play();
		if(v_sounds_[number].getStatus() != sf::Sound::Playing)
		{
			v_sounds_[number].play();
		}
		//v_sounds_[number].setLoop(true);
		
		//v_sounds_[number].setMinDistance(1000);
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