float duration, distance;

// Pins
const int trig = 11;
const int echo = 12;
const int data = 5; 
const int latch = 6;
const int clock = 7;

const int a = 8, 
          b = 7, 
          c = 6,
          d = 5,
          e = 4,
          f = 3,
          g = 2,
          dp = 9;

const int pins[] = {a, b, c, d, e, f, g, dp};
// const int pins[] = {8, 7, 6, 5, 4, 3, 2, 9};
byte leds = 0;


/*
 * * a * *
*         *
f         b
*         *
 * * g * *
*         *
e         c
*         *
 * * d * *  dp
*/

// Format for the map
// 0b(dp)gfedcba
const byte digitMap[11] = {
  0b00111111, // 0 -> abcdef
  0b00000110, // 1 -> bc
  0b01011011, // 2 -> abged
  0b01001111, // 3 -> abgcd
  0b01100110, // 4 -> fgcb
  0b01101101, // 5 -> afgcd
  0b01111101, // 6 -> afgced
  0b00000111, // 7 -> abc
  0b01111111, // 8 -> all
  0b01101111, // 9 -> abfgcd
  0b00000000  // -> erase
};

void updateShiftRegister() {
  digitalWrite(latch, LOW);
  shiftOut(data, clock, MSBFIRST, leds);
  digitalWrite(latch, HIGH);
}

void displayDigit(int digit) {
  leds = digitMap[digit];
  updateShiftRegister();
  // for (int i = 0; i < 7; i++) {
  //   /*
  //     * We are comparing the digit within the map
  //     * using the bitwise AND operator
  //     * to check if the corresponding segment should be on or off.
  //     * by shifting a 1 bit (00000001) to the left i times
  //     */
  //   bool on = digitMap[digit] & (1 << i);

  //   /* 
  //     * And then using the boolean value we can do a small logic of
  //     * if on is true, set the pin HIGH, otherwise LOW
  //     */
  //   digitalWrite(pins[i], on ? HIGH : LOW);
  // }
}


void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(latch, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(clock, OUTPUT);

  Serial.begin(9600);
}


void loop() {
  leds = 0;
  updateShiftRegister(); // clear
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);

  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);

  distance = (duration * 0.00112533) / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance >= 0 && distance <= 9)
    displayDigit(round(distance));
  else  
    displayDigit(10);

  delay(500);
}


