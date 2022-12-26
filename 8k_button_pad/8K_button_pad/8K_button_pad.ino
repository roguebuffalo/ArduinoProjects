#include <Keyboard.h>
// AUTHOR: Me
// PURPOSE: Testing pinout and readings of sliding linear 10K pot
// TESTED ON/WORKS WITH: Leonardo


const int MAX_NUM_OF_BUTTONS = 8;
const long DEBOUNCE_TIME = 5;
int buttonPins[MAX_NUM_OF_BUTTONS] = {10, 16, 14, 15, 6, 7, 8, 9};
char buttonToKeyMap[MAX_NUM_OF_BUTTONS] = { ';', 'l', 'k', 'j', 'f', 'd', 's', 'a'};
long lastButtonDebounceTime[MAX_NUM_OF_BUTTONS] = { 0 };
int buttonValues[MAX_NUM_OF_BUTTONS] = {0};
void setup() {
  // put your setup code here, to run once:
  pinMode(10, INPUT_PULLUP); //R4
  pinMode(16, INPUT_PULLUP); //R3
  pinMode(14, INPUT_PULLUP); //R2
  pinMode(15, INPUT_PULLUP); //R1

  pinMode(6, INPUT_PULLUP); //L4
  pinMode(7, INPUT_PULLUP); //L3
  pinMode(8, INPUT_PULLUP); //L2
  pinMode(9, INPUT_PULLUP); //L1
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i < MAX_NUM_OF_BUTTONS; i++) {
     int currentButtonState = !digitalRead(buttonPins[i]);


     if((millis() - lastButtonDebounceTime[i] > DEBOUNCE_TIME) && (currentButtonState != buttonValues[i])) {  
       lastButtonDebounceTime[i] = millis();
       if(currentButtonState) {
         Keyboard.press(buttonToKeyMap[i]);
       } 
       else {
         Keyboard.release(buttonToKeyMap[i]);
       }
      
       buttonValues[i] = currentButtonState;
       
     }
  }
}

