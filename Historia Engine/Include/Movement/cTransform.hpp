#ifndef CTRANSFORM_HPP
#define CTRANSFORM_HPP

#include <Artemis\Component.hpp>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Transform.hpp>


namespace zkt {

	class cTransform : public artemis::Component
	{

	public:
		cTransform();
		~cTransform();
		void setPosition(float x, float y);
		const sf::Vector2f& getPosition() const;
		void setRotation(float angle);
		float getRotation() const;
		void setScale(float factorX, float factorY);
		const sf::Vector2f& getScale() const;
		void setOrigin(float x, float y);
		const sf::Vector2f& getOrigin() const;
		void move(float x, float y);
		void rotate(float angle);
		void scale(float factorX, float factorY);
		void setToPreviousPosition();
		const sf::Transform& getTransform() const;
		const sf::Transform& getInverseTransform() const;

	private:
		mutable sf::Transform	     m_transform;
		mutable sf::Transform	     m_inverseTransform;
		sf::Vector2f				 m_origin;                 
		sf::Vector2f			     m_position;                 
		sf::Vector2f				 m_previousPosition;
		sf::Vector2f				 m_scale;                     
		float						 m_rotation;
		mutable bool				 m_isTransformNeedUpdate;
		mutable bool				 m_isInverseTransformNeedUpdate;
	};


}

#endif