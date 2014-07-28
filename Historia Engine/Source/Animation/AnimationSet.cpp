#include <Animation\AnimationSet.hpp>



namespace zkt {


	AnimationSet::AnimationSet() : m_sprite(nullptr), m_duration(), m_frames()
{

}

AnimationSet::AnimationSet(const std::vector<sf::IntRect>& frames, sf::Sprite* sprite, const sf::Time& duration) : 
m_frames(frames), m_sprite(sprite), m_duration(duration)
{

}

void AnimationSet::addFrame(sf::IntRect rect)
{
    m_frames.push_back(rect);
}

void AnimationSet::setSpriteSheet(sf::Sprite* sprite)
{
    m_sprite = sprite;
}

sf::Sprite* AnimationSet::getSpriteSheet() const
{
    return m_sprite;
}

std::size_t AnimationSet::getSize() const
{
	
    return m_frames.size();
}

const sf::IntRect& AnimationSet::getFrame(std::size_t n) const
{
    return m_frames[n];
}



void AnimationSet::setDuration(const sf::Time& duration){
	m_duration=duration;
}

const sf::Time& AnimationSet::getDuration() const{
		return m_duration;
}


}