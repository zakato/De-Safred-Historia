#include <Movement\cVelocity.hpp>



namespace zkt {

	cVelocity::cVelocity(float x, float y)
	{
		m_velocity.x = x;
		m_velocity.y = y;
	}

	cVelocity::~cVelocity()
	{

	}
	
	const sf::Vector2f& cVelocity::getVelocity() const
	{
		return m_velocity;
	}

	void cVelocity::setVelocity(float x, float y)
	{
		m_velocity.x = x;
		m_velocity.y = y;
	}

}