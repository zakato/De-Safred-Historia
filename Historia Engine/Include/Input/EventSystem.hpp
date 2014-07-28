#ifndef EVENTSYSTEM_HPP
#define EVENTSYSTEM_HPP

#include <Input\EventListner.hpp>
#include <Input/Connection.hpp>
#include <Input/ConnectionImpl.hpp>

namespace zkt
{

	
	template <typename Event, typename EventId = Event>
	class EventSystem 
	{
		
	public:
		
		EventSystem();
		void						triggerEvent(const Event& event);

		Connection					connect(const EventId& trigger, std::function<void(const Event&)> unaryListener);
		Connection					connect0(const EventId& trigger, std::function<void()> nullaryListener);
		void						clearConnections(EventId identifier);
		void						clearAllConnections();

	private:
		
		typedef ListenerMap<EventId, const Event&>	EventListenerMap;

	private:
		EventListenerMap			mListeners;
	};

	

} 

#include <Input/EventSystem.inl>
#endif