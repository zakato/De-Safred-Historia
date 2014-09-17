#include <Animation\AnimationSystem.hpp>
#include <iostream>


namespace zkt {


	AnimationSystem::AnimationSystem()
		: m_animationMap()
	{
		addComponentType<cAnimation>();
		addComponentType<cRender>();
	}



	AnimationSystem::~AnimationSystem(){
		delete m_animationMap;
	}


	void AnimationSystem::initialize(){
		m_animationComponentMap.init(*world);
		m_renderComponentMap.init(*world);
	}


	void AnimationSystem::setAnimationMap(AnimationMap* map)
	{
		m_animationMap = map;
	}


	void AnimationSystem::processEntity(artemis::Entity& e){

		AnimationMapIterator iterator;
		cAnimation* animationComponent = m_animationComponentMap.get(e);
		cRender* renderComponent = m_renderComponentMap.get(e);

		sf::IntRect	textureRect;
		size_t currentFrame = 0;
		rsize_t numFrames = 0;
		sf::Time duration;
		sf::Time currentTime;
		sf::Time timePerFrame;


		

		if (animationComponent->IsAnimationChanged()){

			assert(m_animationMap->hasAnimationSet(animationComponent->getAnimationType()));
			iterator = m_animationMap->getAnimationSet(animationComponent->getAnimationType());

			

			animationComponent->setAnimationMapIterator(iterator);
			animationComponent->setTempNumframes(iterator->second.getSize());
			animationComponent->setTempDuration(iterator->second.getDuration());
			animationComponent->setCurrentFrame(0);
			animationComponent->setIsAnimationChanged(false);

			renderComponent->setSprite(iterator->second.getSpriteSheet());
			
		}
		else {
			iterator = animationComponent->getPlayingAnimation();
		}

		duration = animationComponent->getTempDuration();
		numFrames = animationComponent->getTempNumFrames();
		currentTime = animationComponent->getCurrentTime();
		timePerFrame = duration / static_cast<float>(numFrames);
		currentTime += world->getDelta();
		currentFrame = animationComponent->getCurrentFrame();


		// While we have a frame to process
		while (currentTime >= timePerFrame  /*  && (currentFrame <= numFrames || mRepeat )*/)
		{


			// And progress to next frame
			currentTime -= timePerFrame;

			// get next Frame index
			if (currentFrame + 1 < numFrames) {
				currentFrame++;
			}
			else
			{
				// animation has ended
				currentFrame = 0; // reset to start

			}
		}

		

		textureRect = iterator->second.getFrame(currentFrame);
		animationComponent->setCurrentFrame(currentFrame);
		animationComponent->setCurrentTime(currentTime);
		
		renderComponent->getSprite()->setTextureRect(textureRect);
		renderComponent->getSprite()->setOrigin(textureRect.width / 2, textureRect.width / 2);


	}


}


