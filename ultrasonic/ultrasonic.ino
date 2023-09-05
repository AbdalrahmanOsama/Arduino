
int triggerpin = 12;
int echopin = 11;
int buzzerpin = 13;
long duration, distance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(triggerpin, OUTPUT);
  pinMode(echopin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(triggerpin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerpin, LOW);
  duration = pulseIn(echopin, HIGH);
  distance = (duration/2) * 0.0343;
  if (distance < 50)
  {
    tone(buzzerpin, 440, 200);
    delay(200);
    noTone(buzzerpin);
  }
  Serial.println(distance);
  delay(5);

}
