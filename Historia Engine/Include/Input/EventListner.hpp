#ifndef EVENTLISTNER_HPP
#define EVENTLISTNER_HPP

#include <Input/Connection.hpp>
#include <Input/ConnectionImpl.hpp>

#include <functional>
#include <vector>
#include <map>
#include <algorithm>


namespace zkt
{
	
		
		template <typename Parameter>
		class Listener
		{
		private:
			
			typedef std::function<void(Parameter)> Function;

		public:
			
			Listener(const Function& fn)
				: mFunction(fn)
				, mStrongRef() 
			{
			}

			
			void call(Parameter arg) const
			{
				mFunction(arg);
			}

			
			void swap(Listener& other)
			{
				std::swap(mFunction, other.mFunction);
				std::swap(mStrongRef, other.mStrongRef);
			}

			
			template <class ListenerContainer>
			void setEnvironment(ListenerContainer& container, typename ListenerContainer::Iterator iterator)
			{
				mStrongRef = makeIteratorConnectionImpl(container, iterator);
			}

			
			Connection shareConnection() const
			{
				return Connection(mStrongRef);
			}

		private:
			Function								mFunction;
			std::shared_ptr<AbstractConnectionImpl>	mStrongRef;
		};


		template <typename Parameter>
		class ListenerSequence
		{
		public:
			
			typedef Listener<Parameter>				ValueType;

		private:
			
			typedef std::vector<ValueType>			Container;

		public:
			
			typedef typename Container::iterator	Iterator;

		public:
			
			Connection add(const ValueType& listener)
			{
				
				mListeners.push_back(listener);

				
				Iterator added = mListeners.end() - 1;
				added->setEnvironment(*this, added);

				
				return added->shareConnection();
			}

			
			void remove(Iterator iterator)
			{
			
				iterator->swap(mListeners.back());
				mListeners.pop_back();
			}

			
			void clear()
			{
				mListeners.clear();
			}

			
			void call(Parameter arg) const
			{
				for(const ValueType& listener, mListeners)
					listener.call(arg);
			}

		private:
			Container mListeners;
		};


	
		template <typename Trigger, typename Parameter>
		class ListenerMap
		{
		public:
			
			typedef Listener<Parameter>							ValueType;

			
			typedef Trigger										KeyType;

		private:
			
			typedef std::multimap<KeyType, ValueType>			Container;

			
			typedef typename Container::const_iterator			ConstIterator;

		public:
			
			typedef typename Container::iterator				Iterator;

		public:
			
			Connection add(const KeyType& trigger, const ValueType& listener)
			{
				
				Iterator added = mListeners.insert(std::make_pair(trigger, listener));

				
				added->second.setEnvironment(*this, added);

				
				return added->second.shareConnection();
			}

			
			void remove(Iterator iterator)
			{
				mListeners.erase(iterator);
			}

			
			void clear(KeyType key)
			{
				mListeners.erase(key);
			}

			
			void clearAll()
			{
				mListeners.clear();
			}

			
			void call(Trigger event, Parameter arg) const
			{
				std::pair<ConstIterator, ConstIterator> range = mListeners.equal_range(event);

				for (ConstIterator itr = range.first; itr != range.second; ++itr)
					itr->second.call(arg);
			}

		private:
			Container mListeners;
		};

	
} 

#endif