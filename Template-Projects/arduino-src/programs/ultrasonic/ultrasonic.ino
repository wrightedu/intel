// This program is untested and may not work.
// If it doesn't, contact jekeltor on Discord (will appear as CSE Dev | Jake in WSU CSE-EE Server).
// You can also email cse-support@wright.edu or hamblin.15@wright.edu

const int trigPin = 12;
const int echoPin = 13;

void setup() {
  // Start serial output
  Serial.begin(9600);

  // Set trigger pin to output
  pinMode(trigPin, OUTPUT);

  // Set echo pin as input
  pinMode(echoPin, INPUT);
}

void loop() {
  // Distance of object from sensor
  float distance;

  // Get distance of object from sensor
  distance = showDistance();

  Serial.println(distance);

  // Print line for pretty console
  Serial.println();
  delay(25);
}

float showDistance() {
  // Get duration and distance
  float duration, distance;

  // Stop sending any trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send trigger
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  // Stop sending any trigger
  digitalWrite(trigPin, LOW);

  // Calculate distance away from sensor
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  delay(25);

  // Return distance
  return distance;
}
