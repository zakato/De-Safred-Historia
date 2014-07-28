#ifndef D_E_PROCESSING_SYSTEM_H
#define D_E_PROCESSING_SYSTEM_H

#include <Artemis\DelayedEntitySystem.hpp>

#include <SFML\System\Time.hpp>



	namespace artemis{
		class DelayedEntityProcessingSystem : public DelayedEntitySystem
		{
		protected:
			virtual void processEntities(ImmutableBag<Entity*>& bag, const sf::Time& accumulatedDelta);
			virtual void processEntity(Entity& e, const sf::Time& accumulatedDelta) = 0;
		};
	};


#endif // $(Guard token)