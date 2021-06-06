#include "IoTest.h"

/*
 * This test uses BCM 13 and outputs PWM signal.
 * Use diode for this test. It should be dim.
*/
TEST(IoTest, TestPwm) {
    wiringPiSetup() ;
    pinMode(PWM_PIN, PWM_OUTPUT);
    pwmWrite(PWM_PIN, 256);
    delay(3000);
}

TEST(IoTest, TurnOffPwm) {
    wiringPiSetup() ;
    pinMode(PWM_PIN, INPUT);
}
