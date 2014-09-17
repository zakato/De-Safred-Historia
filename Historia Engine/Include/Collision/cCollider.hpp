#ifndef CCOLIDER_HPP
#define CCOLIDER_HPP

#include <Artemis\Component.hpp>

#include <SFML\Graphics\Rect.hpp>

#include <Movement\cTransform.hpp>

#include <Collision\BoxCollider.hpp>

#include <memory>
#include <functional>




namespace zkt {

	class cCollider : public artemis::Component
	{
	public:
		cCollider() {}
		~cCollider() {}
		void setCollider(const BoxCollider& collider) { m_collider = collider; }
		 BoxCollider& getCollider()  { return m_collider; }
		bool isTrigger() const { return m_isTrigger; }
		void setTrigger(bool isTrigger) { m_isTrigger = isTrigger; }
		void setCollision(bool hasCollided) { m_hasCollided = hasCollided; }
		bool getHasCollided() const { return m_hasCollided; }

	private:
		BoxCollider  m_collider;
		
		bool		 m_isTrigger;
		bool		 m_hasCollided;
	};
}

#endif