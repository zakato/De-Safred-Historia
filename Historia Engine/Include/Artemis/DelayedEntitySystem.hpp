#ifndef DELAYED_ENTITY_SYSTEM_H
#define DELAYED_ENTITY_SYSTEM_H

#include <Artemis\EntitySystem.hpp>

#include <SFML\System\Time.hpp>






	namespace artemis {
		class DelayedEntitySystem : public EntitySystem {
		private:
			sf::Time delay;
			sf::Time acc;
			bool running;
			bool autoRepeat;
		protected:
			virtual void processEntities(ImmutableBag<Entity*> & bag);
			virtual void processEntities(ImmutableBag<Entity*> & bag, const sf::Time& accumulatedDelta) = 0;
			virtual bool checkProcessing();
		public:
			DelayedEntitySystem();
			void start(const sf::Time& delay);
			void runNow();
			void stop();
			void setAutoRepeat(bool repeat);
			const sf::Time& getInitialTimeDelay();
			const sf::Time& getRemainingTime();
			bool isRunning();

		};
	};


#endif // $(Guard token)