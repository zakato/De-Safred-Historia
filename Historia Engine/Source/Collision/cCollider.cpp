#include <Collision\cCollider.hpp>



namespace zkt {

	cCollider::cCollider(cTransform* transform)
		: m_boxCollider()
		, m_isTrigger(false)
		, m_transform(transform)
	{
	}

	cCollider::~cCollider()
	{

	}

	void cCollider::setFloatRect(const sf::FloatRect& boxCollider)
	{
		m_boxCollider = boxCollider;
	}

	const sf::FloatRect& cCollider::getFloatRect() const
	{
		return m_boxCollider;
	}

	void cCollider::setCTransform(cTransform* transform)
	{
		m_transform = transform;
	}

	cTransform* cCollider::getCTransform() const
	{
		return m_transform;
	}

	bool cCollider::isTrigger() const
	{
		return m_isTrigger;
	}

	void cCollider::setTrigger(bool isTrigger)
	{
		m_isTrigger = isTrigger;
	}





}