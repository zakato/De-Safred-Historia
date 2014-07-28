#include <Artemis\EntityProcessingSystem.h>
#include <Artemis\ComponentMapper.h>
#include <Collision\QuadTree.hpp>
#include <Collision\cCollider.hpp>


namespace zkt {

	class CollisionSystem : public artemis::EntityProcessingSystem {
	private:
		artemis::ComponentMapper<cCollision> collisionMapper;
		artemis::ComponentMapper<cPosition> positionMapper;

	public:
		MovementSystem() {
			addComponentType<cVelocity>();
			addComponentType<cPosition>();
		};

		virtual void initialize() {
			velocityMapper.init(*world);
			positionMapper.init(*world);
		};

		virtual void processEntity(artemis::Entity &e) {
			/*positionMapper.get(e)->posX += velocityMapper.get(e)->velocityX * world->getDelta();
			positionMapper.get(e)->posY += velocityMapper.get(e)->velocityY * world->getDelta();*/
		};

	};

}