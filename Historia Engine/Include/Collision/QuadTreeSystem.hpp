#ifndef QUADTREESYSTEM_HPP
#define QUADTREESYSTEM_HPP

#include <Collision\QuadTree.hpp>
#include <Collision\cCollider.hpp>
#include <Movement\cTransform.hpp>

#include <Artemis\EntityProcessingSystem.hpp>
#include <Artemis\ComponentMapper.hpp>

namespace zkt {

	class QuadTreeSystem : public artemis::EntityProcessingSystem {
		
	public:
		QuadTreeSystem();
		~QuadTreeSystem();

		virtual void initialize();
		virtual void processEntity(artemis::Entity &e);

	protected:
		void begin();
		void end();
		void checkCollision();

	private:
		artemis::ComponentMapper<cCollider> m_colliderMapper;
		artemis::ComponentMapper<cTransform> m_transformMapper;
		QuadTree m_quadTree;


	};
}

#endif