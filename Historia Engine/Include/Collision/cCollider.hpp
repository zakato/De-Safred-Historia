#ifndef CCOLIDER_HPP
#define CCOLIDER_HPP

#include <Artemis\Component.hpp>

#include <SFML\Graphics\Rect.hpp>

#include <memory>




namespace zkt {

	class cCollider : public artemis::Component
	{
	public:
		cCollider(sf::FloatRect boxCollider);
		~cCollider();


	private:
		sf::FloatRect  m_boxCollider;
	};
}

#endif