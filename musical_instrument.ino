#include <Servo.h>
#include "pitches.h"

Servo servo1;                   //controls red and green
Servo servo2;                   //controls yellow and blue
const int potentiometer1 = A0;  //controls tempo
const int grey = 6;             //controls power
const int red = 2;              //C3
const int green = 3;            //E3
const int yellow = 4;           //D3
const int blue = 5;             //G3
int melodySize = 27;
int melody[] = {
  green, yellow, red, yellow, green, green, green, yellow, yellow, yellow, green, blue, blue, green, yellow, red, yellow, green, green, green, green, yellow, yellow, green, yellow, red, 0
};
int duration[] = {
  1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 4
};

void setup() {
  Serial.begin(9600);
  servo1.attach(10);
  servo1.write(90);
  servo2.attach(9);
  servo2.write(90);
  delay(10);
  pinMode(red, INPUT_PULLUP);
  pinMode(green, INPUT_PULLUP);
  pinMode(yellow, INPUT_PULLUP);
  pinMode(blue, INPUT_PULLUP);
  pinMode(grey, INPUT_PULLUP);
}

void loop() {
  if (!digitalRead(grey)) {                       //press the button to start the melody
    delay(500);
    for (int i = 0; i < melodySize; i ++) {
      if (!playTone(melody[i], duration[i])) {    //continue if true, stop if false
        delay(500);
        break;                                    //press the button during the melody to stop
      }
    }
  }
  delayAndPlay(100);                              //so that user can play their own music
}

bool playTone(int color, int duration) {
  //move the servo
  if (color == green) {
    servo1.write(40);
  }
  if (color == red) {
    servo1.write(120);
  }
  if (color == yellow) {
    servo2.write(30);
  }
  if (color == blue) {
    servo2.write(140);
  }
  int interval = map(analogRead(potentiometer1), 0, 1023, 200, 500);
  bool off = delayAndPlay(interval * duration);
  servo1.write(90);
  servo2.write(90);                               //restore the position
  return (off && delayAndPlay(100 * duration));   //return false if button press is detected
}

bool delayAndPlay(long interval) {
  long currentTime = millis();
  for (long i = millis(); i < currentTime + interval; i = millis()) {
    if (!digitalRead(grey)) {
      return false;                               //if button is pressed during the melody, stop immediately and return false
    }
    //make the tone
    if (!digitalRead(red)) {
      tone(8, NOTE_C3, 10);
    }
    if (!digitalRead(green)) {
      tone(8, NOTE_E3, 10);
    }
    if (!digitalRead(yellow)) {
      tone(8, NOTE_D3, 10);
    }
    if (!digitalRead(blue)) {
      tone(8, NOTE_G3, 10);
    }
  }
  return true;
}
