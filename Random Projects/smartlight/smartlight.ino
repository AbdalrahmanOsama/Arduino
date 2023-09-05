
int sensorpin = A0;
int relaypin = 8;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(relaypin, OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorvalue = analogRead(sensorpin);
  if (sensorvalue <= 60)
  {
    digitalWrite(relaypin, LOW);
    Serial.println(sensorvalue);
    delay(100);
  }
  else
  {
    digitalWrite(relaypin, HIGH);
    Serial.println(sensorvalue);
  }

}
