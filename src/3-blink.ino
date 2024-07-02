//global variables for which arduino pins control which LED
int red = 13;
// fix these then uncomment them
//int yellow = ??;
//int green = ??;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
}

// the loop function runs over and over again forever
// try also blinking the yellow and green LED's
void loop() {
  digitalWrite(red, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(red, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}

// Description: Flash an LED on and off for a specified amoutn of time (ms)
// inputs: 
//    pin_num == integer value for what pin the LED is on
//    delay_amount == integer value, number of milliseconds to flash the light on and off for 
// output: visiable light from the LED for a specified amoutn of time
// usage: flash(13, 1000);
void flash(int pin_number, int delay_amount) {
    digitalWrite(pin_num, 1);
    delay(delay_amount);
    digitalWrite(pin_num, 0);
    delay(delay_amount);
}