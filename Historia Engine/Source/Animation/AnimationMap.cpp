#include <Animation\AnimationMap.hpp>


namespace zkt {

	AnimationMap::AnimationMap() : m_animationMap(){

	}



	
	void	AnimationMap::addAnimationSet(const AnimationType& identifier, const AnimationSet& animationSet){
		assert(m_animationMap.find(identifier) == m_animationMap.end());
		m_animationMap.insert(std::make_pair(identifier, animationSet));
	}

	
	AnimationMap::AnimationMapIterator	AnimationMap::getAnimationSet(const AnimationType& identifier) const{

		const AnimationMapIterator iterator = m_animationMap.find(identifier);
		return iterator;
	}


	
	void	AnimationMap::removeAnimationSet(const AnimationType& identifier){
		m_animationMap.erase(identifier);
	}

	
	bool	AnimationMap::hasAnimationSet(const AnimationType& identifier) const{
		return (m_animationMap.find(identifier) != m_animationMap.end());
	}

}