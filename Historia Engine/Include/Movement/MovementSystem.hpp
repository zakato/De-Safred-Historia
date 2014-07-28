#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENETSYSTEM_HPP

#include <Artemis\EntityProcessingSystem.hpp>
#include <Artemis\ComponentMapper.hpp>
#include <Movement\cTransform.hpp>
#include <Movement\cVelocity.hpp>

namespace zkt {

	class MovementSystem : public artemis::EntityProcessingSystem {
	

	public:
		MovementSystem();
		virtual void initialize();
		virtual void processEntity(artemis::Entity &e);
		void setInaction(float friction);
		float getInaction() const;

	private:
		artemis::ComponentMapper<cVelocity> m_velocityMapper;
		artemis::ComponentMapper<cTransform> m_transformMapper;
		float m_friction;
	};


}

#endif