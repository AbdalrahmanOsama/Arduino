#include <Servo.h>

Servo servoMotor;
int photoresistorPin = A0;
int photoresistorThreshold = 900; // Adjust this threshold based on your sensor readings
int jumpDuration = 300; // Adjust this duration for the servo movement

void setup() {
  servoMotor.attach(9);
  pinMode(photoresistorPin, INPUT);
  Serial.begin(38400);
}

void loop() {
  int obstacleValue = analogRead(photoresistorPin);
  
  if (obstacleValue > photoresistorThreshold) {
    jump();
  }
}

void jump() {
  servoMotor.write(90); // Adjust the angle for your servo to simulate a spacebar press
  delay(jumpDuration);
  servoMotor.write(0); // Return to the original position
}
