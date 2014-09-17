#ifndef ANIMATIONSYSTEM_H
#define ANIMATIONSYSTEM_H

#include <Artemis\EntityProcessingSystem.hpp>
#include <Artemis\ComponentMapper.hpp>

#include <map>
#include <iterator>
#include <assert.h>

#include <SFML\System\Time.hpp>
#include <Animation\cAnimation.hpp>
#include <Renderer\cRender.hpp>


#include <Animation\AnimationMap.hpp>




namespace zkt{

	


class AnimationSystem : public artemis::EntityProcessingSystem {
private:
	typedef std::map<AnimationType, AnimationSet>      AnimationSetMap;
	typedef AnimationSetMap::const_iterator		AnimationMapIterator;

public:
	AnimationSystem();
	virtual ~AnimationSystem();
	void initialize();
	void processEntity(artemis::Entity& e);
	void setAnimationMap(AnimationMap* map);

private:
	void	playAnimation(const AnimationType& identifier);

private:
	artemis::ComponentMapper<cAnimation>	m_animationComponentMap;
	artemis::ComponentMapper<cRender>		m_renderComponentMap;
	AnimationMap*							m_animationMap;

};




}

#endif

