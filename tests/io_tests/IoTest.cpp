#include "IoTest.h"


/*
 * This test uses BCM 17, turns it on and off five times.
 * Test this with LED.
*/
TEST(IoTest, TestOutput) {
  wiringPiSetup() ;
  pinMode(OUTPUT_PIN, OUTPUT);
  for(int i = 0; i<5; i++){
      static bool state = false;
      digitalWrite(OUTPUT_PIN, state);
      delay(1000);
      state = !state;
  }
}

/*
 * This test uses BCM 4, reads it's value.
 * Test this by pulling this pin to 3.3V.
*/
TEST(IoTest, TestInput) {
    wiringPiSetup();
    pinMode(INPUT_PIN, INPUT);
    EXPECT_TRUE(digitalRead(INPUT_PIN));
}
