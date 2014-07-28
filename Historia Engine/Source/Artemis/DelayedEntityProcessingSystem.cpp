#include <Artemis\DelayedEntityProcessingSystem.hpp>




namespace artemis {

	void DelayedEntityProcessingSystem::processEntities(ImmutableBag<Entity*>& bag, const sf::Time& accumulatedDelta) {
		for (int i = 0; i< bag.getCount(); i++)
			processEntity(*bag.get(i), accumulatedDelta);
	}
}