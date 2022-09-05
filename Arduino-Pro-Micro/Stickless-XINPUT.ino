#include <Arduino.h>
#include "XInput.h"
#include <Bounce2.h>

/**
#define DDOWN   10
#define DLEFT   16
#define DRIGHT  14
#define DUP     15

#define B_A     2
#define B_B     3
#define B_X     4
#define B_Y     5
#define B_RB    6
#define B_RT    7
#define B_LB    8
#define B_LT    9

#define B_LS    21
#define B_RS    20
#define B_START 19
#define B_SEL   18
**/

#define BOUNCE_INTERVAL 5 //ms

int BUTTON_ARRAY [16] = {
  10, 16, 14, 15, 2, 3, 4, 5, 6, 7, 8, 9, 21, 20, 19, 18
};

enum pad {
  DDOWN   = 0,
  DLEFT,
  DRIGHT,
  DUP,

  B_A,
  B_B,
  B_X,
  B_Y,
  B_RB,
  B_RT,
  B_LB,
  B_LT,

  B_LS,
  B_RS,
  B_START,
  B_SEL
};

Bounce bnPin[16];

void setupPins(){
  for ( int i = 0; i < 16; i++){
    
    bnPin[i] = Bounce();
    
    pinMode(BUTTON_ARRAY[i], INPUT_PULLUP);
    
    bnPin[i].attach(BUTTON_ARRAY[i]);
    bnPin[i].interval(BOUNCE_INTERVAL);
  }
}
bool getV(int x){
  bnPin[x].update();
  return !bnPin[x].read();
}

void setup(){
  setupPins();
  XInput.setAutoSend(false);
  XInput.begin();
}

void loop(){

  XInput.setButton(DPAD_UP,         getV(pad::DUP));
  XInput.setButton(DPAD_DOWN,       getV(pad::DDOWN));
  XInput.setButton(DPAD_LEFT,       getV(pad::DLEFT));
  XInput.setButton(DPAD_RIGHT,      getV(pad::DRIGHT));

  XInput.setButton(BUTTON_A,        getV(pad::B_A));
  XInput.setButton(BUTTON_B,        getV(pad::B_B));
  XInput.setButton(BUTTON_X,        getV(pad::B_X));
  XInput.setButton(BUTTON_Y,        getV(pad::B_Y));
  XInput.setButton(BUTTON_LB,       getV(pad::B_LB));
  XInput.setButton(BUTTON_RB,       getV(pad::B_RB));
  XInput.setButton(TRIGGER_LEFT,    getV(pad::B_LT));
  XInput.setButton(TRIGGER_RIGHT,   getV(pad::B_RT));

  XInput.setButton(BUTTON_L3,       getV(pad::B_LS));
  XInput.setButton(BUTTON_R3,       getV(pad::B_RS));
  XInput.setButton(BUTTON_START,    getV(pad::B_START));
  XInput.setButton(BUTTON_BACK,     getV(pad::B_SEL));

  if( XInput.getButton(DPAD_LEFT) && XInput.getButton(DPAD_RIGHT) ){
    XInput.setButton(DPAD_LEFT,   false);
    XInput.setButton(DPAD_RIGHT,  false);
  };

  if( XInput.getButton(DPAD_DOWN) && XInput.getButton(DPAD_UP) ){
    XInput.setButton(DPAD_DOWN  , false);
    XInput.setButton(DPAD_UP    , true);
  };

  XInput.send();
}
