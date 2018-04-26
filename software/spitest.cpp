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
static const int adcCHANNEL = 1;
static const int bmsCHANNEL = 0;

static const int adcRate = 500000;
static const int bmsRate = 100000;

static const int adcMode = 0;
static const int bmsMode = 0;


int convTwoToDec(uint16_t twos) {
	if((twos & 0b0010000000000000)==0){
		cout << "pos " << twos <<endl;
		return(twos);
	} else {
		int derp =(~(twos << 3)-1);
		cout << "neg "<< twos << "bits and shit: " << std::bitset<16>(derp) <<endl;
		return(derp);
	}
}

void printBytes(unsigned char *buffer,int bytes) {
	int bits = 8*bytes;
	for(int i = 0; i<bytes; i++) {
	cout << "  [" << i << "]: ";
		for(int j = 7; j>=0; j--) {
			cout << std::bitset<1>(buffer[i] >> j);
		}
	}
	cout << endl;	
}

int gpio(int pin, bool state) {
	
}
int main() {
	wiringPiSPISetupMode(bmsCHANNEL, bmsRate, bmsMode);
	wiringPiSPISetupMode(adcCHANNEL, adcRate, adcMode);

	for(int i = 0; i<10; i++) {
		cout << endl << "adcBuffer:" << endl;
		wiringPiSPIDataRW(adcCHANNEL, adcBuffer, 2); 
		printBytes(adcBuffer, 2);
		cout << ((adcBuffer[0]<<8)|adcBuffer[1]) << endl;
   		
		usleep(100);

		bmsBuffer[0]=0x00;
		bmsBuffer[1]=0x00;
		bmsBuffer[2]=0b01000100;
		cout << endl << "bmsBuffer:" << endl;
		wiringPiSPIDataRW(bmsCHANNEL, bmsBuffer, 3); 
		printBytes(bmsBuffer, 3);
		cout << ((bmsBuffer[0]<<16)|(bmsBuffer[1]<<8)|bmsBuffer[2]) << endl;
		
		usleep(1000000);
	}
}

