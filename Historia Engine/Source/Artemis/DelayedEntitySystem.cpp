#include <Artemis\DelayedEntitySystem.hpp>
#include <Artemis\World.hpp>


namespace artemis {

	DelayedEntitySystem::DelayedEntitySystem() {
		acc = sf::Time::Zero;
		delay = sf::Time::Zero;
		running = false;
		autoRepeat = false;
	}

	bool DelayedEntitySystem::checkProcessing() {
		if (running) {
			acc += world->getDelta();

			if (acc >= delay) {
				return true;
			}
		}

		return false;
	}

	const sf::Time& DelayedEntitySystem::getInitialTimeDelay() {
		return delay;
	}

	const sf::Time& DelayedEntitySystem::getRemainingTime() {
		if (running) {
			return delay - acc;
		}

		return sf::Time::Zero;
	}

	bool DelayedEntitySystem::isRunning() {
		return running;
	}

	void DelayedEntitySystem::setAutoRepeat(bool repeat) {
		autoRepeat = repeat;
	}

	void DelayedEntitySystem::processEntities(ImmutableBag<Entity*>& bag) {
		processEntities(bag, acc);

		if (autoRepeat) {
			start(delay);
		}
		else {
			stop();
		}
	}

	void DelayedEntitySystem::start(const sf::Time& delay) {
		this->delay = delay;
		acc = sf::Time::Zero;
		running = true;
	}

	void DelayedEntitySystem::stop() {
		acc = sf::Time::Zero;
		running = false;
	}
	void DelayedEntitySystem::runNow()
	{
		acc = delay;
	}

};