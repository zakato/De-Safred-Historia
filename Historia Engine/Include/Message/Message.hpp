#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <Message\MessageType.hpp>

#include <bitset>

namespace zkt {


	class Message {

	public:
		explicit Message(int sender, int reciever,  bool isSynchronous);
		int getIdSender() const;
		int getIdReciever() const;
		bool isSynchronous() const;
	
	private:
		int m_idSender;
		int m_idReciever;
		bool m_isSynchronous;
	};

}






#endif