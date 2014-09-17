#include <Renderer\RenderSystem.hpp>
#include <iostream>





namespace zkt {

	
	RenderSystem::RenderSystem( sf::RenderWindow* window)
	{
		m_window = window;
		addComponentType<cRender>();
		addComponentType<cTransform>();
		
	}


	
	void RenderSystem::initialize()
	{
		
		m_renderComponentMapper.init(*world);
		m_transformComponentMapper.init(*world);
	}

	void RenderSystem::begin()
	{
		m_window->clear();
	}

	void RenderSystem::end()
	{
		m_window->display();
	}

	
	void RenderSystem::processEntity(artemis::Entity& e)
	{


		

			/*f::Sprite*  sprite = m_spriteComponentMapper.get(e)->getSprite();*/
		sf::Sprite*	sprite = m_renderComponentMapper.get(e)->getSprite();


			sf::RenderStates states;
			states.transform = m_transformComponentMapper.get(e)->getTransform();


			
			m_window->draw(*sprite, states);
			
		
	}
}