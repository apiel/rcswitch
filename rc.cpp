#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h> // usleep
#include <string.h> // strcmp

using namespace std;

void rx(int pin) {
  RCSwitch mySwitch = RCSwitch();
  pinMode(pin, INPUT);
  mySwitch.enableReceive(pin);

  do{
    usleep(100000); // 0.1sec
  } while (!mySwitch.available());
  
  int value = mySwitch.getReceivedValue();
  if (value == 0) {
    cout << "Unknown encoding" << endl;
  } else {
    cout << "{\"code\":";
    cout << mySwitch.getReceivedValue();
    cout << ",\"bit\":";
    cout << mySwitch.getReceivedBitlength();
    cout << "\"protocol\":";
    cout << mySwitch.getReceivedProtocol();
    cout << "}" << endl;
  }
  mySwitch.resetAvailable();
}

void tx(int pin, int code, int protocol, int bit) {
    RCSwitch mySwitch = RCSwitch();
	mySwitch.enableTransmit(pin);
    mySwitch.setProtocol(protocol);
    mySwitch.send(code, bit);

    cout << "Send code " << code << endl;
}

int main(int argc, char *argv[]) {
  int c;
  int x = 1;
  int protocol = 1;
  int code = 12345;
  int bit = 24;
  int pin = 1;
  opterr = 0;
  
  while ((c = getopt(argc, argv, "hx:p:c:b:i:")) != -1) {
    switch (c) {
      case 'h':
        cout << argv[0] << "-x [rx|tx] -c [code] -b [bit] -p [protocol] -i [gpio]" << endl << endl;
        cout << "rx: receive mode (default)" << endl;
        cout << "tx: transmit mode. This mode can get extra parameters -c [code] -b [bit] -p [protocol]." << endl;
        cout << "code: code to transmit eg.: " << code << endl;
        cout << "bit: length of the code to transmit, default: " << bit << endl;
        cout << "protocol: protocol used to transmit (1, 2 or 3), default: " << protocol << endl;
        cout << "gpio: the pin connected to your transmiter or receiver, default: " << pin << " (for orangePi, 1 is the pin 11, GPIO 17)" << endl << endl;
        
        break;
      case 'x': // rx or tx
        x = strcmp (optarg, "tx");
        break;
      case 'p': // protocol
        protocol = atoi(optarg);
        break;
      case 'c': // code
        code = atoi(optarg);
        break;
      case 'b': // bit
        bit = atoi(optarg);
        break;
      case 'i':
        pin = atoi(optarg);
        break;
      case '?':
        if (optopt == 'x')
          fprintf(stderr, "Option -%c requires an argument: rx to receive or tx to transmit.\n", optopt);
        else if (optopt == 'p' || optopt == 'c' || optopt == 'b' || optopt == 'i')
          fprintf(stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint(optopt))
          fprintf(stderr, "Unknown option -%c.\n", optopt);
        else
          fprintf(stderr, "Unknown option character \\x%x.\n", optopt);
        return 1;
      default:
        abort();
    }
  }
  if (x == 0) {
    tx(pin, code, protocol, bit);
  }
  else {
    rx(pin);
  }
  return 0;
}
