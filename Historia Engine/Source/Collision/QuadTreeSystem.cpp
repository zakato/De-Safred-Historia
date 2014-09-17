#include <Collision\QuadTreeSystem.hpp>


namespace zkt {

	QuadTreeSystem::QuadTreeSystem()
		: m_quadTree(0, 0, 800.0f, 600.0f, 0, 3)
	{
		addComponentType<cCollider>();
		addComponentType<cTransform>();
	}

	QuadTreeSystem::~QuadTreeSystem()
	{

	}

	void QuadTreeSystem::initialize()
	{
		m_colliderMapper.init(*world);
		m_transformMapper.init(*world);
	}

	void QuadTreeSystem::processEntity(artemis::Entity &e)
	{
		float x = m_transformMapper.get(e)->getPosition().x;
		float y = m_transformMapper.get(e)->getPosition().y;
		m_colliderMapper.get(e)->getCollider().setPosition(x, y);
		m_quadTree.AddObject(&e);
	}

	void QuadTreeSystem::begin()
	{
		m_quadTree.Clear();
	}

	void QuadTreeSystem::end()
	{
		m_quadTree.checkCollisions();

	}
	

}