#include "pitches.h"
#include <Keypad.h>

// Global variables to specify pin locations 
int sr_data = 7;
int sr_clock = 5;
int sr_latch = 6;
int rgb_r = 8;
int rgb_g = 9;
int rgb_b = 10;
int speaker = 11;

// 7 segment setup data
byte data;
byte seven_segment[10];

//keypad setup data
const byte ROWS = 4; 
const byte COLS = 4; 
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {4, 3, 1, 0}; 
byte colPins[COLS] = {19, 18, 17, 16}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

// initialize needed pins as output
void setup() {

  //setup rgb led and test with rgb blink
  pinMode(rgb_r, OUTPUT);
  pinMode(rgb_g, OUTPUT);
  pinMode(rgb_b, OUTPUT);
  
  digitalWrite(rgb_r, 1);
  delay(500);
  digitalWrite(rgb_r, 0);
  digitalWrite(rgb_g, 1);
  delay(500);  
  digitalWrite(rgb_g, 0);
  digitalWrite(rgb_b, 1);
  delay(500);
  digitalWrite(rgb_b, 0);


  //setup speaker and test with beep
  pinMode(speaker, OUTPUT);
  tone(speaker, NOTE_C4, 4);

  //setup 7-segment
  pinMode(sr_latch, OUTPUT);
  pinMode(sr_clock, OUTPUT);
  pinMode(sr_data, OUTPUT);
  Serial.begin(9600);

  blinkAll_2Bytes(2,500);


  //Binary notation as comment
  seven_segment[0] = 0xFF; //0b11111111
  seven_segment[1] = 0xFE; //0b11111110
  seven_segment[2] = 0xFC; //0b11111100
  seven_segment[3] = 0xF8; //0b11111000
  seven_segment[4] = 0xF0; //0b11110000
  seven_segment[5] = 0xE0; //0b11100000
  seven_segment[6] = 0xC0; //0b11000000
  seven_segment[7] = 0x80; //0b10000000
  seven_segment[8] = 0x00; //0b00000000
  seven_segment[9] = 0xE0; //0b11100000

}

// the loop function runs over and over again forever
void loop() {
//basic keypad functionality
  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
  }
// dont do anything yet...
}

// Description: clears the 7 segment display of all current lit LED's
// inputs: none
// output: blank 7 segment display (visible)
// usage: clear_the_display();
void shiftOut(int sr_data, int sr_clock, byte myDataOut) {

  // This shifts 8 bits out MSB first,
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(sr_data, 0);
  digitalWrite(sr_clock, 0);

  //for each bit in the byte myDataOut&#xFFFD;
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights.
  for (i=7; i>=0; i--)  {
    digitalWrite(sr_clock, 0);

    //if the value passed to myDataOut and a bitmask result
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }

    else {
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    //register shifts bits on upstroke of clock pin
    digitalWrite(sr_data, pinState);
    digitalWrite(sr_clock, 1);
    digitalWrite(sr_data, 0);
  }

  digitalWrite(sr_clock, 0);
}


//blinks the whole register based on the number of times you want to
//blink "n" and the pause between them "d"
//starts with a moment of darkness to make sure the first blink
//has its full visual effect.

void blinkAll_2Bytes(int n, int d) {
  digitalWrite(sr_latch, 0);
  shiftOut(sr_data, sr_clock, 0);
  shiftOut(sr_data, sr_clock, 0);
  digitalWrite(sr_latch, 1);
  delay(200);

  for (int x = 0; x < n; x++) {
    digitalWrite(sr_latch, 0);
    shiftOut(sr_data, sr_clock, 255);
    shiftOut(sr_data, sr_clock, 255);
    digitalWrite(sr_latch, 1);
    delay(d);
    digitalWrite(sr_latch, 0);
    shiftOut(sr_data, sr_clock, 0);
    shiftOut(sr_data, sr_clock, 0);
    digitalWrite(sr_latch, 1);
    delay(d);
  }
}

