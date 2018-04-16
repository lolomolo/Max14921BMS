/******************************************************************************
i2ctest.cpp
Max14921 BMS and ADS8638 ADC

Danny Andreev
https://github.com/lolomolo/Max14921BMS

****************************************************************************/

#define adcPin 24
#include <iostream>
#include <errno.h>
#include <wiringPiSPI.h>
#include <unistd.h>
#include <bitset>
#include <wiringPi.h>
using namespace std;

static const float vref = 4.08;
unsigned char adcBuffer[100];
unsigned char bmsBuffer[100];


int spiCom(unsigned char *buffer, int channel, int rate, int mode) {

   	buffer[0] = 0xAA;
	buffer[1] = 0XAA;


	cout << "buffer[0]: " << std::bitset<8>(buffer[0]) << endl;
   	cout << "buffer[1]: " << std::bitset<8>(buffer[1]) << endl;
	wiringPiSPIDataRW(channel, buffer, 2);
   	cout << "new buffer[0]: " << std::bitset<8>(buffer[0]) << endl;
   	cout << "new buffer[1]: " << std::bitset<8>(buffer[1]) << endl;
	float aout = (buffer[1]+(buffer[0]<<8));
	aout=vref*(aout/(1<<13));
	cout << "voltage reading: " << aout << endl << endl;
   	usleep(20000);
}

int main() {
	int CHANNEL = 1;
	int rate = 500000;
	int defMode = 3;

   	adcBuffer[0] = 0xAA;
   	adcBuffer[1] = 0b00001010;
   
  	wiringPiSPISetupMode(CHANNEL, rate, defMode);
   	
	for(int i = 0; i<100; i++) {
		spiCom(adcBuffer, CHANNEL, 500000, 3);
   	}
}
