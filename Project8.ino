
#include <SPI.h>
#include <MFRC522.h>

#define GREEN_LED 3
#define RED_LED 2
#define BUZZER A5
#define speakerPin A5
#define SS_PIN 10
#define RST_PIN 9
#define BLUE_ID "07 B2 17 B3"
#define RED_ID "39 C1 EA B3"
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int length = 28; // the number of notes
char notes[] = "GGAGcB GGAGdc GGxecBA yyecdc";
int beats[] = { 2, 2, 8, 8, 8, 16, 1, 2, 2, 8, 8,8, 16, 1, 2,2,8,8,8,8,16, 1,2,2,8,8,8,16 };
int tempo = 150;
void playTone(int tone, int duration) {
for (long i = 0; i < duration * 1000L; i += tone * 2) {
   digitalWrite(speakerPin, HIGH);
   delayMicroseconds(tone);
   digitalWrite(speakerPin, LOW);
   delayMicroseconds(tone);
}
}
void playNote(char note, int duration) {
char names[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B',           

                 'c', 'd', 'e', 'f', 'g', 'a', 'b',

                 'x', 'y' };

int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014,

                 956,  834,  765,  593,  468,  346,  224,

                 655 , 715 };

int SPEE = 5;
// play the tone corresponding to the note name
for (int i = 0; i < 17; i++) {
   if (names[i] == note) {
    int newduration = duration/SPEE;
     playTone(tones[i], newduration);

   }
}
}
void setup() 
{

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT); //TODO moze nie dzialac

  
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, HIGH);

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  //Serial.println();
  //Serial.print("Message : ");
  content.toUpperCase();
  //niebieski 07 B2 17 B3
  //czerwony 39 C1 EA B3


  if (content.substring(1) == BLUE_ID) //change here the UID of the card/cards that you want to give access
  {
    digitalWrite(GREEN_LED, LOW);
    Serial.println("Authorized access");
    delay(300);  
    noTone(BUZZER); 
    tone(BUZZER,494,500); 
 
    noTone(BUZZER); 
    tone(BUZZER,523,300); 
    delay(200); 
    digitalWrite(7,HIGH); 
    delay(50); 
    digitalWrite(8,HIGH); 
    delay(50); 
    noTone(BUZZER); 

    digitalWrite(GREEN_LED, HIGH);
  }
  else if (content.substring(1) == RED_ID) //change here the UID of the card/cards that you want to give access
  {
    digitalWrite(RED_LED, LOW);
    Serial.println("Authorized access");
    for (int i = 0; i < length; i++) {
   if (notes[i] == ' ') {
     delay(beats[i] * tempo); // rest
   } else {
     playNote(notes[i], beats[i] * tempo);
   }
   // pause between notes
   delay(tempo);
}

    digitalWrite(RED_LED, HIGH);
  }
 else   {
    Serial.println(" Access denied");
    delay(3000);
  }

  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, HIGH);
} 
