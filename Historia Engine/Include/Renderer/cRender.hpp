#ifndef CRENDER_H
#define CRENDER_H

#include <Artemis\Component.hpp>

#include <SFML\Graphics\Sprite.hpp>

namespace zkt
{

	class cRender : public artemis::Component
	{
	public:
		cRender() : m_sprite(nullptr) {}
		sf::Sprite* getSprite() const { return m_sprite; }
		void setSprite(sf::Sprite* sprite) { m_sprite = sprite; }
	
	private:
		sf::Sprite* m_sprite;
	};
}

#endif