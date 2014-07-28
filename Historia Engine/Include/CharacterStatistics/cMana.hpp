#ifndef CMANA_HPP
#define CMANA_HPP

#include <Artemis\Component.hpp>


namespace zkt {

	class cMana : public artemis::Component {
	public:
		cMana() : m_maxManah(0), m_currentMana(0) {}
		void setMaxMana(float maxMana) { m_maxMana = maxMana; }
		float getMaxMana() const { return m_maxMana; }
		void setCurrentMana(float currentMana) { m_currentMana = currentMana; }
		float getCurrentMana() const { return m_currentMana; }

	private:
		float m_maxMana;
		float m_currentMana;
	};
}