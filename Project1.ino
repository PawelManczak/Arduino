
int btn1, btn2, btn3, btn4, btn5;
int mode = 0; //rgb diode mode
void setup() {

  Serial.begin(1000);
  pinMode(12, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(11, OUTPUT);

  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

}

// the loop function runs over and over again forever
void loop() {


  btn1 = digitalRead(1);
  delay(20);
  if (btn1 == HIGH) {
    digitalWrite(12, HIGH);
    // turn the LED off by making the voltage LOW
  } else {
    digitalWrite(12, LOW);
  }
  btn2 = digitalRead(2);
  delay(20);
  if (btn2 == HIGH) {
    digitalWrite(11, HIGH);
    // turn the LED off by making the voltage LOW
  } else {
    digitalWrite(11, LOW);
  }
  btn3 = digitalRead(3);
  delay(20);
  if (btn3 == HIGH) {
    digitalWrite(10, HIGH);

  } else {
    digitalWrite(10, LOW);
  }
  btn4 = digitalRead(4);
  delay(20);
  if (btn4 == HIGH) {

    digitalWrite(9, HIGH);
  } else {
    digitalWrite(9, LOW);
  }


  btn5 = digitalRead(5);
  delay(20);
  if (btn5 == LOW) {
    mode++;

    if (mode == 8) {
      mode = 0;
    }
    if (mode == 0) {
      digitalWrite(8, LOW);
      digitalWrite(7, LOW);
      digitalWrite(6, LOW);
    } else if (mode == 1) {
      digitalWrite(8, HIGH);
      digitalWrite(7, LOW);
      digitalWrite(6, LOW);
    }
    else if (mode == 2) {
      digitalWrite(8, LOW);
      digitalWrite(7, HIGH);
      digitalWrite(6, LOW);
    }
    else if (mode == 3) {
      digitalWrite(8, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(6, LOW);
    }
    else if (mode == 4) {
      digitalWrite(8, LOW);
      digitalWrite(7, LOW);
      digitalWrite(6, HIGH);
    }
    else if (mode == 5) {
      digitalWrite(8, HIGH);
      digitalWrite(7, LOW);
      digitalWrite(6, HIGH);
    }
    else if (mode == 6) {
      digitalWrite(8, LOW);
      digitalWrite(7, HIGH);
      digitalWrite(6, HIGH);
    }
    else if (mode == 7) {
      digitalWrite(8, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(6, HIGH);
    }
  }




  digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
  digitalWrite(11, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(11, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
  digitalWrite(10, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(10, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
  digitalWrite(9, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(9, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);

}
