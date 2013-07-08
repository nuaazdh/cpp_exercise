#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <process.h>

#pragma comment(lib,"Ws2_32.lib")

#define BUFFERSIZE	100

unsigned __stdcall ExecuteThread(void* lparam)
{
	SOCKET ClientSocket=(SOCKET)(void*)lparam;

	//char sendText[BUFFERSIZE];
	char recvText[BUFFERSIZE];


	if (recv(ClientSocket, recvText, 100, 0) != SOCKET_ERROR)
	{
		printf("receive text: %s\n", recvText);
		/*if (strcmp(recvText,"quit")==0 || strcmp(recvText,"exit")==0)
			break;
			*/
		/*sendText = */
	}

    strcat(recvText," has received.\n");
    send(ClientSocket, recvText, strlen(recvText)+1,0);

	_endthreadex(0);
	return 0;
}

int main(int argc, char* argv[])
{
	// (1)加载套接字库
	WORD wVersionRequested;			//WinSock库的版本号
	WSADATA wsaData;
	int iResult = 0;
	SOCKET sockSrv;
	SOCKADDR_IN addrSrv;
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);

	SOCKET sockConn;
	unsigned dwThreadId;
	HANDLE hThread;

	wVersionRequested = MAKEWORD(1, 1);
	iResult = WSAStartup(wVersionRequested, &wsaData);
	if( iResult != NO_ERROR)
	{
		printf("WSAStartup() failed with error: %d\n", iResult);
		return -1 ;
	}

	if( LOBYTE( wsaData.wVersion) != 1 || HIBYTE( wsaData.wVersion) !=1 )
	{
		WSACleanup();
		return -1;
	}
	// (2)创建用于监听的套接字
	sockSrv = socket(AF_INET, SOCK_STREAM, 0);
	if (sockSrv == INVALID_SOCKET)
	{
		printf("socket function failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}


	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(5555);

	// (3)绑定套接字
	iResult = bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	if (iResult == SOCKET_ERROR)
	{
		printf("bind function failed with error %d\n", WSAGetLastError());

		iResult = closesocket(sockSrv);
		if (iResult == SOCKET_ERROR)
		{
			printf("closesocket function failed with error %d\n", WSAGetLastError());
		}

		WSACleanup();
		return -1;
	}

	// (4)将套接字设为监听模式，准备接受客户请求
	iResult = listen(sockSrv, SOMAXCONN);
	if (iResult == SOCKET_ERROR)
	{
		printf("listen function failed with error: %d\n", WSAGetLastError());
	}

	printf("Listening on socket...\n");

	// (5)创建线程等待客户请求


	while(1)
	{
		//等待客户请求
		sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);
		if (sockConn == INVALID_SOCKET )
		{
			printf("accept function failed with error: %d\n", WSAGetLastError());
		}

		// _beginthreadx比createthread更安全
		hThread = (HANDLE)_beginthreadex(NULL, 0, &ExecuteThread, (void*)sockConn, 0, &dwThreadId );

		WaitForSingleObject(hThread, INFINITE );
	}

	// (6)结束处理
	CloseHandle(hThread);

	iResult = closesocket(sockConn);
	if (iResult == SOCKET_ERROR)
	{
		printf("closesocket function failed with error %d\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	WSACleanup();

	return 0;
}
