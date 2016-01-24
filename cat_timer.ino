// https://github.com/afeld/cat_timer

#include <SimpleTimer.h>

SimpleTimer timer;

// configuration
const int buttonPin = 2;
const int ledPin = 13;
const int sensorPin = A7;
const float voltageThreshold = 6.00;
const int blinkInterval = 1000 * 10; // amount of time between blinks, in ms
const long feedingInterval = ((long) 1000) * 60 * 60 * 10; // in milliseconds

// internal
const long buttonDebounce = ((long) 1000) * 5; // in milliseconds
int buttonState = LOW;
boolean buttonEnabled = true;
int feedingTimer = -1;
int intervalId = -1;

// ------ general helpers --------

void turnOffLed() {
  digitalWrite(ledPin, LOW);
}

void turnOnLed() {
  digitalWrite(ledPin, HIGH);
}

// ----- voltage-related methods --------

float getVoltage() {
  int sensorValue = analogRead(sensorPin); // read the A0 pin value
  return sensorValue * (5.00 / 1023.00) * 2; // convert the value to a true voltage
}


void blinkOnce() {
  turnOnLed();
  timer.setTimeout(50, turnOffLed);
}

void startBlinking() {
  intervalId = timer.setInterval(blinkInterval, blinkOnce);
}

void stopBlinking() {
  timer.deleteTimer(intervalId);
  intervalId = -1;
  turnOffLed();
}

void checkVoltage() {
  float voltage = getVoltage();
  if (voltage < voltageThreshold) {
    // check if already blinking
    if (intervalId < 0) {
      startBlinking();
    }
  } else {
    // check if already blinking
    if (intervalId >= 0) {
      stopBlinking();
    }
  }
}

// ------ feeding-related methods ---------

void markFed() {
  turnOffLed();
}

void enableButton() {
  buttonEnabled = true;
}

void debounceButton() {
  buttonEnabled = false;
  timer.setTimeout(buttonDebounce, enableButton);
}

boolean isFeedingTimerRunning() {
  return feedingTimer >= 0;
}

void needsFood() {
  enableButton();
  turnOnLed();
  feedingTimer = -1;
}

void resetFeedingInterval() {
  if (isFeedingTimerRunning()) {
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

// -----------------------------

void setup() {
  // initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input
  pinMode(buttonPin, INPUT);

  turnOnLed();
}

void loop() {
  if (buttonEnabled) {
    checkButtonPush();
  }
  // only worry about voltage when the timer is running and thus the LED is off anyway
  if (isFeedingTimerRunning()) {
    checkVoltage();
  }

  timer.run();
}
