/*------------------------ 
Pomodoro Timer con Arduino
author: gaba@totel.it
credits: BOCS APS, Francesco Cirillo
-----------------------*/

#include <TM1637Display.h>
#define CLK 4
#define DIO 5

int buzzPin = 3;
int counter;
int timer;
int stage;

//Pomodoro modes in number of minutes
int work = 25;
int smallBreak = 5;
int longBreak = 15;

unsigned long currentMillis;
unsigned long prevMillis;

TM1637Display display(CLK, DIO);

void setup() {
  display.setBrightness(0x8);
  delay(500);
}

void reset() {
  buzz();
  asm volatile("jmp 0x7800");
}

void buzz(){
  int melody[] = {523, 659, 784, 1976, 2349, 2960, 3520, 4435};
  int noteDurations[] = {32, 32, 32, 32, 32, 32, 32, 32};
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzzPin, melody[thisNote]+10, noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(8);
  }
}

int mode() {
  if (counter == 1 || counter == 3 || counter == 5 || counter == 7) {
    stage = work;
  }
  if (counter == 2 || counter == 4 || counter == 6 || counter == 8) {
    stage = smallBreak;
  }
  if (counter == 9) {
    stage = longBreak;
  }
  if (counter >= 10) {
    reset();
  }
  return stage;
}

void loop() {
  if (timer == 0000) {
    prevMillis = millis();
    buzz();
    counter++;
    stage = mode();
  }
  currentMillis = (millis() - prevMillis);
  long timeNow = stage * 60000 - currentMillis;
  int minutes = timeNow / 60000;
  int seconds = (timeNow % 60000) / 1000;
  timer = (minutes * 100) + seconds;
  display.showNumberDec(timer, true, 4, 0);
}
