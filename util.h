typedef void (*voidFuncPtr)(void);

void delayMicroseconds(unsigned int howLong);
void digitalWrite(int pin, int value);
void pinMode(int pin, int mode);
void attachInterrupt(int pin, voidFuncPtr handler, int mode);
void detachInterrupt(int pin);
unsigned long micros(void);