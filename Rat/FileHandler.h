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
	NetworkHandler * NetHandle;
public:
	FileHandler(NetworkHandler NH);
	~FileHandler();
	bool SendFile(string FilePath);
	vector<char> RecvFile();
};

