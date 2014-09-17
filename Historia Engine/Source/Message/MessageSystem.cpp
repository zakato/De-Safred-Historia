#include <Message\MessageSystem.hpp>



namespace zkt {

	MessageSystem::MessageSystem()
	{

	}

	void MessageSystem::insertMessage(bool isSynchronous, int idSender, int idReciever, MessageType messageType)
	{
		Message message(idSender, idReciever, isSynchronous);
		m_multimapMessage.insert(std::make_pair(messageType, message));
	}

	bool MessageSystem::hasMessage(MessageType messageType) const
	{
		if (m_multimapMessage.count(messageType) > 0)
			return true;
		else
			return false;
	}

	MessageSystem::MessageIterator MessageSystem::getMessageIterator(MessageType messageType)
	{
		return m_multimapMessage.find(messageType);
	}

	void MessageSystem::deleteMessage(MessageType messageType)
	{
		m_multimapMessage.erase(messageType);
	}
	
	void MessageSystem::clearMessageMap()
	{
		m_multimapMessage.clear();
	}




}