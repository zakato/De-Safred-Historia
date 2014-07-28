#ifndef ACTIONMAP_HPP
#define ACTIONMAP_HPP

#include <Input\Action.hpp>
#include <Input\ActionOperations.hpp>
#include <Input\ActionContext.hpp>

namespace zkt {

	template <typename Event, typename EventId>
	class EventSystem;



	template <typename ActionId>
	class ActionMap 
	{
		
	public:
		
		typedef EventSystem< ActionContext<ActionId>, ActionId > CallbackSystem;


		
	public:
		
		ActionMap();
		ActionMap(ActionMap&& source);
		ActionMap&					operator= (ActionMap&& source);

		void						update(sf::Window& window);

		void						pushEvent(const sf::Event& event);

		void						clearEvents();

		
		Action&						operator[] (const ActionId& id);

		void						removeAction(const ActionId& id);

		void						clearActions();

		
		bool						isActive(const ActionId& id) const;

		void						invokeCallbacks(CallbackSystem& system, sf::Window* window) const;


	
	private:
		typedef std::map<ActionId, Action> Map;


	private:
		Map							mActionMap;
		EventBuffer					mEventBuffer;
	};



}

#include <Input\ActionMap.inl>

#endif