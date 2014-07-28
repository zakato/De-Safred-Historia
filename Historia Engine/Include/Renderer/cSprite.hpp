#include <Artemis\Component.hpp>

#include <SFML\Graphics\Sprite.hpp>
#include <iostream>
#include <string>

namespace zkt {

	class cSprite : public artemis::Component {

	public:
		cSprite(sf::Sprite* sprite) { m_sprite = sprite; }
		sf::Sprite* getSprite() {  return m_sprite; }
		 void setSprite(sf::Sprite* sprite) {   m_sprite = sprite; }


	private:
		sf::Sprite* m_sprite;
	
	};

}