#include <Collision\CollisionSystem.hpp>


namespace zkt {

	CollisionSystem::CollisionSystem()
		
	{
		addComponentType<cCollider>();
	};

	CollisionSystem::~CollisionSystem()
	{
	}

	void CollisionSystem::initialize()
	{
		m_colliderMapper.init(*world);
		
	};

	void CollisionSystem::processEntity(artemis::Entity &e)
	{
		cCollider* collider = (cCollider*) m_colliderMapper.get(e);
		
		if (collider->getHasCollided())
		{
			collider->launchScript();
		}
	}

	void CollisionSystem::begin()
	{
		
	}

	void CollisionSystem::end()
	{

	}




}