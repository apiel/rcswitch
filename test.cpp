#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h> // usleep

using namespace std;

int main(int argc, char *argv[]) {
    
	RCSwitch mySwitch = RCSwitch();
	//char pathGpioData[128] = "/sys/class/gpio_sw/PA%d/data";
	//setPathGpioData(pathGpioData);
    mySwitch.enableReceive(1);
    
    while(1) {
      //cout << "loop:" << mySwitch.getReceivedValue() << endl; 
      if (mySwitch.available()) {

        int value = mySwitch.getReceivedValue();

        if (value == 0) {
          cout << "Unknown encoding" << endl;
        } else {
          cout << "Received";
          cout << mySwitch.getReceivedValue();
          cout << " / ";
          cout << mySwitch.getReceivedBitlength();
          cout << "bit ";
          cout << "Protocol: ";
          cout << mySwitch.getReceivedProtocol() << endl;
        }

        mySwitch.resetAvailable();
      }
      usleep(100000); // 0.1sec
    }
    cout << "finish!!" << endl;
	return 0;
}
