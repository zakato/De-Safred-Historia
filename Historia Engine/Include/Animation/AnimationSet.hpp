#ifndef ANIMATIONSET_H
#define ANIMATIONSET_H

#include <SFML\System.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <vector>
#include <iterator>
#include <map>
#include <Animation\AnimationType.hpp>

namespace zkt {

class AnimationSet {


public:
							AnimationSet();
	explicit				AnimationSet(const std::vector<sf::IntRect>& frames, sf::Sprite* sprite, const sf::Time& duration);
	void					addFrame(sf::IntRect rect);
    void					setSpriteSheet(sf::Sprite* sprite);
    sf::Sprite*				getSpriteSheet() const;
    std::size_t				getSize() const;
    const sf::IntRect&		getFrame(std::size_t n) const;
	void					setDuration(const sf::Time& duration);
	const sf::Time&			getDuration() const;
	

private:
    std::vector<sf::IntRect> m_frames;
	sf::Time				 m_duration;
    sf::Sprite*				 m_sprite;
};

}

#endif