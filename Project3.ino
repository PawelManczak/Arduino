#include <LiquidCrystal.h>

LiquidCrystal LCD(12, 11, 5, 4, 3, 2);
byte customChar[] = {1, 2, 3, 4, 5, 6, 7, 8};
byte customChar2[] = {5, 6, 7, 8};
// the setup function runs once when you press reset or power the board
int x = 0;
int y = 0;
bool stoper = true;
int milis = 0;
int sec = 0;
int mStopS = 0;
int mStopM = 0;

int mTime = 0;
int mStop = 0;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

   LCD.begin(16, 2);
   //LCD.print("hello");
  //LCD.clear();
  Serial.begin(9600);


  LCD.createChar(4, 0);
  LCD.createChar(5, customChar2);

    LCD.setCursor(x, y);
    LCD.write(4);
}

// the loop function runs over and over again forever
void loop() {

delay(100);
  char c = Serial.read();

  if(c == 'd'){
    x++;
    
  }
  else if( c == 'a' && x){
    x--;
  }
  else if (c == 'w'){
    y++;
  }
  else if(c=='s'){
    y--;
  }
  
    LCD.setCursor(x, y);
    LCD.write(4);

    if(c == 'r'){
      mTime = millis();
      mStop = millis();
      mStopM= millis()%100;
      mStopS=millis()/1000;
      stoper = !stoper;
      milis=0;
      
    
      
    }
    else if(stoper){
      sec = millis()/1000;
      milis = millis()%100;
      mTime = millis();
      sec -=mStopS;
      //milis -= mStopM;
      LCD.clear();
        LCD.setCursor(0,1);
      LCD.print((mTime-mStop)/1000);
      LCD.setCursor(4,1);
      LCD.print((mTime-mStop)%100);
    }
  
  c = 'x';
}
