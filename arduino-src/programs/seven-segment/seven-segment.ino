#include "Keypad.h"

// Shift register pins
int latchPin = 6;
int clockPin = 5;
int dataPin = 7;

// Keypad information
String codeInput = "0000";
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1',  '2',  '3', 'A'},
  {'4',  '5',  '6', 'B'},
  {'7',  '8',  '9', 'C'},
  {'F', '0', 'E', 'D'}
};

byte rowPins[ROWS] = {A5, A4, A3, A2};
byte colPins[COLS] = {4, 3, 1, 0};

// Keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Seven segment display converted numbers (converts integer to hexadecimal)
const int sevenSegmentNumbers[18] = {
  0b11111100,
  0b01100000,
  0b11011010,
  0b11110010,
  0b01100110,
  0b10110110,
  0b10111110,
  0b11100000,
  0b11111110,
  0b11100110,
  0b11101110,
  0b00111110,
  0b10011100,
  0b01111010,
  0b10011110,
  0b10001110,
  0b00000001,
  0b01010100,
};

void setup() {
  // Start serial output
  Serial.begin(9600);

  // Set shift register pins as output
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);

  // Write blank to display
  writeToDisplay(16);
}

void loop() {
  // Get key pushed this loop
  char key = keypad.getKey();

  // If a key was pushed
  if(key != NO_KEY) {
    // Update easter egg
    codeInput = codeInput.substring(1, 4);
    codeInput += key;

    if(codeInput == "BEEF") {
      writeToDisplay(17);
    }
    else if(codeInput == "0000") {
      writeToDisplay(16);
    }
    else {
      int num = hexCharToInt(key);

      // Write number to display
      writeToDisplay(num);
    }
  }
}

void writeToDisplay(int number) {
  // Set latch pin to 0
  digitalWrite(latchPin, 0);

  // Send data out
  shiftOut(dataPin, clockPin, bitSwitch(sevenSegmentNumbers[number]));

  // Set latch pin to 1
  digitalWrite(latchPin, 1);
}

int bitSwitch(int original) {
  // Extract individual bits
  int D = (original >> 4) & 0x01;  // Bit 4
  int E = (original >> 3) & 0x01;  // Bit 5
  int A = (original >> 7) & 0x01;  // Bit 1
  int F = (original >> 2) & 0x01;  // Bit 6
  int G = (original >> 1) & 0x01;  // Bit 7
  int C = (original >> 5) & 0x01;  // Bit 3
  int DP = (original) & 0x01;  // Bit 8
  int B = (original >> 6) & 0x01; // Bit 2

  // Put bits back in order via bitwise shift
  int result = (D << 7) | (E << 6) | (A << 5) | (F << 4) |
                          (G << 3) | (C << 2) | (DP << 1) | (B << 0);

  return result;
}

void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // Create state variables
  int i = 0;
  int pinState;

  // Set pin modes
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  // Write 0 to data and clock
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  // Loop through eight times
  for(i = 0; i < 8; i++)  {
    // Set clock to 0
    digitalWrite(myClockPin, 0);

    // Set pin state
    if (myDataOut & (1<<i) ) {
      pinState = 1;
    }

    else {
      pinState = 0;
    }Combine the bits to form the new value

    // Set data bit output
    digitalWrite(myDataPin, pinState);

    // Send clock high
    digitalWrite(myClockPin, 1);

    // Set data pin to 0
    digitalWrite(myDataPin, 0);
  }

  // Send clock low
  digitalWrite(myClockPin, 0);
}

// Convert character to integer equivalent
int hexCharToInt(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    } else if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    } else {
        return -1;
    }
}