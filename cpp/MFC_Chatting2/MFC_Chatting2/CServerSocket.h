#pragma once
class CServerSocket
{
public:
	CServerSocket(SOCKET sock = INVALID_SOCKET);
	~CServerSocket();

	bool Create(unsigned short port, const char*ip = nullptr);
	SOCKET Accept(sockaddr_in *addr = nullptr, int *addrSize = nullptr);
	void Close();
	bool IsValid() { return mSock != INVALID_SOCKET; }

public:
	SOCKET mSock;
};
