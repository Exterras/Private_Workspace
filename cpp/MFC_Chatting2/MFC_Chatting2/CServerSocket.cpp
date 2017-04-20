CServerSocket::CServerSocket(SOCKET sock) : mSock(sock)
{
}


CServerSocket::~CServerSocket()
{
}

bool CServerSocket::Create(unsigned short port, const char*ip)
{
	if (IsValid() == true)
		return true;

	mSock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (mSock == INVALID_SOCKET)
		return false;

	sockaddr_in addr{ 0 };

	addr.sin_addr.S_un.S_addr = (ip == nullptr) ? INADDR_ANY : inet_addr(ip);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	::bind(mSock, (sockaddr*)&addr, sizeof(addr));
	int ret = ::listen(mSock, SOMAXCONN);

	if (ret == SOCKET_ERROR)
	{
		Close();
		return false;
	}

	return true;
}

