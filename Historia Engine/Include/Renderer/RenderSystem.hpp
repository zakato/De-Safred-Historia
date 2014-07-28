#include <Artemis\EntityProcessingSystem.hpp>
#include <Artemis\ComponentMapper.hpp>

#include <Animation\cAnimation.hpp>
#include <Renderer\cSprite.hpp>
#include <Renderer\cRender.hpp>
#include <Movement\cTransform.hpp>

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\RenderStates.hpp>

namespace zkt {
	
	
	class RenderSystem : public artemis::EntityProcessingSystem {


	public:
													RenderSystem( sf::RenderWindow* window);
		virtual void								initialize();

		virtual void								processEntity( artemis::Entity &e);

	
	private:
		artemis::ComponentMapper<cSprite>			m_spriteComponentMapper;
		artemis::ComponentMapper<cAnimation>		m_animationComponentMapper;
		artemis::ComponentMapper<cTransform>		m_transformComponentMapper;
		sf::RenderWindow*							m_window;

	};

};


