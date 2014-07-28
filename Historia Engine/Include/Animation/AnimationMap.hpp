#ifndef ANIMATIONMAP_H
#define ANIMATIONMAP_H

#include <map>
#include <cassert>
#include <utility>

#include <Animation\AnimationType.hpp>
#include <Animation\AnimationSet.hpp>

namespace zkt {

	


	class AnimationMap {
	
	private:
		typedef std::map<AnimationType, AnimationSet>      AnimationSetMap;
		typedef AnimationSetMap::const_iterator		AnimationMapIterator;
	
	public:
									AnimationMap();

		void						addAnimationSet(const AnimationType& identifier, const AnimationSet& animationSet);
		AnimationMapIterator		getAnimationSet(const AnimationType& identifier) const;
		void						removeAnimationSet(const AnimationType& identifier);
		bool						hasAnimationSet(const AnimationType& identifier) const;
	

	private:
		AnimationSetMap				m_animationMap;

	};


}


#endif