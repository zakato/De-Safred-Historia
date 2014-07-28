#ifndef CHEALTH_HPP
#define CHEALTH_HPP

#include <Artemis\Component.hpp>

namespace zkt {

	class cHealth : artemis::Component {

	public:
		cHealth() : m_maxHealth(0), m_currentHealth(0) {}
		void setMaxHealth(float maxHealth) { m_maxHealth = maxHealth; }
		float getMaxHealth() const { return m_maxHealth; }
		void setCurrentHealth(float currentHealth) { m_currentHealth = currentHealth; }
		float getCurrentHealt() const { return m_currentHealth; }

	private:
		float m_maxHealth;
		float m_currentHealth;
	};
}



#endif