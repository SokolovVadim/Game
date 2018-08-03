
#pragma once


// Bug: when Space key is pressed, it does not output "Pressed"

void HitDetectorEvent(Player & Hero, bool & isHit, sf::Event & event)
{
	if (event.type == sf::Event::KeyPressed) {

		std::cout << "Pressed!" << std::endl;

		if ((event.key.code == sf::Keyboard::Space))
		{
			if (isHit == false)
			{
				std::cout << "Hitted!" << std::endl;
				isHit = true;
				Hero.SetHit();

				poolEn.isAttacked(Hero);
			}

		}
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		isHit = false;
	}
}

// But in this function key detection works correctly


void HitDetector(Player & Hero, bool & isHit, sf::Event & event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		
		std::cout << "Pressed!" << std::endl;

		if (isHit == false)
		{
			std::cout << "Hitted!" << std::endl;
			isHit = true;
			Hero.SetHit();

			poolEn.isAttacked(Hero);
		}

		
	}
}