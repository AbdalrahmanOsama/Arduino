#include <LiquidCrystal_I2C.h>
#include <dht.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
dht DHT;

//pins setup
int BUZZER = 2;
int REDled = 3;
int GREENled = 5;
int BLUEled = 6;
const int BUTTONpin = 7;
int PUMPrelay = 13;
int LIGHTSrelay = 12;

int GASsensor = A0;
int DHTsensor = A1;
int MOISTUREsensor = A2;
int LDRsensor = A3;

//variables
int GASvalue;
int TEMPERATUREvalue;
int HUMIDITYvalue;
int MOISTUREvalue;
int LDRvalue;
String MOISTURElevel;
String PUMPstate;
String LIGHTSstate;

int BUTTONstate = HIGH;
int lastBUTTONstate = HIGH;
int DISPLAYstate = 1;

void updateDisplay(int DISPLAYnum);

void setup() {
  Serial.begin(115200);

  pinMode(GASsensor, INPUT);
  pinMode(DHTsensor, INPUT);
  pinMode(MOISTUREsensor, INPUT);
  pinMode(LDRsensor, INPUT);
  pinMode(BUTTONpin, INPUT_PULLUP);

  pinMode(BUZZER, OUTPUT);
  pinMode(REDled, OUTPUT);
  pinMode(GREENled, OUTPUT);
  pinMode(BLUEled, OUTPUT);
  pinMode(PUMPrelay, OUTPUT);
  pinMode(LIGHTSrelay, OUTPUT);

  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("IRRIGATION");
  lcd.setCursor(0, 1);
  lcd.print("SYSTEM ON ");
  lcd.print("");
  delay(3000);
  lcd.clear();

  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
}

void loop() {
  //smoke
  GASvalue = analogRead(GASsensor);
  Serial.print("Gas Value:");
  Serial.println(GASvalue);
  // if (GASvalue > 500) {
  //   digitalWrite(BUZZER, HIGH);
  //   tone(BUZZER, 494, 500);
  // } else {
  //   digitalWrite(BUZZER, LOW);
  // }
  
  //temperature & humidity
  int DHTread = DHT.read11(DHTsensor);
  TEMPERATUREvalue = DHT.temperature;
  HUMIDITYvalue = DHT.humidity;
  Serial.print("Temperature:");
  Serial.println(TEMPERATUREvalue);
  Serial.print("Humidity:");
  Serial.println(HUMIDITYvalue);
  // if (TEMPERATUREvalue <= 29) {
  //   analogWrite(REDled, 0);
  //   analogWrite(GREENled, 0);
  //   analogWrite(BLUEled, 255);
  // } else if (TEMPERATUREvalue >= 30 && TEMPERATUREvalue <= 31) {
  //   analogWrite(REDled, 0);
  //   analogWrite(GREENled, 255);
  //   analogWrite(BLUEled, 0);
  // } else {
  //   analogWrite(REDled, 255);
  //   analogWrite(GREENled, 0);
  //   analogWrite(BLUEled, 0);
  // }

  //moisture
  MOISTUREvalue = analogRead(MOISTUREsensor);
  Serial.print("Moisture:");
  Serial.println(MOISTUREvalue);
  // if (MOISTUREvalue > 800) {
  //   digitalWrite(PUMPrelay, LOW);
  //   PUMPstate = "ON";
  // } else {
  //   digitalWrite(PUMPrelay, HIGH);
  //   PUMPstate = "OFF";
  // }
  // if (MOISTUREvalue < 300) {
  //   MOISTURElevel = "HIGH";
  // } else if (MOISTUREvalue > 300 && MOISTUREvalue < 800) {
  //   MOISTURElevel = "MEDIUM";
  // } else if (MOISTUREvalue > 800) {
  //   MOISTURElevel = "LOW";
  // }

  //Light
  LDRvalue = analogRead(LDRsensor);
  Serial.print("Light:");
  Serial.println(LDRvalue);
  // if (LDRvalue <= 950) {
  //   digitalWrite(LIGHTSrelay, LOW);
  //   LIGHTSstate = "ON";
  // } else {
  //   digitalWrite(LIGHTSrelay, HIGH);
  //   LIGHTSstate = "OFF";
  // }

  //states
  BUTTONstate = digitalRead(BUTTONpin);
  if (BUTTONstate != lastBUTTONstate) {
    if (BUTTONstate == LOW) {
      DISPLAYstate++;          // Increment the display state
      if (DISPLAYstate > 3) {  // If there are 3 displays, reset to 1
        DISPLAYstate = 1;
      }
    }
    delay(50);  // Debounce delay
  }
  lastBUTTONstate = BUTTONstate;
  updateDisplay(DISPLAYstate);  // Call a function to update the display

  Serial.println("=========");
  delay(2000);
}

void updateDisplay(int DISPLAYnum) {
  lcd.clear();
  lcd.setCursor(0, 0);
  switch (DISPLAYnum) {
    case 1:
      lcd.print("MOISTURE: ");
      lcd.print(MOISTURElevel);
      lcd.setCursor(0, 1);
      lcd.print("WATER PUMP ");
      lcd.print(PUMPstate);
      break;

    case 2:
      lcd.print("TEMP: ");
      lcd.print(DHT.temperature);
      lcd.print((char)223);
      lcd.print("C");
      lcd.setCursor(0, 1);
      lcd.print("Humidity: ");
      lcd.print(DHT.humidity);
      lcd.print("%");
      break;

    case 3:
      lcd.print("Light int.: ");
      lcd.print(LDRvalue);
      lcd.setCursor(0, 1);
      lcd.print("LIGHTS ");
      lcd.print(LIGHTSstate);
      break;
  }
}