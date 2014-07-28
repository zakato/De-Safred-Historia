#include <Renderer\RenderSystem.hpp>
#include <iostream>





namespace zkt {

	
	RenderSystem::RenderSystem( sf::RenderWindow* window)
	{
		m_window = window;
		addComponentType<cAnimation>();
		addComponentType<cTransform>();
		
	}


	
	void RenderSystem::initialize()
	{
		
		m_animationComponentMapper.init(*world);
		m_transformComponentMapper.init(*world);
	}

	
	void RenderSystem::processEntity(artemis::Entity& e)
	{


		

			/*f::Sprite*  sprite = m_spriteComponentMapper.get(e)->getSprite();*/
			sf::Sprite*	sprite = m_animationComponentMapper.get(e)->getTempSpriteSheet();


			sf::RenderStates states;
			states.transform = m_transformComponentMapper.get(e)->getTransform();


			m_window->clear();
			m_window->draw(*sprite, states);
			m_window->display();
		
	}
}