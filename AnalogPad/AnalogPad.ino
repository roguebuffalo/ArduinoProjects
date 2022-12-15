#include "Joystick.h"
// AUTHOR: Me
// PURPOSE: Testing pinout and readings of sliding linear 10K pot
// TESTED ON/WORKS WITH: Leonardo

Joystick_ Joystick( 0x09, JOYSTICK_TYPE_JOYSTICK, //ID + TYPE
                    12, 0, // BUTTON + HAT
                    true, true, false, // x y z axis
                    false, false, false, // rx ry rz
                    false, true, false, // rudder, throttle, accelerator
                    false, false); // brake + steering

int buttons[5] = {0};
int analogAxes[3] = {A0, A1};
const int MAX_NUM_OF_BUTTONS = 5;
const int DIGITAL_INPUT_PIN_START = 2;
void setup() {
  // put your setup code here, to run once:
  pinMode(A3, INPUT); // throttle
  pinMode(A0, INPUT); // X axis
  pinMode(A1, INPUT); // Y axis
  pinMode(2, INPUT_PULLUP); // analog click
  pinMode(3, INPUT_PULLUP); // button 1
  pinMode(4, INPUT_PULLUP); // button 2
  pinMode(5, INPUT_PULLUP); // button 3
  pinMode(6, INPUT_PULLUP); // button 4

  Joystick.setXAxisRange(0, 1023);
  Joystick.setYAxisRange(0, 1023);
  Joystick.setThrottleRange(0, 1023);
  Joystick.begin(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < MAX_NUM_OF_BUTTONS; i++) {
     int currentButtonState = digitalRead(i + DIGITAL_INPUT_PIN_START);

     if(currentButtonState != buttons[i]) {
       Joystick.setButton(i, currentButtonState);
       buttons[i] = currentButtonState;
     }  
  }

  Joystick.setXAxis(analogRead(A0));
  Joystick.setYAxis(analogRead(A1));
  Joystick.setThrottle(analogRead(A3));
  Serial.println(analogRead(A3));
}
