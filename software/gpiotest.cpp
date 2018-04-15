/******************************************************************************
gpiotest.cpp
Raspberry Pi GPIO demo
Byron Jacquot @ SparkFun Electronics>
4/2/2014
https://github.com/sparkfun/Pi_Wedge

A brief demonstration of GPIO features on the Raspberry Pi, to demonstrate 
the SparkFun Pi Wedge breakout board.

Resources:

This example makes use of the Wiring Pi library, which streamlines the inteface
the the I/O pins on the Raspberry Pi, providing an API that is similar to the
Arduino.  You can learn about installing Wiring Pi here:
http://wiringpi.com/download-and-install/

The GPIO API is documented here:
https://projects.drogon.net/raspberry-pi/wiringpi/functions/

WiringPi also installs the very useful command-line utility called 'gpio' 
which allows you to configure and query pin status.  Check it's man page for 
more details.

To build this file, I use the command:
>  g++ gpiotest.cpp -lwiringPi

Then to run it, I have to use sudo, as it creates restricted file resources.
> sudo ./a.out

WiringPi defines its own pin numbers, in a contiguous range, from 0 to 16.  
These numbers account for the V1/V2 hardware differences.  You can alternately 
use the RPi/Broadcom pin numbers.

This test will repurpose the UART pins.  If you're using a terminal on the UART, 
constrain it to pins 0 through 14.  If you're using SSH/telnet, you can include 
pins 15 and 16.

Development environment specifics:
Tested on Raspberry Pi V2 hardware, running Raspbian.
Building with GCC 4.6.3 (Debian 4.6.3-14+rpi1)

This code is beerware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!

Distributed as-is; no warranty is given.
******************************************************************************/

#include <iostream>
#include <errno.h>
#include <wiringPi.h>

using namespace std;

// This will only touch 0 through 14.  15 and 16 are the UART, which we 
// wouldn't want to reconfigure is you're using them for a terminal.
// If you're using SSH, you can run up to 16.
static const int MAX_PIN = 14;

int main()
{
   int result;

   // Init using the wiring Pi numbering scheme ( GPIOs referenced as
   // a contiguous 0 through 16 range).
   //
   // Could alternately call:
   // - wiringPiSetupGpio() to use the native Pi pin numbers
   // - wiringPiSetupSys() to use pre-exported /sys/class/gpio pins.  This
   //                      requires that the pins be pre-exported, but doesn't 
   //                      require root access to run the application.
   result = wiringPiSetup();

   // Result of -1 indicates error
   cout << "Setup result: " << result << endl;

   // set all pins as outputs
   for(int i = 0; i <= MAX_PIN; i++)
   {
      pinMode(i, OUTPUT);

      cout << "init'd pin: " << i << endl;
   }

   // Cycle through the pins, setting one at a time high.
   // Repeat 10 times.
   // This allows us to check them with a meter or oscilloscope.
   for(int i = 0; i < MAX_PIN; i++)
   {
      for(int j = 0; j <= MAX_PIN; j++)
      {
         if( (i % 17) == j)
         {
            cout << "Pin " << j << " set high." <<endl;
            digitalWrite(j, HIGH);
         }
         else
         {
            digitalWrite(j, LOW);
         }
      }

      sleep(1);
   }
}
