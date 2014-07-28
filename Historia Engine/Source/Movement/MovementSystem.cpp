#include <Movement\MovementSystem.hpp>

namespace zkt {

	MovementSystem::MovementSystem()
		
	{
		addComponentType<cTransform>();
		addComponentType<cVelocity>();
		m_friction = 0;
	}
		
	void MovementSystem::initialize() {
		m_velocityMapper.init(*world);
		m_transformMapper.init(*world);
	};

	void MovementSystem::processEntity(artemis::Entity &e) {
		m_transformMapper.get(e)->move(m_velocityMapper.get(e)->getVelocity().x * world->getDelta().asSeconds(), 
										m_velocityMapper.get(e)->getVelocity().y * world->getDelta().asSeconds());
		m_velocityMapper.get(e)->setVelocity(m_velocityMapper.get(e)->getVelocity().x * m_friction,
			m_velocityMapper.get(e)->getVelocity().y * m_friction);
	};

	void MovementSystem::setInaction(float friction)
	{
		m_friction = friction;
	}

	float MovementSystem::getInaction() const
	{
		return m_friction;
	}
}