#ifndef _CSOCKETCLIENT_H_
#define _CSOCKETCLIENT_H_

#include "csocket.h"

class CSocketClient : public CSocket
{
		bool IsConnected;

		bool StopTheReconnect;

		TDescriptor descriptor;

		void Init();

	protected :

		bool Connect(struct sockaddr* server, size_t size_of_server);

	public :

		CSocketClient();
		virtual ~CSocketClient();

		// Bring base class functions into scope
		using CSocket::Send;
		using CSocket::SendBigData;
		using CSocket::Read;
		using CSocket::ReadBigData;

		// Convenience functions that use stored descriptor
		ssize_t Send(const char* data, ssize_t sizeOfData);
		ssize_t SendBigData(const char* data, TMinimalSize sizeOfData);
		ssize_t Read(char* data, ssize_t sizeOfData);
		ssize_t ReadBigData(CDynBuffer* data);

		bool ConnectLoop();

	// virtual :
		virtual bool _Configure() = 0;
		virtual bool _Connect() = 0;
		virtual int _GetID() = 0;
};

#endif
