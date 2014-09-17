#ifndef COLLIDERSYSTEM_HPP
#define COLLIDERSYSTEM_HPP

#include <Artemis\EntityProcessingSystem.hpp>
#include <Artemis\ComponentMapper.hpp>
#include <Collision\QuadTree.hpp>
#include <Collision\cCollider.hpp>


namespace zkt {

	class CollisionSystem : public artemis::EntityProcessingSystem {		

	public:
		CollisionSystem();

		~CollisionSystem();

		virtual void initialize();

		virtual void processEntity(artemis::Entity &e);
	
	protected:
		void begin();
		void end();

	private:
		artemis::ComponentMapper<cCollider> m_colliderMapper;
	};

}

#endif