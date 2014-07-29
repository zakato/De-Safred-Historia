#include <Movement\cTransform.hpp>



namespace zkt {

	cTransform::cTransform() :  m_transform(),
								m_inverseTransform(),
								m_position(0, 0),
								m_origin(0, 0),
								m_previousPosition(0, 0),
								m_scale(1, 1),
								m_rotation(0.f),
								m_isInverseTransformNeedUpdate(true),
								m_isTransformNeedUpdate(true)
								{}



	cTransform::~cTransform()
	{}


	void cTransform::setPosition(float x, float y)
	{
		m_previousPosition = m_position;
		m_position.x = x; 
		m_position.y = y; 
		m_isTransformNeedUpdate = true;
		m_isInverseTransformNeedUpdate = true;
	}


	const sf::Vector2f& cTransform::getPosition() const 
		{ 
		return m_position;
		}


	void cTransform::setRotation(float angle)
	{ 
		m_rotation = static_cast<float>(fmod(angle, 360));
		if (m_rotation < 0)
			m_rotation += 360.f;

		m_isTransformNeedUpdate = true;
		m_isInverseTransformNeedUpdate = true;
	}

	float cTransform::getRotation() const
	{
		return m_rotation;
	}

	void cTransform::setScale(float factorX, float factorY) 
	{ 
		m_scale.x = factorX;
		m_scale.y = factorY;
		m_isTransformNeedUpdate = true;
		m_isInverseTransformNeedUpdate = true;
	}

	const sf::Vector2f& cTransform::getScale() const 
	{ 
		return m_scale;
	}
	
	void cTransform::setOrigin(float x, float y) 
	{ 
		m_origin.x = x;
		m_origin.y = y; 
		m_isTransformNeedUpdate = true;
		m_isInverseTransformNeedUpdate = true;
	}

	const sf::Vector2f& cTransform::getOrigin() const
	{
		return m_origin;
	}


	void cTransform::move(float x, float y) 
	{
		setPosition(m_position.x + x, m_position.y + y);
	}

	void cTransform::rotate(float angle) 
	{
		setRotation(m_rotation + angle);
	}

	void cTransform::scale(float factorX, float factorY)
	{
		setScale(m_scale.x * factorX, m_scale.y * factorY * m_scale.y);
	}

	void cTransform::setToPreviousPosition()
	{ 
		m_position = m_previousPosition;
	}

	const sf::Transform& cTransform::getTransform() const
	{
		if (m_isTransformNeedUpdate)
		{
			float angle = -m_rotation * 3.141592654f / 180.f;
			float cosine = static_cast<float>(std::cos(angle));
			float sine = static_cast<float>(std::sin(angle));
			float sxc = m_scale.x * cosine;
			float syc = m_scale.y * cosine;
			float sxs = m_scale.x * sine;
			float sys = m_scale.y * sine;
			float tx = -m_origin.x * sxc - m_origin.y * sys + m_position.x;
			float ty = m_origin.x * sxs - m_origin.y * syc + m_position.y;

			m_transform = sf::Transform(sxc, sys, tx,
				-sxs, syc, ty,
				0.f, 0.f, 1.f);
			m_isTransformNeedUpdate = false;
		}
		
		return m_transform;
	}


	const sf::Transform& cTransform::getInverseTransform() const
	{
		if (m_isInverseTransformNeedUpdate)
		{
			m_inverseTransform = getTransform().getInverse();
			m_isInverseTransformNeedUpdate = false;
		}

		return m_inverseTransform;
	}

}