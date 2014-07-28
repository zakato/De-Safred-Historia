#ifndef ACTION_HPP
#define ACTION_HPP

#include <SFML\Window.hpp>

#include <Input\Joystick.hpp>

#include <Input\ActionOperations.hpp>

namespace zkt
{
	class Action
	{
	public:

		enum ActionType
		{
			Hold,
			PressOnce,
			ReleaseOnce
		};

	public:
		explicit Action(sf::Keyboard::Key key, ActionType action = Hold);
		explicit Action(sf::Mouse::Button mouseButton, ActionType action = Hold);
		explicit Action(JoystickButton joystickState, ActionType action = Hold);
		explicit Action(JoystickAxis joystickState);
		explicit Action(sf::Event::EventType eventType);

	
				Action();
				bool	isActive(const EventBuffer& buffer) const;
				bool	isActive(const EventBuffer& buffer, ActionResult& out) const;

	private:
		explicit Action(ActionNode::ActionPtr operation);

	private:
			ActionNode::ActionPtr m_operation;


		friend Action operator|| (const Action& lhs, const Action& rhs);
		friend Action operator&& (const Action& lhs, const Action& rhs);
		friend Action operator! (const Action& action);
		friend Action eventAction(std::function<bool(const sf::Event&)> filter);
		friend Action realtimeAction(std::function<bool()> filter);



	};


	 Action operator|| (const Action& lhs, const Action& rhs);
	 Action operator&& (const Action& lhs, const Action& rhs);
	 Action operator! (const Action& action);
	 Action eventAction(std::function<bool(const sf::Event&)> filter);
	 Action realtimeAction(std::function<bool()> filter);
}

#endif