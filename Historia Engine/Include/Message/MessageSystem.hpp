#ifndef MESSAGESYSTEM_HPP
#define MESSAGESYSTEM_HPP

#include <Artemis\EntityProcessingSystem.hpp>
#include <Artemis\ComponentMapper.hpp>

#include <Message\Message.hpp>
#include <Message\MessageType.hpp>

#include <map>
#include <bitset>
#include <memory>

namespace zkt {


	class MessageSystem {
	public:
		typedef std::multimap<std::bitset<MSGTYPESIZE>, Message> MessageMap;
		typedef std::multimap<std::bitset<MSGTYPESIZE>, Message>::iterator MessageIterator;
		typedef std::bitset<MSGTYPESIZE> MessageType;
	public:
		MessageSystem();
		void insertMessage(bool isSynchronous, int idSender, int idReciever, MessageType messageType);
		bool hasMessage(MessageType messageType) const;
		MessageIterator getMessageIterator(MessageType messageType);
		void deleteMessage(MessageType messageType);
		void clearMessageMap();



		
	private:
		MessageMap m_multimapMessage;

	};

}

#endif