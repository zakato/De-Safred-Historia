namespace zkt
{

	template <typename Event, typename EventId>
	EventSystem<Event, EventId>::EventSystem()
		: mListeners()
	{
	}

	template <typename Event, typename EventId>
	void EventSystem<Event, EventId>::triggerEvent(const Event& event)
	{
		
		

		mListeners.call(getEventId(event), event);
	}

	template <typename Event, typename EventId>
	Connection EventSystem<Event, EventId>::connect(const EventId& trigger, std::function<void(const Event&)> unaryListener)
	{
		return mListeners.add(trigger, std::move(unaryListener));
	}

	template <typename Event, typename EventId>
	Connection EventSystem<Event, EventId>::connect0(const EventId& trigger, std::function<void()> nullaryListener)
	{
		return connect(trigger, std::bind(std::move(nullaryListener)));
	}

	template <typename Event, typename EventId>
	void EventSystem<Event, EventId>::clearConnections(EventId identifier)
	{
		mListeners.clear(identifier);
	}

	template <typename Event, typename EventId>
	void EventSystem<Event, EventId>::clearAllConnections()
	{
		mListeners.clearAll();
	}


	

		template <typename Event>
		const Event& getEventId(const Event& event)
		{
			return event;
		}

	
}