#ifndef BOXCOLLIDER_HPP
#define BOXCOLLIDER_HPP

#include <SFML\Graphics\Rect.hpp>


namespace zkt {

	class BoxCollider {

	public:
		BoxCollider() {}
		void setBoxCollider(const sf::FloatRect boxCollider) { m_boxCollider = boxCollider; }
		 sf::FloatRect& getBoxCollider()  { return m_boxCollider; }
		 void setPosition(float x, float y)	{ m_boxCollider.left = x - m_boxCollider.width / 2; m_boxCollider.top = y - m_boxCollider.height / 2 ; }

	private:
		sf::FloatRect m_boxCollider;
	};
}


#endif