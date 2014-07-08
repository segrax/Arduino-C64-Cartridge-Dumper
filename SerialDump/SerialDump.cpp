#include <stdio.h>
#include <tchar.h>
#include "SerialClass.h"
#include <string>
#include <fstream>

int _tmain(int argc, _TCHAR* argv[]) {
	printf("C64 Cartridge Dumper");

	Serial* SP = new Serial("\\\\.\\COM3");

	if (SP->IsConnected())
		printf("connected");
	else
		exit(1);

	char incomingData[0x200] = "";

	int totalRead = 0x2000;
	int dataLength = 0x1ff;
	int readResult = 0;
	int readTotal = 0;
	
	SP->WriteData("DUMP\n", 5);
	Sleep(2000);

	SP->ReadData(incomingData,0x09);

	std::ofstream myFile ("dump.bin", std::ios::out | std::ios::binary);

	while(SP->IsConnected()) {
		readResult = SP->ReadData(incomingData,dataLength);
		if( readResult == -1 )
			continue;

		myFile.write (incomingData, readResult);
		readTotal += readResult;

		if( readTotal >= totalRead )
			break;

		printf("Bytes read: %i\n",readResult);

		Sleep(1000);
	}
	myFile.close();
	return 0;
}