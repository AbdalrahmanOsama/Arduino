
int smokesensor = A0;
int buzzer = 13;
int sensorvalue;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  Serial.println("Gas sensor warming up");
  delay(2000);

}

void loop() {
  // put your main code here, to run repeatedly:
  sensorvalue = analogRead(smokesensor);
  Serial.print("Sensor Value: ");
  Serial.println(sensorvalue);
  if (sensorvalue > 200)
  {
    Serial.print("SMOKE DETECTED!!!!!!!!!!!!!!!!!!!!");
    digitalWrite(buzzer, HIGH);
    tone(buzzer,494,500);
  }
  else
  {
    digitalWrite(buzzer, LOW);
  }
  delay(2000);

}
