#include <Input/Action.hpp>

#include <algorithm>
#include <cassert>


namespace zkt
{

	Action::Action()
		: m_operation()
	{
	}

	Action::Action(sf::Keyboard::Key key, ActionType action)
		: m_operation()
	{
		switch (action)
		{
		case Hold:
			m_operation = std::make_shared<RealtimeKeyLeaf>(key);
			break;

		case PressOnce:
		case ReleaseOnce:
			m_operation = std::make_shared<EventKeyLeaf>(key, action == PressOnce);
			break;
		}
	}

	Action::Action(sf::Mouse::Button mouseButton, ActionType action)
		: m_operation()
	{
		switch (action)
		{
		case Hold:
			m_operation = std::make_shared<RealtimeMouseLeaf>(mouseButton);
			break;

		case PressOnce:
		case ReleaseOnce:
			m_operation = std::make_shared<EventMouseLeaf>(mouseButton, action == PressOnce);
			break;
		}
	}

	Action::Action(JoystickButton joystick, ActionType action)
		: m_operation()
	{
		switch (action)
		{
		case Hold:
			m_operation = std::make_shared<RealtimeJoystickButtonLeaf>(joystick);
			break;

		case PressOnce:
		case ReleaseOnce:
			m_operation = std::make_shared<EventJoystickLeaf>(joystick, action == PressOnce);
			break;
		}
	}

	Action::Action(JoystickAxis joystickState)
		: m_operation(std::make_shared<RealtimeJoystickAxisLeaf>(joystickState))
	{
	}

	/*Action::Action(sf::Event::EventType eventType)
		: m_operation(std::make_shared<MiscEventLeaf>(eventType))
	{
	}*/

	bool Action::isActive(const EventBuffer& buffer) const
	{
		return m_operation->isActionActive(buffer);
	}

	bool Action::isActive(const EventBuffer& buffer, ActionResult& out) const
	{
		return m_operation->isActionActive(buffer, out);
	}

	Action::Action(ActionNode::ActionPtr operation)
	{
		m_operation = std::move(operation);
	}

	// TODO: Wait until aurora::CopiedPtr implements move derived-to-base more efficiently
	Action operator|| (const Action& lhs, const Action& rhs)
	{
		return Action(std::make_shared<OrNode>(lhs.m_operation, rhs.m_operation));
	}

	Action operator&& (const Action& lhs, const Action& rhs)
	{
		return Action(std::make_shared<AndNode>(lhs.m_operation, rhs.m_operation));
	}

	Action operator! (const Action& action)
	{
		return Action(std::make_shared<NotNode>(action.m_operation));
	}

	/*Action eventAction(std::function<bool(const sf::Event&)> filter)
	{
		return Action(std::make_shared<CustomEventLeaf>(std::move(filter)));
	}

	Action realtimeAction(std::function<bool()> filter)
	{
		return Action(std::make_shared<CustomRealtimeLeaf>(std::move(filter)));
	}
*/
}