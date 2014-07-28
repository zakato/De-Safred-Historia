#ifndef SCENENODE_H
#define SCENENODE_H

#include <Artemis\Entity.hpp>

#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Transform.hpp>

#include <vector>
#include <memory>

namespace zkt {

	class SceneNode {
	public:
		typedef std::unique_ptr<SceneNode> Ptr;
	
	public:
												SceneNode();
		void									attachChild(Ptr child);
		Ptr										detachChild(const SceneNode& node);
		Ptr										getParent() const;

		void									attachEtntiy(artemis::Entity* entity);
		artemis::Entity*						getEntity() const;

		sf::Vector2f							getWorldPosition() const;
		sf::Transform							getWorldTransform() const;

		artemis::Entity*						getEntity() const;
	
	private:
		std::vector<Ptr>						m_children;
		Ptr										m_parent;
		std::unique_ptr<artemis::Entity>		m_entity;
	};
}



#endif