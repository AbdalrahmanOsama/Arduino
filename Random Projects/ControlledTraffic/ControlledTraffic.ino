
int ledpin1 = 9;
int ledpin2 = 10;
int ledpin3 = 11;
int button = 8;
int reading = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledpin1, OUTPUT);
  pinMode(ledpin2, OUTPUT);
  pinMode(ledpin3, OUTPUT);
  pinMode(button, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  reading = digitalRead(button);
  if (reading == HIGH)
  {
    digitalWrite(ledpin1, HIGH);
    digitalWrite(ledpin2, LOW);
    digitalWrite(ledpin3, LOW);
    delay(750);
}
  reading = digitalRead(button);
  if (reading == HIGH)
  {
    digitalWrite(ledpin1, LOW);
    digitalWrite(ledpin2, HIGH);
    digitalWrite(ledpin3, LOW);
    delay(750);
  }
  reading = digitalRead(button);
  if (reading == HIGH)
  {
    digitalWrite(ledpin1, LOW);
    digitalWrite(ledpin2, LOW);
    digitalWrite(ledpin3, HIGH);
    delay(750);
  }
 
}