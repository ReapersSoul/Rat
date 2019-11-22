#include "pch.h"
#include "FileHandler.h"


FileHandler::FileHandler(NetworkHandler * NH,int packetSize=512)
{
	packSize = packetSize;
	NetHandle = NH;
}


FileHandler::~FileHandler()
{
}


bool FileHandler::SendFile(string FilePath,string filename)
{
	int remainingBytes = getFileSize(FilePath);

	ifstream File(FilePath, ifstream::in | ifstream::binary);

	string FileName=filename;

	NetHandle->SendData((char*)FileName.c_str(), sizeof((char*)FileName.c_str()));

	NetHandle->SendData((char*)remainingBytes, sizeof(int));


	//should work?
	while (remainingBytes > 0) {
		if (remainingBytes < packSize) {
			vector<char> buffer;
			buffer.resize(packSize);
			File.read(buffer.data(), remainingBytes);
			if (NetHandle->SendData((char*)remainingBytes, sizeof(int))) {
				if (!NetHandle->SendData(buffer.data(), remainingBytes)) {
					return false;
				}
			}
			remainingBytes -= remainingBytes;
		}
		else {
			vector<char> buffer;
			File.read(buffer.data(), packSize);
			if (NetHandle->SendData((char*)packSize, sizeof(int))) {
				if (!NetHandle->SendData(buffer.data(), packSize)) {
					return false;
				}
			}
			remainingBytes -= packSize;
		}
	}
	return true;
}


bool FileHandler::RecvFile()
{
	string FileName;

	int FileSize = 0;

	NetHandle->RecvData((char*)FileName.c_str());

	NetHandle->RecvData((char*)FileSize);

	if (FileSize != 0) {
		ofstream File(FileName, ifstream::out | ifstream::binary);

		int fileSize = 0;

		while (fileSize != FileSize) {

			int PacketSize = 0;

			NetHandle->RecvData((char*)PacketSize);

			char tmp;

			char * buffer=&tmp;

			NetHandle->RecvData(buffer);

			File.write(buffer, PacketSize);

			fileSize += PacketSize;
		}
		return true;
	}
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
