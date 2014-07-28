#ifndef BOOK_GAMESTATE_HPP
#define GAMESTATE_HPP

#include "State.hpp"
#include <Artemis\World.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

namespace zkt
{
	using namespace artemis;

class GameState : public State
{
	public:
							GameState(StateStack& stack, Context context);

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleEvent(const sf::Event& event);


	private:
		World				m_world;
		
};

}

#endif