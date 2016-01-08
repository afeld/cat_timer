/*
  Modified from http://www.arduino.cc/en/Tutorial/Button. Requires http://playground.arduino.cc/Code/SimpleTimer.

  The circuit:
  * LED attached from pin 13 to ground
  * pushbutton attached from pin 2 to +5V
  * 10K resistor attached from pin 2 to ground
 */

#include <SimpleTimer.h>

// the timer object
SimpleTimer timer;

const int buttonPin = 2;
const int ledPin = 13;
const int feedingInterval = 1000 * 3; // in milliseconds

int buttonState = LOW;
boolean buttonEnabled = true;

void feedMe() {
  // turn LED on
  digitalWrite(ledPin, HIGH);
  buttonEnabled = true;
}

void setup() {
  // initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input
  pinMode(buttonPin, INPUT);

  // turn LED on
  digitalWrite(ledPin, HIGH);
}

void loop() {
  if (buttonEnabled) {
    buttonState = digitalRead(buttonPin);
  
    if (buttonState == HIGH) {
      // ignore it if pressed again in the same feeding cycle
      buttonEnabled = false;

      // turn LED off
      digitalWrite(ledPin, LOW);
      timer.setTimeout(feedingInterval, feedMe);
    }
  }

  timer.run();
}
