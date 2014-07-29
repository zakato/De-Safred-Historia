#include <Artemis\World.hpp>
#include <Artemis\EntityManager.hpp>
#include <Artemis\SystemManager.hpp>
#include <Artemis\Entity.hpp>

#include <Animation\AnimationSystem.hpp>
#include <Animation\AnimationMap.hpp>
#include <Animation\AnimationType.hpp>
#include <Animation\AnimationSet.hpp>
#include <Animation\cAnimation.hpp>

#include <Movement\MovementSystem.hpp>
#include <Movement\cTransform.hpp>
#include <Movement\cVelocity.hpp>

#include <Renderer\cRender.hpp>
#include <Renderer\RenderSystem.hpp>

#include <Input\Action.hpp>
#include <Input\ActionMap.hpp>
#include <Input\ActionOperations.hpp>
#include <Input\EventSystem.hpp>

#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\System\Time.hpp>  
#include <SFML\Window.hpp>

#include <Player\PlayerManager.hpp>

#include <string>

namespace zkt {


	

	class Game {
		
	public:
		Game( sf::RenderWindow* window);
		~Game();
		void Start();
		void Update(const sf::Time& delta);

	private:  
		artemis::World m_world;
		artemis::SystemManager* m_sm;
		artemis::EntityManager* m_em;

		AnimationSystem* m_animationSystem;
		AnimationMap*	m_animationMap;
		
		MovementSystem* m_movementSystem;
		
		RenderSystem* m_renderSystem;
		sf::RenderWindow* m_window;

		PlayerManager* m_playerManager; 
	    
		ActionMap<std::string> m_actionMap;
		ActionMap<std::string>::CallbackSystem m_callBacks;
	};
};
