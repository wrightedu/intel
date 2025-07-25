/**
 *
 *  BANGER BOX
 *
 *  Box has buttons, buttons when pressed plays sound
 *  sounds includes songs, Ricky Roll, TMNT, Doom, Crab Rave, and possibly more, 
 *  idk, we keep wanting to add more songs
 *  
 *
 *  Authors: 
 *    Emily Creed
 *    Nick Pontious
 *    MG Davis
 *  
 *  Contributors:
 *    Nathaniel Ezzie
 *    Corporal Kelley Billy
 *    
 *
 */
// RGB Pin Layout
#define red 6
#define blue 5
#define green 3

#include "Doom.h"
#include "CrabRave.h"
#include "LavaChicken.h"
#include "RickRoll.h"

/**
  * Pin Layouts for buttons
  * NOTE: Change pins according to pinouts
 */
//buzzer is in 11
int buttona = 13;
int buttonb = 10;
int buttonc = 7;
int buttond = 2;

// Lava = 5282
// Rick = 7425
// Doom = beef
// Crab = 2722

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes

void setup() {
  // pin setup
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(buttona, INPUT_PULLUP);
  pinMode(buttonb, INPUT_PULLUP);
  pinMode(buttonc, INPUT_PULLUP);
  pinMode(buttond, INPUT_PULLUP);

}

void loop() {

  int buttons[] = {digitalRead(buttona), digitalRead(buttonb), digitalRead(buttonc), digitalRead(buttond)};
  short pressed = -1;

  if (digitalRead(buttona) == LOW || digitalRead(buttonb) == LOW || digitalRead(buttonc) == LOW || digitalRead(buttond) == LOW) {
    if (digitalRead(buttona) == LOW) crabRave();
    if (digitalRead(buttonb) == LOW) rickRoll();
    if (digitalRead(buttonc) == LOW) lavaChicken();
    if (digitalRead(buttond) == LOW) doom();
  }
}