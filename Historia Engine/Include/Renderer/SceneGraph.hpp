#ifndef SCENEGRAPH_HPP
#define SCENEGRAPH_HPP

#include <Renderer\SceneNode.hpp>
#include <Artemis\Entity.hpp>

namespace zkt {

	class SceneGraph {
	public:
		SceneGraph();
		void insertEntity(const artemis::Entity& e);
		void attachToEntity( artemis::Entity* target, artemis::Entity* entity);
		void dettachEntity(artemis::Entity* e);
		artemis::Entity*  getEntity();
	
	private:
		SceneNode* m_sceneGraph;
	};
}


#endif