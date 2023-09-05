//pins setups
//RGBled
int redled = 3;
int greenled = 5;
int blueled = 6;
int redpot = A0;
int greenpot = A1;
int bluepot = A2;
int potvalue;
int ledvalue;

//smoke
int smokesensor = A3;
int buzzer = 2;
int smokevalue;

//smartlight
int lightsensor = A4;
int relay = 4;

//temperature
int tempsensor = A5;

void setup() {
  //RGBled
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(blueled, OUTPUT);

  //smoke
  pinMode(buzzer, OUTPUT);
  Serial.println("Gas sensor warming up");
  delay(2000);

  //smartlight
  pinMode(relay, OUTPUT);

  //temp
  pinMode(tempsensor, INPUT);

  Serial.begin(9600);
}

void loop() {
  //RGBled
  potvalue = analogRead(redpot);
  ledvalue = map(potvalue, 0, 1023, 0, 255);
  analogWrite(redled, ledvalue);

  potvalue = analogRead(greenpot);
  ledvalue = map(potvalue, 0, 1023, 0, 255);
  analogWrite(greenled, ledvalue);

  potvalue = analogRead(bluepot);
  ledvalue = map(potvalue, 0, 1023, 0, 255);
  analogWrite(blueled, ledvalue);

  //smoke
  smokevalue = analogRead(smokesensor);
  if (smokevalue > 300)
  {
    Serial.println("SMOKE DETECTED!!!!!!!!!!!!!!!!!!!!");
    Serial.print("Smoke Value: ");
    Serial.println(smokevalue);
    digitalWrite(buzzer, HIGH);
    tone(buzzer,494,500);
  }
  else
  {
    digitalWrite(buzzer, LOW);
  }
  delay(2000);

  //smartlight
  int lightvalue = analogRead(lightsensor);
  if (lightvalue <= 100)
  {
    digitalWrite(relay, HIGH);
    Serial.print("Light Value: ");
    Serial.println(lightvalue);
    delay(100);
  }
  else
  {
    digitalWrite(relay, LOW);
  }

  //temp
  int tempvalue = analogRead(tempsensor);
  if (tempvalue >= 50)
  {
    Serial.print("Temperature Value: ");
    Serial.println(tempvalue);

  }

  Serial.print("{");
  Serial.print("\"LightValue:\"");
  Serial.print(lightvalue);
  Serial.print(",");
  Serial.print("\"SmokeValue:\"");
  Serial.print(smokevalue);
  Serial.print(",");
  Serial.print("\"TemperatureValue:\"");
  Serial.print(tempvalue);
  Serial.println("}");


}
