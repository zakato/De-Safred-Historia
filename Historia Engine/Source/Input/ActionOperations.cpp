//#include <Input\ActionOperations.hpp>
//
//#include <iterator>
//#include <algorithm>
//
//
//
//namespace zkt
//{
//	EventBuffer::EventBuffer()
//		: m_events()
//		, m_realtimeEnabled(true)
//	{
//
//	}
//
//	void EventBuffer::pushEvent(const sf::Event& event)
//	{
//		switch (event.type)
//		{
//		case sf::Event::GainedFocus:
//			m_realtimeEnabled = true;
//			break;
//
//		case sf::Event::LostFocus:
//			m_realtimeEnabled = false;
//			break;
//		}
//
//		
//		m_events.push_back(event);
//	}
//
//	void EventBuffer::clearEvents()
//	{
//		m_events.clear();
//	}
//
//	bool EventBuffer::containsEvent(const EventNode& filterNode) const
//	{
//		std::vector<sf::Event> unused;
//		return filterEvents(filterNode, unused);
//	}
//
//	bool EventBuffer::filterEvents(const EventNode& filterNode, std::vector<sf::Event>& out) const
//	{
//		// Variable to check if something was actually inserted (don't look at range, it's not filtered yet)
//		std::size_t oldSize = out.size();
//
//		// Copy events that fulfill filter criterion to the end of the output vector
//		std::copy_if(m_events.begin(), m_events.end(), std::back_inserter(out), std::bind(&EventNode::isEventActive, &filterNode, _1));
//		return oldSize != out.size();
//	}
//
//	bool EventBuffer::isRealtimeInputEnabled() const
//	{
//		return m_realtimeEnabled;
//	}
//
//	void EventBuffer::pollEvents(sf::Window& window)
//	{
//		sf::Event event;
//
//		while (window.pollEvent(event))
//			pushEvent(event);
//	}
//
//	
//
//	ActionNode::~ActionNode()
//	{
//	}
//
//	
//
//	EventNode::EventNode()
//		: m_event()
//	{
//	}
//
//	bool EventNode::isActionActive(const EventBuffer& buffer) const
//	{
//		return buffer.containsEvent(*this);
//	}
//
//	bool EventNode::isActionActive(const EventBuffer& buffer, ActionResult& out) const
//	{
//		return buffer.filterEvents(*this, out.eventContainer);
//	}
//
//
//	bool RealtimeNode::isActionActive(const EventBuffer& buffer) const
//	{
//		return buffer.isRealtimeInputEnabled() && isRealtimeActive();
//	}
//
//	bool RealtimeNode::isActionActive(const EventBuffer& buffer, ActionResult& out) const
//	{
//		if (isActionActive(buffer))
//		{
//			++out.nbRealtimeTriggers;
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//
//	
//	RealtimeKeyLeaf::RealtimeKeyLeaf(sf::Keyboard::Key key)
//		: RealtimeNode()
//		, m_key(key)
//	{
//	}
//
//	bool RealtimeKeyLeaf::isRealtimeActive() const
//	{
//		return sf::Keyboard::isKeyPressed(m_key);
//	}
//
//	
//
//	EventKeyLeaf::EventKeyLeaf(sf::Keyboard::Key key, bool pressed)
//		: EventNode()
//	{
//		m_event.type = pressed ? sf::Event::KeyPressed : sf::Event::KeyReleased;
//		m_event.key.code = key;
//	}
//
//	bool EventKeyLeaf::isEventActive(const sf::Event& event) const
//	{
//		return event.type == m_event.type && event.key.code == m_event.key.code;
//	}
//
//	
//
//	RealtimeMouseLeaf::RealtimeMouseLeaf(sf::Mouse::Button mouseButton)
//		: RealtimeNode()
//		, m_mouseButton(mouseButton)
//	{
//	}
//
//	bool RealtimeMouseLeaf::isRealtimeActive() const
//	{
//		return sf::Mouse::isButtonPressed(m_mouseButton);
//	}
//
//	
//
//	EventMouseLeaf::EventMouseLeaf(sf::Mouse::Button mouseButton, bool pressed)
//		: EventNode()
//	{
//		m_event.type = pressed ? sf::Event::MouseButtonPressed : sf::Event::MouseButtonReleased;
//		m_event.mouseButton.button = mouseButton;
//	}
//
//	bool EventMouseLeaf::isEventActive(const sf::Event& event) const
//	{
//		return event.type == m_event.type && event.mouseButton.button == m_event.mouseButton.button;
//	}
//
//	// ---------------------------------------------------------------------------------------------------------------------------
//
//
//	RealtimeJoystickButtonLeaf::RealtimeJoystickButtonLeaf(JoystickButton joystick)
//		: RealtimeNode()
//		, m_joystick(joystick)
//	{
//	}
//
//	bool RealtimeJoystickButtonLeaf::isRealtimeActive() const
//	{
//		return sf::Joystick::isButtonPressed(m_joystick.JoystickId, m_joystick.button);
//	}
//
//	// ---------------------------------------------------------------------------------------------------------------------------
//
//
//	RealtimeJoystickAxisLeaf::RealtimeJoystickAxisLeaf(JoystickAxis joystick)
//		: RealtimeNode()
//		, m_joystick(joystick)
//	{
//	}
//
//	bool RealtimeJoystickAxisLeaf::isRealtimeActive() const
//	{
//		float axisPos = sf::Joystick::getAxisPosition(m_joystick.JoystickId, m_joystick.axis);
//
//		return m_joystick.above && axisPos > m_joystick.threshold
//			|| !m_joystick.above && axisPos < m_joystick.threshold;
//	}
//
//	// ---------------------------------------------------------------------------------------------------------------------------
//
//
//	EventJoystickLeaf::EventJoystickLeaf(JoystickButton joystick, bool pressed)
//		: EventNode()
//	{
//		m_event.type = pressed ? sf::Event::JoystickButtonPressed : sf::Event::JoystickButtonReleased;
//		m_event.joystickButton.joystickId = joystick.JoystickId;
//		m_event.joystickButton.button = joystick.button;
//	}
//
//	bool EventJoystickLeaf::isEventActive(const sf::Event& event) const
//	{
//		return event.type == m_event.type && event.joystickButton.button == m_event.joystickButton.button;
//	}
//
//	// ---------------------------------------------------------------------------------------------------------------------------
//
//
//	MiscEventLeaf::MiscEventLeaf(sf::Event::EventType eventType)
//		: EventNode()
//	{
//		m_event.type = eventType;
//	}
//
//	bool MiscEventLeaf::isEventActive(const sf::Event& event) const
//	{
//		return m_event.type == event.type;
//	}
//
//	// ---------------------------------------------------------------------------------------------------------------------------
//
//
//	CustomEventLeaf::CustomEventLeaf(std::function<bool(const sf::Event&)> filter)
//		: m_filter(std::move(filter))
//	{
//	}
//
//	bool CustomEventLeaf::isEventActive(const sf::Event& event) const
//	{
//		return m_filter(event);
//	}
//
//	// ---------------------------------------------------------------------------------------------------------------------------
//
//
//	CustomRealtimeLeaf::CustomRealtimeLeaf(std::function<bool()> filter)
//		: m_filter(std::move(filter))
//	{
//	}
//
//	bool CustomRealtimeLeaf::isRealtimeActive() const
//	{
//		return m_filter();
//	}
//
//	// ---------------------------------------------------------------------------------------------------------------------------
//
//
//	OrNode::OrNode(ActionNode::ActionPtr lhs, ActionNode::ActionPtr rhs)
//		: ActionNode()
//		, m_lhs(std::move(lhs))
//		, m_rhs(std::move(rhs))
//	{
//	}
//
//	bool OrNode::isActionActive(const EventBuffer& buffer) const
//	{
//		return m_lhs->isActionActive(buffer) || m_rhs->isActionActive(buffer);
//	}
//
//	bool OrNode::isActionActive(const EventBuffer& buffer, ActionResult& out) const
//	{
//		// Prevent shortcut semantics of logical OR: If first operand is true, the second's vector isn't filled.
//		bool lhsValue = m_lhs->isActionActive(buffer, out);
//		bool rhsValue = m_rhs->isActionActive(buffer, out);
//
//		return lhsValue || rhsValue;
//	}
//
//	// ---------------------------------------------------------------------------------------------------------------------------
//
//
//	AndNode::AndNode(ActionNode::ActionPtr lhs, ActionNode::ActionPtr rhs)
//		: ActionNode()
//		, m_lhs(std::move(lhs))
//		, m_rhs(std::move(rhs))
//	{
//	}
//
//	bool AndNode::isActionActive(const EventBuffer& buffer) const
//	{
//		return m_lhs->isActionActive(buffer) && m_rhs->isActionActive(buffer);
//	}
//
//	bool AndNode::isActionActive(const EventBuffer& buffer, ActionResult& out) const
//	{
//		
//		ActionResult tmpResult;
//
//		
//		if (m_lhs->isActionActive(buffer, tmpResult) && m_rhs->isActionActive(buffer, tmpResult))
//		{
//			out.eventContainer.insert(out.eventContainer.end(), tmpResult.eventContainer.begin(), tmpResult.eventContainer.end());
//			out.nbRealtimeTriggers += tmpResult.nbRealtimeTriggers;
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//
//	
//
//	NotNode::NotNode(ActionNode::ActionPtr action)
//		: ActionNode()
//		, m_action(std::move(action))
//	{
//	}
//
//	bool NotNode::isActionActive(const EventBuffer& buffer) const
//	{
//		return !m_action->isActionActive(buffer);
//	}
//
//	bool NotNode::isActionActive(const EventBuffer& buffer, ActionResult& out) const
//	{
//		
//		ActionResult tmpResult;
//
//		if (!m_action->isActionActive(buffer, tmpResult))
//		{
//			out.eventContainer.insert(out.eventContainer.end(), tmpResult.eventContainer.begin(), tmpResult.eventContainer.end());
//			out.nbRealtimeTriggers += tmpResult.nbRealtimeTriggers;
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//
//
//}