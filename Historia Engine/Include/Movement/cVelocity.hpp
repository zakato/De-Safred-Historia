#ifndef CVELOCITY_HPP
#define CVELOCITY_HPP

#include <Artemis\Component.hpp>
#include <SFML\System\Vector2.hpp>


namespace zkt {

	class cVelocity : public artemis::Component {

	public:
		cVelocity(float x = 0, float y = 0);
		~cVelocity();
		const sf::Vector2f& getVelocity() const;
		void setVelocity(float x, float y);

	private:
		sf::Vector2f m_velocity;
	};
}


#endif