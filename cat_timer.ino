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

int buttonState = 0;

void feedMe() {
    // turn LED on
    digitalWrite(ledPin, HIGH);
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
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    // turn LED off
    digitalWrite(ledPin, LOW);
    timer.setTimeout(1000, feedMe);
  }

  timer.run();
}
