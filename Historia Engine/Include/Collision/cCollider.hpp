#ifndef CCOLIDER_HPP
#define CCOLIDER_HPP

#include <Artemis\Component.hpp>

#include <SFML\Graphics\Rect.hpp>

#include <Movement\cTransform.hpp>

#include <memory>




namespace zkt {

	class cCollider : public artemis::Component
	{
	public:
		cCollider(cTransform* transform);
		~cCollider();
		void setFloatRect(const sf::FloatRect& boxCollider);
		const sf::FloatRect& getFloatRect() const;
		void setCTransform(cTransform* transform);
		cTransform* getCTransform() const;
		bool isTrigger() const;
		void setTrigger(bool isTrigger);

	private:
		sf::FloatRect  m_boxCollider;
		cTransform*	   m_transform;
		bool		   m_isTrigger;
	};
}

#endif