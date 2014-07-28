#ifndef CONNECTIONIMPL_HPP
#define CONNECTIONIMPL_HPP


#include <algorithm>
#include <memory>


namespace zkt
{
	
		
		class AbstractConnectionImpl
		{
		public:
			
			virtual void disconnect() = 0;

			
			virtual ~AbstractConnectionImpl()
			{
			}
		};

		
		template <typename List>
		class IteratorConnectionImpl : public AbstractConnectionImpl
		{
		private:
			typedef typename List::Iterator Iterator;

		public:
			
			IteratorConnectionImpl(List& container, Iterator iterator)
				: mContainer(&container)
				, mIterator(iterator)
			{
			}

			virtual void disconnect()
			{
				mContainer->remove(mIterator);
			}

		private:
			List*		mContainer;
			Iterator	mIterator;
		};

		
		template <typename Container>
		class IdConnectionImpl : public AbstractConnectionImpl
		{
		private:
			typedef typename Container::value_type ValueType;

		public:
			
			IdConnectionImpl(Container& container, unsigned int id)
				: mContainer(&container)
				, mId(id)
			{
			}

			virtual void disconnect()
			{
				
				auto found = std::find_if(mContainer->begin(), mContainer->end(), [this](ValueType& v) { return v.id == mId; });

				if (found != mContainer->end())
					mContainer->erase(found);
			}

		private:
			Container*			mContainer;
			unsigned int		mId;
		};

		template <typename List>
		std::shared_ptr<IteratorConnectionImpl<List>> makeIteratorConnectionImpl(List& container, typename List::Iterator iterator)
		{
			return std::make_shared<IteratorConnectionImpl<List>>(container, iterator);
		}

		template <typename Container>
		std::shared_ptr<IdConnectionImpl<Container>> makeIdConnectionImpl(Container& container, unsigned int id)
		{
			return std::make_shared<IdConnectionImpl<Container>>(container, id);
		}

	 
}

#endif