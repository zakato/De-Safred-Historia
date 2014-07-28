#include <SFML\Graphics.hpp>
#include <Game.hpp>


namespace zkt {

	class Application {
	
	public:
		Application();
		void Start();
		void Run();

	private:
		sf::RenderWindow m_window;
		Game* m_game;
		//Statestack

	};
}