#include <Wire.h>
#include <ZumoShield.h>

#define LED_PIN 13
#define FORWARD_PIN 2 // if high, drive forwards
#define BACKWARD_PIN 3 // if high, drive backwards
#define LEFT_PIN 4 // if high, turn left
#define RIGHT_PIN 5 // if high, turn right
#define ARMING_PIN 6 // if high, enable drive commands

ZumoMotors motors;
int motorSpeed = 200; // Initial motor speed
int driveDelay = 10; // Delay in milliseconds
int speedLeft, speedRight;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(FORWARD_PIN, INPUT_PULLUP);
  pinMode(BACKWARD_PIN, INPUT_PULLUP);
  pinMode(LEFT_PIN, INPUT_PULLUP);
  pinMode(RIGHT_PIN, INPUT_PULLUP);
  pinMode(ARMING_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop()
{
  bool forward = digitalRead(FORWARD_PIN) == LOW;
  bool backward = digitalRead(BACKWARD_PIN) == LOW;
  bool left = digitalRead(LEFT_PIN) == LOW;
  bool right = digitalRead(RIGHT_PIN) == LOW;
  bool armed = digitalRead(ARMING_PIN) == LOW;

  // check that no more than one drive command is active and the arming pin is LOW
  if ((forward + backward + left + right) == 1 && armed)
  {

    // check for individual drive commands
    if (forward)
    {
      // run both motors forward
      motors.setLeftSpeed(motorSpeed);
      motors.setRightSpeed(motorSpeed);
    }
    else if (backward)
    {
      // run both motors backward
      motors.setLeftSpeed(-motorSpeed);
      motors.setRightSpeed(-motorSpeed);
    }
    else if (left)
    {
      // run left motor backward and right motor forward
      motors.setLeftSpeed(-motorSpeed);
      motors.setRightSpeed(motorSpeed);
    }
    else if (right)
    {
      // run left motor forward and right motor backward
      motors.setLeftSpeed(motorSpeed);
      motors.setRightSpeed(-motorSpeed);
    }
    else
    {
      // stop both motors
      motors.setLeftSpeed(0);
      motors.setRightSpeed(0);
    }

    delay(driveDelay);
  }

  else
  {
    // stop both motors
    motors.setLeftSpeed(0);
    motors.setRightSpeed(0);
  }

  if (Serial.available()) {
    speedLeft = Serial.parseInt(); // Read the first integer from serial input
    if (Serial.read() == ',') { // Ensure data is correctly formatted
        speedRight = Serial.parseInt(); // Read the second integer
    
        // Set motor speeds
        motors.setLeftSpeed(speedLeft);
        motors.setRightSpeed(speedRight);
        delay(10); // Delay to allow motors to respond
    }
  }
}
