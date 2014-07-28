#include <Game.hpp>






namespace zkt {

	Game::Game( sf::RenderWindow* window)
		: m_world()
		, m_window(window)
		, m_actionMap()
		, m_callBacks()
	{

		m_sm = m_world.getSystemManager();
		m_em = m_world.getEntityManager();
		m_animationSystem = (AnimationSystem*) (m_sm->setSystem(new AnimationSystem()));
		m_renderSystem = (RenderSystem*) (m_sm->setSystem(new RenderSystem(window)));
		m_movementSystem = (MovementSystem*)(m_sm->setSystem(new MovementSystem()));
		m_playerManager = new PlayerManager();
		

	}

	void Game::Start()
	{
		
		m_sm->initializeAll();
		
		AnimationMap* animationMap = new AnimationMap();
		
		m_animationSystem->setAnimationMap(animationMap);

		sf::Texture* texture = new sf::Texture();;
		if (!texture->loadFromFile("Media/Textures/player.png"))
		{
			std::cout << "Failed to load player spritesheet!" << std::endl;
		}

		sf::Sprite* sprite = new sf::Sprite(*texture);

		
			AnimationSet* walk = new AnimationSet();
			walk->setSpriteSheet(sprite);
			walk->addFrame(sf::IntRect(32, 0, 32, 32));
			walk->addFrame(sf::IntRect(64, 0, 32, 32));
			walk->addFrame(sf::IntRect(32, 0, 32, 32));
			walk->addFrame(sf::IntRect(0, 0, 32, 32));
			walk->setDuration(sf::seconds(1.f));
		
			animationMap->addAnimationSet(AnimationType::Walk_Nord, *walk);

		

		artemis::Entity & player = m_em->create();

		player.addComponent(new cAnimation());
		player.addComponent(new cTransform());
		player.addComponent(new cVelocity());
		player.refresh();

		cAnimation* comp = (cAnimation*) player.getComponent<cAnimation>();
		comp->setAnimationType(AnimationType::Walk_Nord);
		cVelocity* velocity = (cVelocity*) player.getComponent < cVelocity>();
		/*velocity->setVelocity(20, 0);*/
		
		m_movementSystem->setInaction(0.4f);

		/*cSprite* comp = (cSprite*) player.getComponent<cSprite>();
		comp->setSprite(sprite);*/

		/*sf::RenderStates states;

		while (true) {
			m_window->clear();
			m_window->draw(*comp->getSprite(), states);
			m_window->display();
		}*/

		m_playerManager->setPlayer(&player);
		
		m_actionMap["run"] = Action(sf::Keyboard::D, Action::ActionType::Hold);

		m_callBacks.connect("run", std::bind(&PlayerManager::move, *m_playerManager, 20, 0));
	}

	void Game::Update(const sf::Time& delta)
	{
		m_actionMap.update(*m_window);
		m_actionMap.invokeCallbacks(m_callBacks, m_window);
		
		m_world.loopStart();
		m_world.setDelta(delta);
		m_animationSystem->process();
		m_movementSystem->process();
		m_renderSystem->process();

		
			
	}


}