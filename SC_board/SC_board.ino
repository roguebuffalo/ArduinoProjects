// Program used to test the USB Joystick library when used as 
// a Flight Controller on the Arduino Leonardo or Arduino 
// Micro.
//
// Matthew Heironimus
// 2016-05-29 - Original Version
//------------------------------------------------------------

#include "Joystick.h"

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_JOYSTICK, 32, 0,
  true, true, false, false, false, false,
  false, false, false, false, false);

// Set to true to test "Auto Send" mode or false to test "Manual Send" mode.
//const bool testAutoSendMode = true;
const bool testAutoSendMode = true;

//dedicates the first num_of_toggles * 2 buttons to spam that state
const int NUM_OF_TOGGLES = 4;
// start digital pin inputs on pin 2
const int DIGITAL_INPUT_PIN_START = 2;

static int buttonStates[32] = {-1};

static bool initializeToggles = true;

void InitializeToggles(int toggles){
  for(int i = 0; i < NUM_OF_TOGGLES; i++){
    Joystick.setButton((i*2), 1);
  }
}

void VirtualToggle(int off, int on, int turnOn){
  Joystick.setButton(off, !turnOn);
  Joystick.setButton(on, turnOn);
}

void HandleToggleSwitchesAsButtons(){
  for(int i = 0; i < NUM_OF_TOGGLES; i++) {
    int currentToggleState = !digitalRead(i + DIGITAL_INPUT_PIN_START);
    
    //if read state does not match last state, toggle
    if(currentToggleState != buttonStates[i]) {
      switch(i) {
        case 0: // toggle 1
          VirtualToggle(0, 1, currentToggleState);
          break;
        case 1: // toggle 2
          VirtualToggle(2,3, currentToggleState);
          break;
        case 2:
          VirtualToggle(4,5, currentToggleState);
          break;
        case 3:
          VirtualToggle(6,7, currentToggleState);
          break;
        default:
          break;
      }
      buttonStates[i] = currentToggleState; 
    }
  }
}

void setup() {
  //init toggle pins
  pinMode(2, INPUT_PULLUP); // toggle 1: low = button 0; high = button 1
  pinMode(3, INPUT_PULLUP); // toggle 2: low = button 2; high = button 3
  pinMode(4, INPUT_PULLUP); // toggle 3: low = button 4; high = button 5
  pinMode(5, INPUT_PULLUP); // toggle 4: low = button 6; high = button 7

  Joystick.begin(false);
  Joystick.setXAxisRange(-256, 256);
  Joystick.setYAxisRange(-256, 256);

  InitializeToggles(NUM_OF_TOGGLES);

}

void loop() {
  HandleToggleSwitchesAsButtons();
  Joystick.sendState();
  delay(10);
}