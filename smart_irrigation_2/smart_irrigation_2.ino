#include <LiquidCrystal_I2C.h>
#include <dht.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
dht DHT;

//DHT
int DHTsensor;
int DHTread = DHT.read11(temperatureSensor);

//pins setup
int RGB_RED = 2;
int RGB_GREEN =3;
int RGB_BLUE = 4;
int LED_YELLOW = 5;
int LED_GREEN = 6;
int LED_WHITE = 7;
int BUZZER = 8;
int BUTTON = 9;

//sensors
int temperatureSensor = A0;
int gasSensor = A1;
int moistureSensor = A2;
int lightSensor = A3;

//variables
int GASvalue;
int MOISTUREvalue;
int LIGHTvalue;
float TEMPERATUREvalue;
float HUMIDITYvalue;

String MOISTURElevel;
String PUMPstatus;
String LIGHTSstatus;

int BUTTONstatus = HIGH;
int lastBUTTONstatus = HIGH;
int DISPLAYstate = 1;

void updateDisplay(int DISPLAYnum);

void setup() {
  // put your setup code here, to run once:
  
  //lcd setup
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("IRRIGATION");
  lcd.setCursor(0, 1);
  lcd.print("SYSTEM ON ");
  lcd.print("");
  delay(2500);
  lcd.clear();

  //outputs pins
  pinMode(RGB_RED, OUTPUT);
  pinMode(RGB_GREEN, OUTPUT);
  pinMode(RGB_BLUE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_WHITE, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  //inputs pins
  pinMode(temperatureSensor, INPUT);
  pinMode(gasSensor, INPUT);
  pinMode(moistureSensor, INPUT);
  pinMode(lightSensor, INPUT);


  //button pin
  pinMode(BUTTON, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  //Light
  LIGHTvalue = analogRead();
  Serial.print("Light=");
  Serial.println(LIGHTvalue);
  if (LIGHTvalue <= 900) {
    analogWrite(LED_WHITE, 255);
    LIGHTSstatus = "ON";

  } else {
    analogWrite(LED_WHITE, 0);
    LIGHTSstatus = "OFF";
  }
  // if (inLDR <= 900) {
  //   analogWrite(LED_WHITE, 255);
  // } else {
  //   analogWrite(LED_WHITE, 0);
  // }

  //moisture
  MOISTUREvalue = SENSORvalues[3];
  Serial.print("Moisture=");
  Serial.print(MOISTUREvalue);
  Serial.print(", ");
  if (MOISTUREvalue > 800) {
    // digitalWrite(PUMPrelay, LOW);
    // PUMPstate = "ON";
    analogWrite(LED_GREEN, 255);
    PUMPstatus = "ON";
  } else {
    // digitalWrite(PUMPrelay, HIGH);
    // PUMPstate = "OFF";
    analogWrite(LED_GREEN, 0);
    PUMPstatus = "OFF";
  }
  // if (inMoisture > 800) {
  //   digitalWrite(PUMPrelay, LOW);
  //   PUMPstate = "ON";
  //   analogWrite(LED_YELLOW, 255);
  // } else {
  //   digitalWrite(PUMPrelay, HIGH);
  //   PUMPstate = "OFF";
  //   analogWrite(LED_YELLOW, 0);
  // }
  // if (inMoisture < 300) {
  //   MOISTURElevel = "HIGH";
  // } else if (inMoisture > 300 && inMoisture < 800) {
  //   MOISTURElevel = "MEDIUM";
  // } else if (inMoisture > 800) {
  //   MOISTURElevel = "LOW";
  // }
  if (MOISTUREvalue < 300) {
    MOISTURElevel = "HIGH";
  } else if (MOISTUREvalue > 300 && MOISTUREvalue < 800) {
    MOISTURElevel = "MEDIUM";
  } else if (MOISTUREvalue > 800) {
    MOISTURElevel = "LOW";
  }

  //gas
  GASvalue = SENSORvalues[4];
  Serial.print("Gas=");
  Serial.print(GASvalue);
  Serial.print(", ");
  if(GASvalue > 600){
    analogWrite(BUZZER, HIGH);
    tone(BUZZER, 494, 500);
    digitalWrite(LED_YELLOW, HIGH);
  }
  else{
    analogWrite(BUZZER, LOW);
    digitalWrite(LED_YELLOW, LOW);
  }
  // if (inGas > 600) {
  //   digitalWrite(BUZZER, HIGH);
  //   tone(BUZZER, 494, 500);
  // } else {
  //   digitalWrite(BUZZER, LOW);
  // }
  
  //temperature & humidity
  TEMPERATUREvalue = DHT.temperature;
  HUMIDITYvalue = DHT.humidity;
  Serial.print("Temperature=");
  Serial.print(TEMPERATUREvalue);
  Serial.print(", ");
  Serial.print("Humidity=");
  Serial.print(HUMIDITYvalue);
  Serial.print(", ");
  if (TEMPERATUREvalue <= 27) {
    analogWrite(RGB_RED, 0);
    analogWrite(RGB_GREEN, 0);
    analogWrite(RGB_BLUE, 255);
  } else if (TEMPERATUREvalue >= 28 && TEMPERATUREvalue <= 31) {
    analogWrite(RGB_RED, 0);
    analogWrite(RGB_GREEN, 255);
    analogWrite(RGB_BLUE, 0);
  } else {
    analogWrite(RGB_RED, 255);
    analogWrite(RGB_GREEN, 0);
    analogWrite(RGB_BLUE, 0);
  }
  // if (inTemperature <= 27) {
  //   analogWrite(RGB_RED, 0);
  //   analogWrite(RGB_GREEN, 0);
  //   analogWrite(RGB_BLUE, 255);
  // } else if (inTemperature >= 28 && inTemperature <= 31) {
  //   analogWrite(RGB_RED, 0);
  //   analogWrite(RGB_GREEN, 255);
  //   analogWrite(RGB_BLUE, 0);
  // } else {
  //   analogWrite(RGB_RED, 255);
  //   analogWrite(RGB_GREEN, 0);
  //   analogWrite(RGB_BLUE, 0);
  // }


  //states
  BUTTONstatus = digitalRead(BUTTON);
  if (BUTTONstatus != lastBUTTONstatus) {
    if (BUTTONstatus == LOW) {
      DISPLAYstate++;          // Increment the display state
      if (DISPLAYstate > 3) {  // If there are 5 displays, reset to 1
        DISPLAYstate = 1;
      }
    }
    delay(50);  // Debounce delay
  }
  lastBUTTONstatus = BUTTONstatus;
  updateDisplay(DISPLAYstate);  // Call a function to update the display

  Serial.println("=========");
  delay(1000);

}

//LCD state view
void updateDisplay(int DISPLAYnum) {
  lcd.clear();
  lcd.setCursor(0, 0);
  switch (DISPLAYnum) {
    case 1:
      lcd.print("MOISTURE: ");
      lcd.print(MOISTURElevel);
      lcd.setCursor(0, 1);
      lcd.print("WATER PUMP ");
      lcd.print(PUMPstatus);
      break;

    case 2:
      lcd.print("TEMP: ");
      lcd.print(TEMPERATUREvalue);
      lcd.print((char)223);
      lcd.print("C");
      lcd.setCursor(0, 1);
      lcd.print("Humidity: ");
      lcd.print(HUMIDITYvalue);
      lcd.print("%");
      break;

    case 3:
      lcd.print("Light int.: ");
      lcd.print(LIGHTvalue);
      lcd.setCursor(0, 1);
      lcd.print("LIGHTS ");
      lcd.print(LIGHTSstatus);
      break;

  }

  //reading data from cloud
  // if (Serial.available() > 0) {
  //   // read the incoming byte:
  //   String incomingByte = Serial.readString();
  //   // say what you got:
  //   if (incomingByte[0] == 'L') {
  //     incomingByte.remove(0, 1);
  //     LIGHTin = incomingByte.toFloat();
  //     //Serial.println("Light: ");
  //     //Serial.println(LIGHTin);}
  //   } else if (incomingByte[0] == 'F') {
  //     incomingByte.remove(0, 1);
  //     FIREin = incomingByte.toFloat();
  //     //Serial.println("Fire: ");
  //     //Serial.println(FIREin);}
  //   } else if (incomingByte[0] == 'R') {
  //     incomingByte.remove(0, 1);
  //     RAINin = incomingByte.toFloat();
  //     //Serial.println("Rain: ");
  //     //Serial.println(RAINin);}
  //   } else if (incomingByte[0] == 'M') {
  //     incomingByte.remove(0, 1);
  //     MOISTUREin = incomingByte.toFloat();
  //     //Serial.println("Moisture: ");
  //     //Serial.println(MOISTUREin);}
  //   } else if (incomingByte[0] == 'G') {
  //     incomingByte.remove(0, 1);
  //     GASin = incomingByte.toFloat();
  //     //Serial.println("Gas: ");
  //     //Serial.println(GASin);}
  //   } else if (incomingByte[0] == 'T') {
  //     incomingByte.remove(0, 1);
  //     TEMPERATUREin = incomingByte.toFloat();
  //     //Serial.println("Temperature: ");
  //     //Serial.println(TEMPERATUREin);}
  // } else if (incomingByte[0] == 'H') {
  //     incomingByte.remove(0, 1);
  //     HUMIDITYin = incomingByte.toFloat();
  //     //Serial.println("Humidity: ");
  //     //Serial.println(HUMIDITYin);
  //     }
  //}
}


