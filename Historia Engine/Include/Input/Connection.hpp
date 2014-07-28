#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <Input\ConnectionImpl.hpp>

#include <memory>

namespace zkt {

	class  Connection
	{
		
	public:
		
		Connection();
		bool						isConnected() const;
		void						invalidate();
		void						disconnect();

	public:
		explicit					Connection(std::weak_ptr<AbstractConnectionImpl> tracker);

	private:
		std::weak_ptr<AbstractConnectionImpl> mWeakRef;
	};


	
	class  ScopedConnection 
	{
		

	public:
	
		ScopedConnection();

		
		explicit					ScopedConnection(const Connection& connection);
									ScopedConnection(ScopedConnection&& source);
		ScopedConnection&			operator= (ScopedConnection&& source);
		~ScopedConnection();
		bool						isConnected() const;


	private:
		Connection					mConnection;
	};

} 

#endif


