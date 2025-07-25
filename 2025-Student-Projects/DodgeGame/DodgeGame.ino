#include <LiquidCrystal.h>

int DI = 12;
int RW = 11;
int DB[] = {3, 4, 5, 6, 7, 8, 9, 10};//Use an array to define the pins
int Enable = 2;

int buzz = 13;

//LiquidCrystal(rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7)
LiquidCrystal lcd(DI, RW, Enable, DB[0], DB[1], DB[2], DB[3], DB[4], DB[5], DB[6], DB[7]);

const int joystickX = A0;
const int joystickY = A1;
int playerPosY = 0; //Col 0
int playerPosX = 0; //Row 0
int obstaclePosY = 15;
int obstaclePosX;
int score = 0;
bool gameOver = false;
int turn = 1;

void setup() {
  pinMode(buzz, OUTPUT);//initialize the buzzer pin as an output
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Dodge Game!");
  delay(2000);
  lcd.clear();

  //Menu Screen
   
}

void loop() {
  if (gameOver) return;

  int xVal = analogRead(joystickX);
  int yVal = analogRead(joystickY);

  if (xVal < 400 && playerPosX == 1) {
    playerPosX--;
    delay(150); // debounce
  } else if (xVal > 600 && playerPosX == 0) {
    playerPosX++;
    delay(150);
  }
  if (yVal < 400 && playerPosY > 0) {
    playerPosY--;
    delay(150); 
  } else if (yVal > 600 && playerPosY < 15) {
    playerPosY++;
    delay(150); 
  }

  // Update obstacle and player
  lcd.clear();
  obstaclePosX = random(2);
  lcd.setCursor(obstaclePosY, obstaclePosX);
  lcd.print("|");  // obstacle
  lcd.setCursor(playerPosY, playerPosX);
  lcd.print(">");  // player

  // Check for collision
  if (obstaclePosY == playerPosY && obstaclePosX == playerPosX) {
    gameOver = true;
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("GAME OVER");
    lcd.setCursor(4, 1);
    lcd.print("Score: ");
    lcd.print(score);
    tone(buzz, 660, 150);  // E5
    delay(200);
    tone(buzz, 440, 150);  // A4
    delay(200);
    tone(buzz, 220, 300);  // A3
    delay(350);
    noTone(buzz);
    return;
  } else if (obstaclePosY == playerPosY && obstaclePosX != playerPosX || obstaclePosY == playerPosY-1 && obstaclePosX != playerPosX || obstaclePosY == playerPosY-1 && obstaclePosX == playerPosX){
      if (score < turn){
        tone(buzz, 880, 100);
        delay(150);
        tone(buzz, 1320, 100);
        delay(150);
        score++;
      }
  }

  obstaclePosY--;
  if (obstaclePosY == 0) {
    obstaclePosY = 15;
    turn++;
  }

  delay(500);  // game speed
}
