#pragma once
class NetworkHandler
{
public:
	NetworkHandler();
	~NetworkHandler();
	bool SendData(char*data,int size);
	bool RecvData();
};

