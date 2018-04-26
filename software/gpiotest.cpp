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

int main() {
  	
	wiringPiSetup ();
	pinMode (21, OUTPUT);
	
	while(1) {
		digitalWrite(21, HIGH); delay(100);
		digitalWrite(21, LOW); delay(100);
	}

}
