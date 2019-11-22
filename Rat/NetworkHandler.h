#pragma once

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <vector>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
#include <vector>

using namespace std;

class NetworkHandler
{
	
	string ip;
	string port;
public:
	vector<SOCKET> sock;
	NetworkHandler(bool isClient,string ipAdder= "127.0.0.1", string prt = "24000");
	~NetworkHandler();
	bool SendData(char*data,int size);
	bool RecvData(char * buff);
};

