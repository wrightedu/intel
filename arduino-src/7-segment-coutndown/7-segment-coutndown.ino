// Global variables to specify pin locations that correspond to the indicated 7-segment 
// display segment
int a = 3;
int b = 4;
int c = 5;
int d = 6;
int e = 7;
int f = 8;
int g = 9;

// initialize needed pins as output
void setup() {
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
}

void chase_tail(){
  delay(100);
  display(1,0,0,0,0,0,0);
  delay(100);
  display(1,1,0,0,0,0,0);
  delay(100);
  display(1,1,1,0,0,0,0);
  delay(100);
  display(0,1,1,0,0,0,0);
  delay(100);
  display(0,1,1,1,0,0,0);
  delay(100);
  display(0,0,1,1,0,0,0);
  delay(100);
  display(0,0,1,1,1,0,0);
  delay(100);
  display(0,0,0,1,1,0,0);
  delay(100);
  display(0,0,0,1,1,1,0);
  delay(100);
  display(0,0,0,0,1,1,0);
  delay(100);
  display(1,0,0,0,0,1,0);
  delay(100);
}

// the loop function runs over and over again forever
void countdown() {
  
  //display a 9
  display(1,1,1,0,0,1,1);
  delay(500);
  display(1,1,1,1,1,1,1);    
  delay(500);
  display(1,1,1,0,0,0,0);     
  delay(500);
  display(1,0,1,1,1,1,1);
  delay(500);
  display(1,0,1,1,0,1,1);   
  delay(500);
  display(0,1,1,0,0,1,1);
  delay(1000);
  display(1,1,1,1,0,0,1);
  delay(500);
  display(1,1,0,1,1,0,1);
  delay(500);
  display(0,1,1,0,0,0,0);
  delay(500);
  display(1,1,1,1,1,1,0);
  delay(500);
}

// Description: clears the 7 segment display of all current lit LED's
// inputs: none
// output: blank 7 segment display (visible)
// usage: clear_the_display();
void clear_the_display() {
   digitalWrite(a,0); 
   digitalWrite(b,0); 
   digitalWrite(c,0); 
   digitalWrite(d,0); 
   digitalWrite(e,0); 
   digitalWrite(f,0);
   digitalWrite(g,0);
}

// Description: Sets the on/off position of the 7 segments of the 7-segment LED 
//              (no decimal point functionality yet...)
// inputs: 0 or 1 integer values for the a through g LEDs
// output: visiable light from the on (LED state = 1) 7 segment display LED's
// usage: display(1,1,1,1,1,1,0);
void display(int astate, int bstate, int cstate, int dstate, int estate, int fstate, int gstate) {
  digitalWrite(a,astate); 
  digitalWrite(b,bstate); 
  digitalWrite(c,cstate); 
  digitalWrite(d,dstate); 
  digitalWrite(e,estate); 
  digitalWrite(f,fstate);
  digitalWrite(g,gstate);
}

void loop(){
  countdown();
  chase_tail();
  chase_tail();
  chase_tail();

}
