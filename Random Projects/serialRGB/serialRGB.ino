
int redled = 3;
int greenled = 5;
int blueled = 6;
char reading;


void setup() {
  // put your setup code here, to run once:
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(blueled, OUTPUT);
  Serial.begin(9600);

}

void loop() {

  if(Serial.available() > 0)
  {
    reading = Serial.read();
    switch(reading)
    {
      case 'R': analogWrite(redled,255);
      Serial.println("Red is on");
      break;

      case 'G': analogWrite(greenled,255);
      Serial.println("Green is on");
      break;

      case 'B': analogWrite(blueled,255);
      Serial.println("Blue is on");
      break;

      case 'F': analogWrite(redled,0);
                analogWrite(greenled,0);
                analogWrite(blueled,0);
      Serial.println("OFF");
      break;
    }
  }

}
