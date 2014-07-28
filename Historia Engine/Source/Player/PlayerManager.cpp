#include <Player\PlayerManager.hpp>




namespace zkt {

	PlayerManager::PlayerManager(artemis::Entity* e)
		: m_player(e)
	{

	}

	void PlayerManager::move(float x, float y)
	{
		cVelocity* velocity = (cVelocity*) m_player->getComponent<cVelocity>();
		velocity->setVelocity(x, y);
	}


}


