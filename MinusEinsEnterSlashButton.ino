#include "DigiKeyboard.h"

unsigned int pos = 0;
unsigned int ticks = 0;
unsigned int antiscreensaver = 0;
uint16_t rst = 0;
bool tick_flag = false;

void setup(){
  // this is generally not necessary but with some older systems it seems to prevent missing the first character after a delay:
  DigiKeyboard.sendKeyStroke(0);
  pinMode(0, INPUT_PULLUP); //button
  pinMode(1, OUTPUT); //LED
  pinMode(2, OUTPUT); //RESET  
}

void loop(){
  if (digitalRead(0) == LOW){
    switch (rst){
      case 0 ... 99:
        pos = 100;
        digitalWrite(1, LOW);
        break;
      case 100:
        pos = 0;
        break;
      case 300:
        digitalWrite(1, HIGH);
        delay(50);
        digitalWrite(2, HIGH);
        delay(3000);
        digitalWrite(2, LOW);
    }
    rst++;
  }else{
    rst = 0;
  }
  

  if (tick_flag){
    antiscreensaver++;
    if (antiscreensaver >= 3600){
      antiscreensaver = 0;
      DigiKeyboard.sendKeyStroke(85); //NUM_MULTIPLY
    }
    
    if (pos >0){
      if ((pos >= 50) or (pos%2 == 1)){
        digitalWrite(1, HIGH);    
      }else{
        digitalWrite(1, LOW);
      }
      switch(pos){
        case 98:
          DigiKeyboard.sendKeyStroke(86); // NUM_MINUS
          break; 
        case 95:
          DigiKeyboard.sendKeyStroke(86); // NUM_MINUS
          break;
        case 75: 
//          DigiKeyboard.sendKeyStroke(89); // NUM_1
          DigiKeyboard.sendKeyStroke(30); // KEY_1
          break;
        case 60: 
          DigiKeyboard.sendKeyStroke(88); // NUM_ENTER
          break;
        case 1: 
          DigiKeyboard.sendKeyStroke(84); // NUM_SLASH
          break;
      }
      pos--;
    }else{
      digitalWrite(1, LOW);
      if (antiscreensaver % 200 == 1){
          DigiKeyboard.sendKeyStroke(0);        
      }
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
