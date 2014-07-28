#include <Input/Connection.hpp>
#include <Input/ConnectionImpl.hpp>


namespace zkt
{

	Connection::Connection()
		: mWeakRef()
	{
	}

	Connection::Connection(std::weak_ptr<AbstractConnectionImpl> tracker)
		: mWeakRef(std::move(tracker))
	{
	}

	bool Connection::isConnected() const
	{
		return !mWeakRef.expired();
	}

	void Connection::invalidate()
	{
		mWeakRef.reset();
	}

	void Connection::disconnect()
	{
		if (auto shared = mWeakRef.lock())
		{
			shared->disconnect();
			invalidate();
		}
	}

	// ---------------------------------------------------------------------------------------------------------------------------


	ScopedConnection::ScopedConnection()
		: mConnection()
	{
	}

	ScopedConnection::ScopedConnection(const Connection& connection)
		: mConnection(connection)
	{
	}

	ScopedConnection::ScopedConnection(ScopedConnection&& source)
		: mConnection(source.mConnection)
	{
		source.mConnection.invalidate();
	}

	ScopedConnection& ScopedConnection::operator= (ScopedConnection&& source)
	{
		mConnection = source.mConnection;
		source.mConnection.invalidate();

		return *this;
	}

	ScopedConnection::~ScopedConnection()
	{
		mConnection.disconnect();
	}

	bool ScopedConnection::isConnected() const
	{
		return mConnection.isConnected();
	}

}