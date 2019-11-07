#include "pch.h"
#include "FileHandler.h"


FileHandler::FileHandler(NetworkHandler NH)
{
	NetHandle = &NH;
}


FileHandler::~FileHandler()
{
}


bool FileHandler::SendFile(string FilePath)
{
	ifstream File(FilePath, ifstream::in | ifstream::binary);

	while (!File.eof()) {
		vector<char> buffer;
		File.read(buffer.data(), buffer.size());
		NetHandle->SendData(buffer.data(),buffer.size());
	}

	return false;
}


vector<char> FileHandler::RecvFile()
{
	vector<char> buffer;

	NetHandle->RecvData()

	destination.write(buffer.data(), source.gcount());
	// TODO: Add your implementation code here.
	return false;
}

int getFileSize(const std::string & fileName)
{
	ifstream file(fileName.c_str(), ifstream::in | ifstream::binary);

	if (!file.is_open())
	{
		return -1;
	}

	file.seekg(0, ios::end);
	int fileSize = file.tellg();
	file.close();

	return fileSize;
}
