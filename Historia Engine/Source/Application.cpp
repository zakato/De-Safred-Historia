#include <Application.hpp>




namespace zkt {


	Application::Application()
		: m_window(sf::VideoMode(1024, 768), "Graphics", sf::Style::Close)
	{
		m_game = new Game(&m_window);
	}

	void Application::Start()
	{
		m_game->Start();
	}

	void Application::Run()
	{


			sf::Clock clock;
			sf::Time timeSinceLastUpdate = sf::Time::Zero;
			const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

			while (m_window.isOpen())
			{
				sf::Event event;
				while (m_window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						m_window.close();
					if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
						m_window.close();
				}

			sf::Time elapsedTime = clock.restart();
			timeSinceLastUpdate += elapsedTime;
			while (timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;
				m_game->Update(TimePerFrame);
			}
		}

	}

}