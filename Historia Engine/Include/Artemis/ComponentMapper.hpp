#ifndef COMPONENTMAPPER_H
#define COMPONENTMAPPER_H

#include <Artemis\EntityManager.hpp>
#include <Artemis\World.hpp>


namespace artemis {

	template<typename c>
	/**
	* High performance component retrieval from entities. Use this wherever you
	* need to retrieve components from entities often and fast.
	*/
	class ComponentMapper {

	private:

		EntityManager * em;

	public:

		~ComponentMapper() {
			//Not the owner. Only a pointer to.
			em = nullptr;
		}

		void init(World& world){
			em = world.getEntityManager();
		}

		/**
		*Returns the component mapped to the Entity.
		*If there is no such component associated with the entity
		*NULL is returned.
		*/
		c * get(Entity & e) {
			//ATTN perhaps pointing to the component bag is faster.
			return (c*)em->getComponent<c>(e);
		}

	};
};

#endif // $(Guard token)