#include "DigiKeyboard.h"

unsigned int pos = 0;
unsigned int ticks = 0;
unsigned int antiscreensaver = 0;
bool tick_flag = false;

void setup() {
  // this is generally not necessary but with some older systems it seems to prevent missing the first character after a delay:
  DigiKeyboard.sendKeyStroke(0);
  pinMode(0, INPUT_PULLUP); //Button
  pinMode(1, OUTPUT); //LED
}

void loop() {
  if (digitalRead(0) == LOW) {
    pos = 100;
    digitalWrite(1, LOW);
  }

  if (tick_flag){
    antiscreensaver++;
    if (antiscreensaver >= 3600){
      antiscreensaver = 0;
      DigiKeyboard.sendKeyStroke(85); //NUM_MULTIPLY
    }
    if (pos >0){
      if (((pos >= 70) or (pos%2 == 1)) and pos%10 != 0){
        digitalWrite(1, HIGH);    
      }else{
        digitalWrite(1, LOW);
      }
      switch(pos){
        case 90: 
          DigiKeyboard.sendKeyStroke(86); // NUM_MINUS
          break;
        case 80: 
//          DigiKeyboard.sendKeyStroke(89); // NUM_1
          DigiKeyboard.sendKeyStroke(30); // KEY_1
          break;
        case 70: 
          DigiKeyboard.sendKeyStroke(88); // NUM_ENTER
          break;
        case 1: 
          DigiKeyboard.sendKeyStroke(84); // NUM_SLASH
          break;
      }
      pos--;
    }else{
      digitalWrite(1, LOW);      
    }
    tick_flag = 0;
  }

  delay(5);
  ticks++;
  if (ticks >= 10){
    tick_flag = true;
    ticks = 0;
  } 
}
