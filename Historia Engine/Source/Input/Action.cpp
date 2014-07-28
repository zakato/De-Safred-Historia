#include <Input\Action.hpp>

#include <cassert>

//
//namespace zkt
//{
//	
//	Action::Action()
//		: m_operation()
//	{
//	}
//
//	Action::Action(sf::Keyboard::Key key, ActionType action)
//		: m_operation()
//	{
//		switch (action)
//		{
//		case zkt::Action::Hold:
//			m_operation = std::make_shared<RealtimeKeyLeaf>(key);
//			break;
//
//		case zkt::Action::PressOnce:
//			break;
//		case zkt::Action::ReleaseOnce:
//			m_operation = std::make_shared<EventKeyLeaf>(key, action == PressOnce);
//			break;
//		}
//	}
//
//
//	Action::Action(JoystickButton joystick, ActionType action)
//		: m_operation()
//	{
//		switch (action)
//		{
//		case Hold:
//			m_operation = std::make_shared<RealtimeJoystickButtonLeaf>(joystick);
//			break;
//		case PressOnce:
//			break;
//		case ReleaseOnce:
//			m_operation = std::make_shared<EventJoystickLeaf>(joystick, action == PressOnce);
//			break;
//		}
//	}
//
//
//	Action::Action(JoystickAxis joysticState)
//		: m_operation(std::make_shared<RealtimeJoystickAxisLeaf>(joysticState))
//	{
//	}
//
//	Action::Action(sf::Event::EventType eventType)
//		: m_operation(std::make_shared<MiscEventLeaf>(eventType))
//	{
//
//	}
//
//	bool Action::isActive(const EventBuffer& buffer) const
//	{
//		return m_operation->isActionActive(buffer);
//	}
//
//	bool Action::isActive(const EventBuffer& buffer, ActionResult& out) const
//	{
//		return m_operation->isActionActive(buffer, out);
//	}
//
//	Action::Action(ActionNode::ActionPtr operation)
//	{
//		m_operation = std::move(operation);
//	}
//
//	Action operator|| (const Action& lhs, const Action& rhs)
//	{
//		return Action(std::make_shared<OrNode>(lhs.m_operation, rhs.m_operation));
//	}
//
//
//	Action operator&& (const Action& lhs, const Action& rhs)
//	{
//		return Action(std::make_shared<AndNode>(lhs.m_operation, rhs.m_operation));
//	}
//
//	Action operator! (const Action& action)
//	{
//		return Action(std::make_shared<NotNode>(action.m_operation));
//	}
//
//	Action eventAction(std::function<bool(const sf::Event&)> filter)
//	{
//		return Action(std::make_shared<CustomEventLeaf>(std::move(filter)));
//	}
//
//	Action realtimeAction(std::function<bool()> filter)
//	{
//		return Action(std::make_shared<CustomRealtimeLeaf>(std::move(filter)));
//	}
//
//}