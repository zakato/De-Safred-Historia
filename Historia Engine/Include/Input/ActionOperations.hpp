#ifndef ACTIONOPERATION_HPP
#define ACTIONOPERATION_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Joystick.hpp>
#include <SFML\Window\Window.hpp>

#include <vector>
#include <memory>
#include <functional>

#include <Input\Joystick.hpp>



namespace zkt
{
	class EventNode;

	class EventBuffer
	{
	public:
		EventBuffer();

		void pushEvent(const sf::Event& event);
		void clearEvents();
		void pollEvents(sf::Window& window);

		bool containsEvent(const EventNode& filterNode) const;
		bool filterEvents(const EventNode& filterNode, std::vector<sf::Event>& out) const;
		bool isRealtimeInputEnabled() const;

	private:
		std::vector<sf::Event> m_events;
		bool m_realtimeEnabled;

	};




	struct ActionResult
	{
		ActionResult();

		std::vector<sf::Event> eventContainer;
		unsigned int	nbRealtimeTriggers;
	};




	class ActionNode
	{
	public:
		typedef std::shared_ptr<ActionNode>	ActionPtr;

	public:
		virtual ~ActionNode();
		virtual bool isActionActive(const EventBuffer& buffer) const = 0;
		virtual bool isActionActive(const EventBuffer& buffer, ActionResult& out) const = 0;
	};




	class EventNode : public ActionNode
	{
	public:
		EventNode();

		virtual bool isActionActive(const EventBuffer& buffer) const;
		virtual bool isActionActive(const EventBuffer& buffer, ActionResult& out) const;
		virtual bool isEventActive(const sf::Event& event) const = 0;

	protected:
		sf::Event m_event;
	};






	class RealtimeNode : public ActionNode
	{
	public:
		virtual bool isActionActive(const EventBuffer& buffer) const;
		virtual bool isActionActive(const EventBuffer& buffer, ActionResult& out) const;
		virtual bool isRealtimeActive() const = 0;
	};





	class RealtimeKeyLeaf : public RealtimeNode
	{
	public:
		explicit					RealtimeKeyLeaf(sf::Keyboard::Key key);
		virtual bool				isRealtimeActive() const;

	private:
		sf::Keyboard::Key			m_key;
	};





	
	class EventKeyLeaf : public EventNode
	{
	public:
		EventKeyLeaf(sf::Keyboard::Key key, bool pressed);
		virtual bool				isEventActive(const sf::Event& event) const;
	};





	class RealtimeMouseLeaf : public RealtimeNode
	{
	public:
		explicit					RealtimeMouseLeaf(sf::Mouse::Button mouseButton);
		virtual bool				isRealtimeActive() const;

	private:
		sf::Mouse::Button			m_mouseButton;
	};

	




	class EventMouseLeaf : public EventNode
	{
	public:
		EventMouseLeaf(sf::Mouse::Button mouseButton, bool pressed);
		virtual bool				isEventActive(const sf::Event& event) const;
	};







	class RealtimeJoystickButtonLeaf : public RealtimeNode
	{
	public:
		explicit					RealtimeJoystickButtonLeaf(JoystickButton joystick);
		virtual bool				isRealtimeActive() const;

	private:
		JoystickButton				m_joystick;
	};







	
	class RealtimeJoystickAxisLeaf : public RealtimeNode
	{
	public:
		RealtimeJoystickAxisLeaf(JoystickAxis joystick);
		virtual bool				isRealtimeActive() const;

	private:
		JoystickAxis				m_joystick;
	};






	
	class EventJoystickLeaf : public EventNode
	{
	public:
		EventJoystickLeaf(JoystickButton joystick, bool pressed);
		virtual bool				isEventActive(const sf::Event& event) const;
	};





	
	class MiscEventLeaf : public EventNode
	{
	public:
		explicit					MiscEventLeaf(sf::Event::EventType eventType);
		virtual bool				isEventActive(const sf::Event& event) const;
	};






	
	class CustomEventLeaf : public EventNode
	{
	public:
		explicit					CustomEventLeaf(std::function<bool(const sf::Event&)> filter);
		virtual bool				isEventActive(const sf::Event& event) const;

	private:
		std::function<bool(const sf::Event&)>	m_filter;
	};





	
	class CustomRealtimeLeaf : public RealtimeNode
	{
	public:
		explicit					CustomRealtimeLeaf(std::function<bool()> filter);
		virtual bool				isRealtimeActive() const;

	private:
		std::function<bool()>		m_filter;
	};






	
	class OrNode : public ActionNode
	{
	public:
		OrNode(ActionNode::ActionPtr lhs, ActionNode::ActionPtr rhs);
		virtual bool				isActionActive(const EventBuffer& buffer) const;
		virtual bool				isActionActive(const EventBuffer& buffer, ActionResult& out) const;

	private:
		ActionNode::ActionPtr		m_lhs;
		ActionNode::ActionPtr		m_rhs;
	};






	
	class AndNode : public ActionNode
	{
	public:
		AndNode(ActionNode::ActionPtr lhs, ActionNode::ActionPtr rhs);
		virtual	bool				isActionActive(const EventBuffer& buffer) const;
		virtual bool				isActionActive(const EventBuffer& buffer, ActionResult& out) const;

	private:
		ActionNode::ActionPtr		m_lhs;
		ActionNode::ActionPtr		m_rhs;
	};

	





	class NotNode : public ActionNode
	{
	public:
		explicit					NotNode(ActionNode::ActionPtr action);
		virtual	bool				isActionActive(const EventBuffer& buffer) const;
		virtual bool				isActionActive(const EventBuffer& buffer, ActionResult& out) const;

	private:
		ActionNode::ActionPtr		m_action;
	};


}


#endif