
int ledpin1 = 13;
int ledpin2 = 12;
int ledpin3 = 11;
void setup() {
  // put your setup code here, to run once:
  pinMode(ledpin1, OUTPUT);
  pinMode(ledpin2, OUTPUT);
  pinMode(ledpin3, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledpin1, HIGH);
  delay(1000);
  digitalWrite(ledpin1, LOW);
  delay(1000);
  digitalWrite(ledpin2, HIGH);
  delay(1000);
  digitalWrite(ledpin2, LOW);
  delay(1000);
  digitalWrite(ledpin3, HIGH);
  delay(1000);
  digitalWrite(ledpin3, LOW);
  delay(1000);
}
