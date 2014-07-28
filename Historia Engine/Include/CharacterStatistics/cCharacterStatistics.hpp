#ifndef CCHARACTHERSTATISTICS_HPP
#define CCHARACTHERSTATISTICS_HPP

#include <Artemis\Component.hpp>


namespace zkt {

	class cCharacterStatistics : public artemis::Component {

	public:
		cCharacterStatistics();
		

	private:
		int m_maxLevel;
		int m_currentLevel;
		int strenght;
		int speed;
		int agility;
		int intellect;
		int defense;
	};
}


#endif