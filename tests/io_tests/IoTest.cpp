#include "IoTest.h"

TEST(IoTest, TestOutput) {
  wiringPiSetup() ;
  pinMode(0, OUTPUT);
  for(int i = 0; i<20; i++){
      static bool state = false;
      digitalWrite(0, state);
      delay(1000);
      state = !state;
  }

}
