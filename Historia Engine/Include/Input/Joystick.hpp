#ifndef JOYSTICK_HPP
#define JOYSTICK_HPP

#include <SFML\Window\Joystick.hpp>





namespace zkt
{
	struct JoystickButton
	{
		unsigned int JoystickId;
		unsigned int button;
	};

	struct JoystickAxis
	{
		unsigned int			JoystickId;
		sf::Joystick::Axis		axis;
		float					threshold;
		bool					above;
	};



}

#endif