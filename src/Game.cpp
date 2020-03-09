#include "Game.h"


sf::RenderWindow window;

class Engine {
public:

	void run()
	{
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();

			for (const auto& nowObject : GameObject)
			{
				nowObject->draw();
				nowObject->phisyc();
				nowObject->logic();
				nowObject->intercept(...);
			}

			window.display();
		}

	}
	//void addObject(Object* o);
	//
	//private:
	//std::vector<Object*> objects;
}


























	class phystech
	{
	public:
		std::vector<double> position;
		std::vector<double> velocity;
		std::vector<double> acceleration;
		std::vector<double> mass;
		sf::Sprite spr;
		void Draw();
		void Move();
		void Collide(phystech* that);
		void shoot();




	};


	class bullet
	{
	public:
		std::vector<double> position;
		std::vector<double> velocity;
		std::vector<double> acceleration;
		std::vector<double> mass;
		sf::Sprite spr;
		int damage;
		phystech* owner;



		void Draw();
		void Move();
		void Collide(phystech* that);


	};



	class GameObject
	{
	public:
		std::vector<double> position;
		std::vector<double> velocity;
		std::vector<double> acceleration;
		std::vector<double> mass;
		sf::Sprite spr;


		void Draw();
		void Move();
		void Collide(phystech* that);
	};




	void Process(GameObject *o)
	{
		o->Draw();
		o->Move();
	}















	int main()
	{

		DrawWindow();


		//DrawPict();

		//DrawTexture(XCOORD, YCOORD);

	//	UseThread();

	}



	void DrawPict()
	{
		sf::Window window(sf::VideoMode(600, 800), "PICTURE");

		window.setPosition(sf::Vector2i(30, 30));
		window.setSize(sf::Vector2u(300, 300));

		while (window.isOpen())              // game loop
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
		}

	}


	void DrawWindow()
	{




		sf::RenderWindow window(sf::VideoMode(400, 400), "Purple Cycle!", sf::Style::Default);


		window.setPosition(sf::Vector2i(30, 30));
		window.setSize(sf::Vector2u(300, 300));



		sf::CircleShape  shape(200.f);
		shape.setFillColor(sf::Color::Magenta);


		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();
			window.draw(shape);
			window.display();
		}
	}




	void UseThread()
	{

		sf::Thread thread(&DrawFunc);

		thread.launch();

		thread.wait(); // for using one after one

		for (int i = 0; i < 2; ++i)
			std::cout << "I'm the main thread" << std::endl;

		system("pause");

	}




	void DrawFunc()
	{
		for (int i = 0; i < 3; ++i)
			std::cout << "I'm thread number one" << std::endl;
	}


	void DrawTexture(float x, float y)
	{
		sf::Texture texture;
		texture.loadFromFile("texture.png");

		sf::RenderWindow window(sf::VideoMode(400, 400), "It is anything new....");


		sf::Sprite sprite(texture);
		sprite.setPosition(x, y);
		sprite.setColor(sf::Color::Blue);
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			window.clear();
			window.draw(sprite);
			window.display();
		}

	}

