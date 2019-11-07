#pragma once
#include <vector>

using namespace std;

class NetworkHandler
{
public:
	NetworkHandler();
	~NetworkHandler();
	bool SendData(char*data,int size);
	bool RecvData(char * buff);
};

