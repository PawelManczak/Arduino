#include <LiquidCrystal.h>
#include <TimerOne.h>
LiquidCrystal lcd(12, 11, 7, 6, 5, 4 );
const int analogInPin = A5;
float voltage;
bool activeManual = true;
int buttonState;

void measureVoltage() {
  voltage = analogRead(analogInPin) * (5.0 / 1023.0); \
  delay(100);
  progres(round(voltage));
}


void displayVoltage() {
  lcd.setCursor(0, 0);
  lcd.print(voltage, 2);
  lcd.print(" V");
}
void progres(int value) {

  lcd.setCursor(0, 1);
  for (int i = 0; i < value; i++) {
    lcd.setCursor(i, 1);
    lcd.print("X");
  }
  for (int i = value; i < 5; i++) {
    lcd.setCursor(i, 1);
    lcd.print(" ");
  }
}

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);

  pinMode(8, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);

  if (activeManual) {
    attachInterrupt(digitalPinToInterrupt(2), [] {
      measureVoltage();
      displayVoltage();
      lcd.print(" MAN");
    }, RISING);
  } else {
    Timer1.initialize(500000);
    Timer1.attachInterrupt([] () {
      measureVoltage();
      displayVoltage();
      lcd.print(" AUTO");
    });
  }
}

void switchMode() {
  activeManual = !activeManual;
  Serial.print ("hello world");
}

void loop() {
  int buttonState = digitalRead(8);
  delay(50);
  if (buttonState == LOW) {
    switchMode();
    delay(100);
  }

  if (activeManual) {
    measureVoltage();
    displayVoltage();
    lcd.print(" AUTO");
  }


}
