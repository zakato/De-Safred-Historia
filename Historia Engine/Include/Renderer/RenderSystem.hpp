#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <Artemis\EntityProcessingSystem.hpp>
#include <Artemis\ComponentMapper.hpp>

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

	protected:
		void begin();
		void end();

	private:
		artemis::ComponentMapper<cRender>			m_renderComponentMapper;
		artemis::ComponentMapper<cTransform>		m_transformComponentMapper;
		sf::RenderWindow*							m_window;

	};

};


#endif