


namespace zkt
{

	template <typename ActionId>
	ActionMap<ActionId>::ActionMap()
	{
	}

	template <typename ActionId>
	ActionMap<ActionId>::ActionMap(ActionMap&& source)
		: mActionMap(std::move(source.mActionMap))
		, mEventBuffer(std::move(source.mEventBuffer))
	{
	}

	template <typename ActionId>
	ActionMap<ActionId>& ActionMap<ActionId>::operator= (ActionMap&& source)
	{
		mActionMap = std::move(source.mActionMap);
		mEventBuffer = std::move(source.mEventBuffer);

		return *this;
	}

	template <typename ActionId>
	void ActionMap<ActionId>::update(sf::Window& window)
	{
		mEventBuffer.clearEvents();
		mEventBuffer.pollEvents(window);
	}

	template <typename ActionId>
	void ActionMap<ActionId>::pushEvent(const sf::Event& event)
	{
		mEventBuffer.pushEvent(event);
	}

	template <typename ActionId>
	void ActionMap<ActionId>::clearEvents()
	{
		mEventBuffer.clearEvents();
	}

	template <typename ActionId>
	Action& ActionMap<ActionId>::operator[] (const ActionId& id)
	{
		return mActionMap[id];
	}

	template <typename ActionId>
	void ActionMap<ActionId>::removeAction(const ActionId& id)
	{
		mActionMap.erase(id);
	}

	template <typename ActionId>
	void ActionMap<ActionId>::clearActions()
	{
		mActionMap.clear();
	}

	template <typename ActionId>
	bool ActionMap<ActionId>::isActive(const ActionId& id) const
	{
		typename Map::const_iterator action = mActionMap.find(id);
		if (action == mActionMap.end())
			return false;

		return action->second.isActive(mEventBuffer);
	}

	template <typename ActionId>
	void ActionMap<ActionId>::invokeCallbacks(CallbackSystem& system, sf::Window* window) const
	{
		for(const auto& actionPair : mActionMap)
		{
			ActionResult result;
			if (!actionPair.second.isActive(mEventBuffer, result))
				continue;

			
			for(const sf::Event& event : result.eventContainer)
				system.triggerEvent(ActionContext<ActionId>(window, &event, actionPair.first));

			if (result.nbRealtimeTriggers > 0 && result.eventContainer.empty())
				system.triggerEvent(ActionContext<ActionId>(window, nullptr, actionPair.first));
		}
	}

}