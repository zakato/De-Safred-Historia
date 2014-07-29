#ifndef PLAYERMANAGER_HPP
#define PLAYERMANAGER_HPP

#include <Artemis\Entity.hpp>

#include <Movement\cVelocity.hpp>
#include <Movement\cTransform.hpp>

namespace zkt {

	class PlayerManager {
	
	public:
		/*enum class Direction {
			up,
			down,
			right,
			left
		};*/

	public:
		PlayerManager() : m_player(nullptr) {}
		explicit PlayerManager(artemis::Entity* e);

		void setPlayer(artemis::Entity* player) { m_player = player; }
		void move( float x, float y);

	private:
		artemis::Entity* m_player;
	};
}

#endif