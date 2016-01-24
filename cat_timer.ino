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
const long feedingInterval = ((long) 1000) * 60 * 60 * 10; // in milliseconds
const long buttonDebounce = ((long) 1000) * 5; // in milliseconds

int buttonState = LOW;
boolean buttonEnabled = true;
int feedingTimer = -1;

void markFed() {
  // turn LED off
  digitalWrite(ledPin, LOW);
}

void enableButton() {
  buttonEnabled = true;
}

void debounceButton() {
  buttonEnabled = false;
  timer.setTimeout(buttonDebounce, enableButton);
}

void needsFood() {
  enableButton();
  // turn LED on
  digitalWrite(ledPin, HIGH);
  feedingTimer = -1;
}

void resetFeedingInterval() {
  if (feedingTimer >= 0) {
    // already a timer running - they were fed early
    timer.restartTimer(feedingTimer);
  } else {
    feedingTimer = timer.setTimeout(feedingInterval, needsFood);
  }
}

void checkButtonPush() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    markFed();
    resetFeedingInterval();
    debounceButton();
  }
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
    checkButtonPush();
  }

  timer.run();
}
