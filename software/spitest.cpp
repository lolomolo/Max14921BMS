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


// channel is the wiringPi name for the chip select (or chip enable) pin.
// Set this to 0 or 1, depending on how it's connected.


static const float vref = 4.08;
unsigned char buffer[100];


int spiCom(int channel, int rate, int mode) {
	wiringPiSPISetupMode(channel, rate, mode);


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

int main()
{
   int CHANNEL = 1;

   buffer[0] = 0xAA;
   buffer[1] = 0b00001010;
   

   for(int i = 0; i<100; i++) {
	spiCom(CHANNEL, 500000, 3);
   }

}
