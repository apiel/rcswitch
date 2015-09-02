/*
 Usage: ./send <systemCode> <unitCode> <command>
 Command is 0 for OFF and 1 for ON
 */

#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    
	RCSwitch mySwitch = RCSwitch();
    mySwitch.enableReceive(1);
    
    while(1) {
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
