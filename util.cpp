#include "util.h"

#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <fstream> // readfile
#include <string> // readfile
#include <iostream>
#include <thread>  
//#include <unistd.h> // usleep
//#include <pthread.h>

using namespace std;

bool loopInterrupt = false;

void delayMicrosecondsHard (unsigned int howLong)
{
  struct timeval tNow, tLong, tEnd ;

  gettimeofday (&tNow, NULL) ;
  tLong.tv_sec  = howLong / 1000000 ;
  tLong.tv_usec = howLong % 1000000 ;
  timeradd (&tNow, &tLong, &tEnd) ;

  while (timercmp (&tNow, &tEnd, <))
    gettimeofday (&tNow, NULL) ;
}

void delayMicroseconds (unsigned int howLong)
{
  struct timespec sleeper ;

  /**/ if (howLong ==   0)
    return ;
  else if (howLong  < 100)
    delayMicrosecondsHard (howLong) ;
  else
  {
    sleeper.tv_sec  = 0 ;
    sleeper.tv_nsec = (long)(howLong * 1000) ;
    nanosleep (&sleeper, NULL) ;
  }
}

void pinMode(int pin, int mode)
{

}

void digitalWrite(int pin, int value)
{
  
}

int digitalRead(int pin) // pin not used
{
  string line;
  ifstream myfile ("/sys/class/gpio_sw/PA1/data");
  //ifstream myfile ("test");
  if (myfile.is_open())
  {
    getline (myfile,line);
    myfile.close();
  }

  return atoi(line.c_str());
}

//void *tAttachInterrupt(void* /*voidFuncPtr handler*/)
void tAttachInterrupt(voidFuncPtr handler)
{
  int val2 = 0;
  int val = digitalRead(0);
  cout << "start loop" << endl;
  loopInterrupt = true;
  while(loopInterrupt) {
    val2 = digitalRead(0);
    if (val != val2) {
      //cout << "change" << endl;
      val = val2;
      handler();
    }
    //usleep(1);
  }
}

// to trigger the interrupt whenever the pin changes value
void attachInterrupt(int pin, voidFuncPtr handler, int mode)
{
  thread tAttInt (tAttachInterrupt, handler);
  tAttInt.detach();
  //pthread_t thread;
  //pthread_create( &thread, NULL, tAttachInterrupt, NULL);
  /////tAttachInterrupt();
  cout << "end attachInt" << endl;
}

// if implement attach Interrupt with thread, stop attachInterrupt
void detachInterrupt(int pin)
{
  loopInterrupt = false;
}

unsigned long micros(void)
{
    struct timeval t;
    long micros;
    gettimeofday(&t, NULL);
    micros = t.tv_sec * 1000000L + t.tv_usec;
    
    return micros; // should be the time in microsecond
}

void mylog() 
{
cout << "yo" << endl;
}
