
int ledpin1 = 11;
int button1 = 8;
int button2 = 9;
int reading = 0;
int ledbrightness = 128;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledpin1, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(button1) == LOW)
  {
    ledbrightness -= 15;
  }
  else if(digitalRead(button2) == LOW)
  {
    ledbrightness += 15;
  }
  ledbrightness = constrain(ledbrightness, 0, 255);
  analogWrite(ledpin1, ledbrightness);
  delay(500);
  
}