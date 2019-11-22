#include "pch.h"
#include "NetworkHandler.h"


NetworkHandler::NetworkHandler(bool isClient, string ipAdder, string prt)
{

	port = prt;
	ip = ipAdder;

	WSADATA wsaData;

	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return;
	}

	if (isClient) {
		addrinfo *result = NULL,
			*ptr = NULL,
			hints;

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		// Resolve the server address and port
		iResult = getaddrinfo(ip.c_str(), port.c_str(), &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed: %d\n", iResult);
			WSACleanup();
			return;
		}

		// Attempt to connect to the first address returned by
// the call to getaddrinfo
		ptr = result;

		// Create a SOCKET for connecting to server
		sock = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);

		if (sock == INVALID_SOCKET) {
			printf("Error at socket(): %ld\n", WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
			return;
		}

		// Connect to server.
		iResult = connect(sock, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(sock);
			sock = INVALID_SOCKET;
		}

		// Should really try the next address returned by getaddrinfo
		// if the connect call failed
		// But for this simple example we just free the resources
		// returned by getaddrinfo and print an error message

		freeaddrinfo(result);

		if (sock == INVALID_SOCKET) {
			printf("Unable to connect to server!\n");
			WSACleanup();
			return;
		}

	}
	else {
		addrinfo *result = NULL, *ptr = NULL, hints;
		
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;

		// Resolve the local address and port to be used by the server
		iResult = getaddrinfo(NULL, port.c_str(), &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed: %d\n", iResult);
			WSACleanup();
			return;
		}
	
		sock = INVALID_SOCKET;
	
		sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

		if (sock == INVALID_SOCKET) {
			printf("Error at socket(): %ld\n", WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
			return;
		}

		// Setup the TCP listening socket
		iResult = bind(sock, result->ai_addr, (int)result->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			printf("bind failed with error: %d\n", WSAGetLastError());
			freeaddrinfo(result);
			closesocket(sock);
			WSACleanup();
			return;
		}

		freeaddrinfo(result);

		if (listen(sock, SOMAXCONN) == SOCKET_ERROR) {
			printf("Listen failed with error: %ld\n", WSAGetLastError());
			closesocket(sock);
			WSACleanup();
			return;
		}

		SOCKET ClientSocket;

		ClientSocket = INVALID_SOCKET;

		// Accept a client socket
		ClientSocket = accept(sock, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET) {
			printf("accept failed: %d\n", WSAGetLastError());
			closesocket(sock);
			WSACleanup();
			return;
		}



	}

}


NetworkHandler::~NetworkHandler()
{
}


bool NetworkHandler::SendData(char*data, int size)
{
	// TODO: Add your implementation code here.
	send(sock, (char*)size, sizeof(int), 0);
	Sleep(100);
	send(sock, data, size, 0);

	//check to make sure recved
	return false;
}


bool NetworkHandler::RecvData(char * Data)
{
	// TODO: Add your implementation code here.
	int size = 0;
	recv(sock, (char*)size, sizeof(int), 0);
	Sleep(100);
	recv(sock, Data, size, 0);
	return false;
}
