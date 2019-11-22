// Rat.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "NetworkHandler.h"
#include <iostream>


NetworkHandler NH(1);

using namespace std;

int main()
{
	int sen = 95;
	int Recv = 0;
	while (true) {
		//NH.SendData((char*)sen, sizeof(int));

		send(NH.sock, (char*)sen, sizeof(int), 0);

		cout << "sent " << sen << endl;
		Sleep(100);
		//NH.RecvData((char*)Recv);

		recv(NH.sock, (char*)Recv, sizeof(int), 0);

		cout << "recived " << Recv << endl;
	}
	system("pause");
}