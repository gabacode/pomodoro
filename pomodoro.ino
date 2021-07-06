#define works 0
#define shortBreak 1
#define longBreak 2

#include "SevSegShift.h"

#define SHIFT_PIN_DS   13
#define SHIFT_PIN_STCP 12
#define SHIFT_PIN_SHCP 11

const int buttonPin = 2;
const int buzzer = 3;
int state = works;
int counter = 0;
bool buzzerFlag = true;

long minute = 60000;
long second =  1000;

SevSegShift sevseg(SHIFT_PIN_DS, SHIFT_PIN_SHCP, SHIFT_PIN_STCP);

void setup() {
  pinMode(buzzer, OUTPUT);
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
  sevseg.setBrightness(100);
}

void countdown(int m){
   long work = minute * m;
   long timeNow = work - millis();
   int minutes = timeNow / minute;
   int seconds = (timeNow % minute) / second;
   minutes = (minutes * 100) + seconds;
   sevseg.setNumber(minutes);
   sevseg.refreshDisplay();
}

void workMode(void){
  pomodoroStatus();
  countdown(25);
  counter++;
  if(counter <= 3){
    state = shortBreak;
  }
  if(counter == 4){
    state = longBreak;
  }
}
  
void shortBreakMode(void){
  pomodoroStatus();
  countdown(5);
  if(counter<=3){
    state = works;
  }
}

void longBreakMode(void){
  pomodoroStatus();
  countdown(20);
  while(digitalRead(buttonPin) == 1);
  counter = 0;
  state = works; 
}

void buzz(int number){
  if (buzzerFlag == true){
    tone(buzzer, number, 100);
    delay(number / 2);
    buzzerFlag = false;
  }
 }

void pomodoroStatus(void){
  if(counter == 0){
    buzz(1000);
  }
  if(counter == 1){
    buzz(1500);
  }
  if(counter == 2){
    //buzz three times
  }
  if(counter == 3){
    //buzz four times
  }
  if(counter == 4){
    //buzz five times
  }

}

void loop() {
  if(state == works){
    workMode(); 
  }
  if(state == shortBreak){
    shortBreakMode();
  }
  if(state == longBreak){
    longBreakMode();
  }
}
