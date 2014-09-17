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
		m_animationMap =  new AnimationMap();
		m_renderSystem = (RenderSystem*) (m_sm->setSystem(new RenderSystem(window)));
		m_movementSystem = (MovementSystem*)(m_sm->setSystem(new MovementSystem()));
		m_playerManager = new PlayerManager();
		

	}

	Game::~Game()
	{
		delete m_sm;
		delete m_em;
		delete m_animationSystem;
		delete m_animationMap;
		delete m_renderSystem;
		delete m_movementSystem;
		delete m_playerManager;
	}

	void Game::Start()
	{
		
		m_sm->initializeAll();
		
		
		
		m_animationSystem->setAnimationMap(m_animationMap);

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
		
			m_animationMap->addAnimationSet(AnimationType::Walk_Nord, *walk);

		

		artemis::Entity & player = m_em->create();

		player.addComponent(new cAnimation());
		player.addComponent(new cRender());
		player.addComponent(new cTransform());
		player.addComponent(new cVelocity());
		player.refresh();

		cAnimation* comp = (cAnimation*) player.getComponent<cAnimation>();
		comp->setAnimationType(AnimationType::Walk_Nord);
		cTransform* transform = (cTransform*)player.getComponent<cTransform>();
		cVelocity* velocity = (cVelocity*) player.getComponent < cVelocity>();

		/*transform->setOrigin(20, 20);*/
		/*velocity->setVelocity(20, 0);*/


		sf::Texture* texture2 = new sf::Texture();;
		if (!texture2->loadFromFile("Media/Textures/monster.png"))
		{
			std::cout << "Failed to load enemy spritesheet!" << std::endl;
		}

		sf::Sprite* sprite2 = new sf::Sprite(*texture2);

		artemis::Entity& enemy = m_em->create();

		enemy.addComponent(new cRender());
		enemy.addComponent(new cTransform());
		enemy.addComponent(new cCollider());
		enemy.refresh();

		cRender* render = (cRender*) enemy.getComponent<cRender>();
		render->setSprite(sprite2);
		transform = (cTransform*) enemy.getComponent<cTransform>();
		transform->move(100, 0);
		transform->setScale(0.5f, 0.5f);


		sf::Texture* texture3 = new sf::Texture();;
		if (!texture3->loadFromFile("Media/Textures/monster.png"))
		{
			std::cout << "Failed to load enemy spritesheet!" << std::endl;
		}

		sf::Sprite* sprite3 = new sf::Sprite(*texture3);

		artemis::Entity& enemy2 = m_em->create();

		enemy2.addComponent(new cRender());
		enemy2.addComponent(new cTransform());
		enemy2.addComponent(new cCollider());
		enemy2.refresh();

		cRender* render2 = (cRender*)enemy2.getComponent<cRender>();
		render2->setSprite(sprite3);
		transform = (cTransform*)enemy2.getComponent<cTransform>();
		transform->move(0, 100);
		transform->setScale(0.5f, 0.5f);
		

		m_movementSystem->setInaction(0.4f);

		

		/*sf::RenderStates states;

		while (true) {
			m_window->clear();
			m_window->draw(*comp->getSprite(), states);
			m_window->display();
		}*/

		m_playerManager->setPlayer(&player);
		

		m_actionMap["up"] = Action(sf::Keyboard::W, Action::ActionType::Hold) && !(Action(sf::Keyboard::A, Action::ActionType::Hold) && Action(sf::Keyboard::D, Action::ActionType::Hold) && Action(sf::Keyboard::S, Action::ActionType::Hold));
		m_actionMap["down"] = Action(sf::Keyboard::S, Action::ActionType::Hold) && !(Action(sf::Keyboard::A, Action::ActionType::Hold) && Action(sf::Keyboard::W, Action::ActionType::Hold) && Action(sf::Keyboard::D, Action::ActionType::Hold));
		m_actionMap["right"] = Action(sf::Keyboard::D, Action::ActionType::Hold) && !(Action(sf::Keyboard::A, Action::ActionType::Hold) && Action(sf::Keyboard::W, Action::ActionType::Hold) && Action(sf::Keyboard::S, Action::ActionType::Hold));
		m_actionMap["left"] = Action(sf::Keyboard::A, Action::ActionType::Hold) && !(Action(sf::Keyboard::W, Action::ActionType::Hold) && Action(sf::Keyboard::S, Action::ActionType::Hold) && Action(sf::Keyboard::D, Action::ActionType::Hold));
		
		
		m_actionMap["down_right"] = Action(sf::Keyboard::S, Action::ActionType::Hold) && Action(sf::Keyboard::D, Action::ActionType::Hold);
		m_actionMap["down_left"] = Action(sf::Keyboard::S, Action::ActionType::Hold) && Action(sf::Keyboard::A, Action::ActionType::Hold);
		m_actionMap["up_right"] = Action(sf::Keyboard::W, Action::ActionType::Hold) && Action(sf::Keyboard::D, Action::ActionType::Hold);
		m_actionMap["up_left"] = Action(sf::Keyboard::W, Action::ActionType::Hold) && Action(sf::Keyboard::A, Action::ActionType::Hold);

		
		m_callBacks.connect("up", std::bind(&PlayerManager::move, *m_playerManager, 0, -20));
		m_callBacks.connect("down", std::bind(&PlayerManager::move, *m_playerManager, 0, 20));
		m_callBacks.connect("right", std::bind(&PlayerManager::move, *m_playerManager, 20, 0));
		m_callBacks.connect("left", std::bind(&PlayerManager::move, *m_playerManager, -20, 0));
		
		m_callBacks.connect("up_right", std::bind(&PlayerManager::move, *m_playerManager, 20, -20));
		m_callBacks.connect("up_left", std::bind(&PlayerManager::move, *m_playerManager, -20, -20));
		m_callBacks.connect("down_right", std::bind(&PlayerManager::move, *m_playerManager, 20, 20));
		m_callBacks.connect("down_left", std::bind(&PlayerManager::move, *m_playerManager, -20, 20));

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