#include <Message\Message.hpp>


namespace zkt {

	Message::Message(int sender, int reciever, bool isSynchronous)
	{
		m_idSender = sender;
		m_idReciever = reciever;
		m_isSynchronous = isSynchronous;
	}


	int Message::getIdSender() const
	{
		return m_idSender;
	}

	int Message::getIdReciever() const
	{
		return m_idReciever;
	}
	
	bool Message::isSynchronous() const
	{
		m_isSynchronous;
	}
}