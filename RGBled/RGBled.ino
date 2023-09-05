
int redled = 3;
int greenled = 5;
int blueled = 6;
int redpot = A0;
int greenpot = A1;
int bluepot = A2;
int potvalue;
int ledvalue;
// int redbrightness = 128;
// int greenbrightness = 128;
// int bluebrightness = 128;

void setup() {
  // put your setup code here, to run once:
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(blueled, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  potvalue = analogRead(redpot);
  ledvalue = map(potvalue, 0, 1023, 0, 255);
  analogWrite(redled, ledvalue);

  potvalue = analogRead(greenpot);
  ledvalue = map(potvalue, 0, 1023, 0, 255);
  analogWrite(greenled, ledvalue);

  potvalue = analogRead(bluepot);
  ledvalue = map(potvalue, 0, 1023, 0, 255);
  analogWrite(blueled, ledvalue);

}
