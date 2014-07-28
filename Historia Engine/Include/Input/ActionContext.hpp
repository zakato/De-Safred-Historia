#ifndef ACTIONCONTEXT_HPP
#define ACTIONCONTEXT_HPP



namespace  zkt {

	template <typename ActionId>
	struct ActionContext
	{
		
		ActionContext(sf::Window* window, const sf::Event* event, const ActionId& actionId)
		: window(window)
		, event(event)
		, actionId(actionId)
		{
		}

		
		sf::Window*					window;

		
		const sf::Event*			event;

		
		ActionId					actionId;
	};

	
	template <typename ActionId>
	ActionId getEventId(const ActionContext<ActionId>& event)
	{
		return event.actionId;
	}

	
}


#endif