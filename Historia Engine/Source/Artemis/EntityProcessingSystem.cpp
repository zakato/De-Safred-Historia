#include <Artemis\EntityProcessingSystem.hpp>




namespace artemis {

	bool EntityProcessingSystem::checkProcessing() {
		return true;
	}

	void EntityProcessingSystem::processEntities(ImmutableBag<Entity*>& bag) {
		for (int i = 0; i < bag.getCount(); i++)
		{
			processEntity(*bag.get(i));
		}
	}

};