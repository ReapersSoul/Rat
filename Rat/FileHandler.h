#pragma once

#include <Windows.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include "NetworkHandler.h"

using namespace std;

int getFileSize(const std::string &fileName);

class FileHandler
{
	int packSize;
	NetworkHandler * NetHandle;
public:
	FileHandler(NetworkHandler * NH,int packetSize);
	~FileHandler();
	bool SendFile(string FilePath);
	vector<char> RecvFile();
};

