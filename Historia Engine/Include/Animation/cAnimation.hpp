#ifndef CANIMATION_H
#define CANIMATION_H

#include <Artemis\Component.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#include <map>
#include <iterator>

#include <Animation\AnimationType.hpp>

namespace zkt {

	
	
	class AnimationSet;

	
	class cAnimation : public artemis::Component {
	private:
		typedef std::map<AnimationType, AnimationSet>      AnimationSetMap;
		typedef AnimationSetMap::const_iterator		AnimationMapIterator;

	public:
									cAnimation() : m_isAnimationChanged(true), m_iterator(), m_animationType(AnimationType::None) {   }
		void						setIterator(AnimationMapIterator iterator)					{ m_iterator = iterator; }
		AnimationMapIterator		getPlayingAnimation() const									{ return m_iterator; }
		void						setTempDuration(const sf::Time& duration)					{ m_temp_duration = duration; }
		const sf::Time&				getTempDuration() const										{ return m_temp_duration; }
		void						setTempNumframes(const size_t& numFrames)					{  m_temp_numFrames = numFrames; }
		const sf::Time&				getCurrentTime() const										{ return m_currentTime; }
		void						setCurrentTime(const sf::Time& currentTime )				{  m_currentTime = currentTime; }
		size_t						getTempNumFrames() const									{ return m_temp_numFrames; }
		void						setCurrentFrame(const size_t& currentFrame)					{ m_temp_currentframes = currentFrame; }
		size_t						getCurrentFrame() const										{ return m_temp_currentframes; } 
		void						setAnimationMapIterator(AnimationMapIterator iterator)		{ m_iterator = iterator; }
		AnimationMapIterator		getAnimationMapIterator() const								{ return m_iterator;}
		void						setAnimationType(const AnimationType& id)						{ m_animationType = id; }
		AnimationType				getAnimationType() const									{ return m_animationType; }
		void						setIsAnimationChanged(bool isAnimationChanged)				{ m_isAnimationChanged = isAnimationChanged; }
		bool						IsAnimationChanged() const									{ return m_isAnimationChanged; }

	private:
	sf::Time					m_temp_duration;
	sf::Time					m_currentTime;
	size_t						m_temp_numFrames;
	size_t						m_temp_currentframes;
	AnimationMapIterator		m_iterator;
	AnimationType				m_animationType;
	bool						m_isAnimationChanged;
	};



}

#endif