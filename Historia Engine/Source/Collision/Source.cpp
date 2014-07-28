#include <SFML/Graphics.hpp>

#include <Animation\AnimationMap.hpp>
#include <Animation\AnimationSystem.hpp>
#include <iostream>
#include <Artemis\Artemis.h>
#include <Input\Command.hpp>

#include <SceneNode\SceneNode.hpp>


using namespace zkt;

int main()
{
	enum class AnimationType
	{
		sex,
		pene
	};

	//**********************************************************************

	sf::Vector2i screenDimensions(800, 600);
	sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Animations!");
	window.setFramerateLimit(60);

	sf::Texture texture;
	if (!texture.loadFromFile("Media/Textures/player.png"))
	{
		std::cout << "Failed to load player spritesheet!" << std::endl;
		return 1;
	}

	sf::Sprite* sprite = new sf::Sprite(texture);

	AnimationSet walk;
	walk.setSpriteSheet(sprite);
	walk.addFrame(sf::IntRect(32, 0, 32, 32));
	walk.addFrame(sf::IntRect(64, 0, 32, 32));
	walk.addFrame(sf::IntRect(32, 0, 32, 32));
	walk.addFrame(sf::IntRect(0, 0, 32, 32));
	walk.setDuration(sf::seconds(1.f));

	AnimationMap<AnimationType>* animationMap = new AnimationMap<AnimationType>;
	animationMap->addAnimationSet(AnimationType::sex, walk);

	sf::Clock frameClock;

	float speed = 80.f;
	bool noKeyWasPressed = true;
	size_t currentFrame = 0;


	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

	sf::RenderStates states;

	//**********************************************************************

	artemis::World world;
	artemis::SystemManager * sm = world.getSystemManager();
	AnimationSystem<AnimationType>* animationSystem = (AnimationSystem<AnimationType>*) (sm->setSystem(new AnimationSystem<AnimationType>(animationMap)));
	artemis::EntityManager * em = world.getEntityManager();

	sm->initializeAll();

	artemis::Entity& player = em->create();

	player.addComponent(new cAnimation<AnimationType>());
	player.refresh();


	cAnimation<AnimationType>* anim = (cAnimation<AnimationType>*) player.getComponent<cAnimation<AnimationType>>();
	anim->setAnimationType(AnimationType::sex);



	//**********************************************************************

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();
		}

		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			world.loopStart();
			world.setDelta(TimePerFrame);
			animationSystem->process();

			sf::Sprite* spritesheet = anim->getTempSpriteSheet();

			// draw
			window.clear();
			window.draw(*spritesheet, states);
			window.display();

		}



		/*  animatedSprite.play(*currentAnimation);
		animatedSprite.move(movement * frameTime.asSeconds());
		*/


		// add delta time




		// set the current frame, not reseting the time

	}




	//artemis::World world;
	//  artemis::SystemManager * sm = world.getSystemManager();
	//  MovementSystem * movementsys = (MovementSystem*)sm->setSystem(new MovementSystem());
	//  artemis::EntityManager * em = world.getEntityManager();

	//  sm->initializeAll();

	//  artemis::Entity & player = em->create();

	//  player.addComponent(new zkt::VelocityComponent(2,4));
	//  player.addComponent(new zkt::PositionComponent(0,0));
	//  player.refresh();

	//  zkt::PositionComponent * comp = (zkt::PositionComponent*) player.getComponent<zkt::PositionComponent>();

	//  while(true){

	//      world.loopStart();
	//world.setDelta(TimePerFrame);
	//movementsys->process();

	//      std::cout << "X:"<< comp->posX << std::endl;
	//      std::cout << "Y:"<< comp->posY << std::endl;
	//      
	//  }






	return 0;
}