/*------------------------ 
Pomodoro Timer con Arduino
author: gaba@totel.it
thx BOCS APS
-----------------------*/

#include "SevSegShift.h"
#include "pitches.h"

#define SHIFT_PIN_DS   13
#define SHIFT_PIN_STCP 12
#define SHIFT_PIN_SHCP 11

SevSegShift sevseg(SHIFT_PIN_DS, SHIFT_PIN_SHCP, SHIFT_PIN_STCP);

//Condizioni
const String workMode   = "counter == 0 || counter == 2 || counter == 4 || counter == 6";
const String shortBreak = "counter == 1 || counter == 3 || counter == 5 || counter == 7";
const String longBreak  = "counter == 8";

//Minuti per ogni modalità
const float mode[] = {25, 5, 10};

int melody[] = {NOTE_C5, NOTE_E5, NOTE_G5, NOTE_B6, NOTE_D7, NOTE_FS7, NOTE_A7, NOTE_CS8};
int noteDurations[] = {32, 32, 32, 32, 32, 32, 32, 32};

int counter = 0;
const int buttonPin = 2;
const int buzzPin = 3;
bool buzzerFlag = false;

unsigned long currentMillis = 0;
unsigned long prevMillis = 0;

void reset() { 
  buzzerFlag = false;
  asm volatile ("jmp 0x7800");
}

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(buzzPin, OUTPUT);
  byte numDigits = 4;
  byte digitPins[] = {8+2, 8+5, 8+6, 2};
  byte segmentPins[] = {8+3, 8+7, 4, 6, 7, 8+4, 3,  5};
  bool resistorsOnSegments = false;
  byte hardwareConfig = COMMON_CATHODE;
  bool updateWithDelays = false;
  bool leadingZeros = true;
  bool disableDecPoint = true;

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(90);
}

void buzz(){
  if(buzzerFlag == false){
    for (int thisNote = 0; thisNote < 8; thisNote++) {
      int noteDuration = 1000 / noteDurations[thisNote];
      tone(buzzPin, melody[thisNote]+10, noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(8);
    }
    buzzerFlag = true;
  }
}

long minute = 60000; //millisecondi in un minuto
long second =  1000; //millisecondi in un secondo

void countdown(float m){
   currentMillis = (millis() - prevMillis);   //da quanto tempo l'Arduino è acceso (in ms)
   long work = minute * m;                    //numero di minuti in millisecondi
   long timeNow = work - currentMillis;       //sottrai timer al tempo corrente
   int minutes = timeNow / minute;            //converti in minuti
   int seconds = (timeNow % minute) / second; //converti in secondi
   
   minutes = (minutes * 100) + seconds;       //concatena minuti e secondi
   sevseg.setNumber(minutes);                 //setta valore sul display
   sevseg.refreshDisplay();                   //aggiorna il display
 
   if(minutes == 0000) {                      //quando il timer arriva a 0
     buzzerFlag = false;                      //attiva il buzzer
     prevMillis = millis();                   //snapshot in millisecondi
     counter++;                               //aggiungi +1 quando il timer finisce
     if(counter >=9) {                        //fine ciclo
      buzz();
      //counter = 0;                          //reset ciclo
      sevseg.setNumber(0000);
     }
     Serial.println(counter);
   }
}

void loop() {
  if(workMode){
    buzz();
    countdown(mode[0]);
  }
  if(shortBreak){
    buzz();
    countdown(mode[1]);
  }
  if(longBreak){
    buzz();
    countdown(mode[2]);
  }
  if(digitalRead(buttonPin) == LOW){
    reset();
  }
}
