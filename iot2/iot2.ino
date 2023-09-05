#include <LiquidCrystal_I2C.h>
#include <dht.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
dht DHT;
//SoftwareSerial esp8266(0, 1);  // RX, TX


//pins setup
int buzzer = 2;
int redled = 3;
int greenled = 5;
int blueled = 6;
int pumprelay = 13;
int lightsrelay = 12;

int smokesensor = A0;
int tempsensor = A1;
int moistsensor = A2;
int ldrsensor = A3;

//variables
int smokevalue;
int tempvalue;
int lightvalue;
String moisturelevel;
String pumpstatus;
String lightstatus;


const int buttonPin = 7;
int buttonState = HIGH;
int lastButtonState = HIGH;
int displayState = 1;

void updateDisplay(int displayNum);

void setup() {
  Serial.begin(115200);
  //esp8266.begin(115200);


  pinMode(smokesensor, INPUT);
  pinMode(tempsensor, INPUT);
  pinMode(moistsensor, INPUT);
  pinMode(ldrsensor, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(blueled, OUTPUT);
  pinMode(pumprelay, OUTPUT);
  pinMode(lightsrelay, OUTPUT);

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

  ////esp8266.println("AT");
}

void loop() {
  // //smoke
  smokevalue = analogRead(smokesensor);
  //esp8266.print("Gas Value: ");
  //esp8266.println(smokevalue);
  if (smokevalue > 500) {
    //esp8266.print("SMOKE DETECTED!!!!!!!!!!!!!!!!!!!!");
    digitalWrite(buzzer, HIGH);
    tone(buzzer, 494, 500);
  } else {
    digitalWrite(buzzer, LOW);
  }

  //temperature & humidity
  int tempvalue = analogRead(tempsensor);
  if (tempvalue <= 35) {
    analogWrite(redled, 0);
    analogWrite(greenled, 0);
    analogWrite(blueled, 255);
  } else if (tempvalue >= 36 && tempvalue <= 39) {
    analogWrite(redled, 0);
    analogWrite(greenled, 255);
    analogWrite(blueled, 0);
  } else {
    analogWrite(redled, 255);
    analogWrite(greenled, 0);
    analogWrite(blueled, 0);
  }

  int chk = DHT.read11(tempsensor);
  //esp8266.print("Temperature = ");
  //esp8266.println(DHT.temperature);
  //esp8266.print("Humidity = ");
  //esp8266.println(DHT.humidity);
  delay(1000);

  //moisture
  int moistvalue = analogRead(moistsensor);

  //esp8266.println("moisture: ");
  //esp8266.println(moistvalue);
  if (moistvalue > 800) {
    digitalWrite(pumprelay, LOW);
    pumpstatus = "ON";
  } else {
    digitalWrite(pumprelay, HIGH);
    pumpstatus = "OFF";
  }
  if (moistvalue < 300) {
    moisturelevel = "HIGH";
  } else if (moistvalue > 300 && moistvalue < 800) {
    moisturelevel = "MEDIUM";
  } else if (moistvalue > 800) {
    moisturelevel = "LOW";
  }

  //Light
  int lightvalue = analogRead(ldrsensor);
  if (lightvalue <= 950) {
    digitalWrite(lightsrelay, LOW);
    lightstatus = "ON";
    //esp8266.println("Light Value: ");
    //esp8266.println(lightvalue);
  } else {
    digitalWrite(lightsrelay, HIGH);
    lightstatus = "OFF";
  }

  //states
  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      displayState++;          // Increment the display state
      if (displayState > 3) {  // If there are 3 displays, reset to 1
        displayState = 1;
      }
    }
    delay(50);  // Debounce delay
  }
  lastButtonState = buttonState;
  updateDisplay(displayState);  // Call a function to update the display

  // while (esp8266.available()) {
  //   char c = esp8266.read();
  //   Serial.write(c);  // Forward data from //esp8266 to Arduino //esp8266 Monitor
  //   //Serial.print(c);

  //   delay(100);
  // }
}
void updateDisplay(int displayNum) {
  lcd.clear();
  lcd.setCursor(0, 0);
  switch (displayNum) {
    case 1:
      lcd.print("MOISTURE: ");
      lcd.print(moisturelevel);
      lcd.setCursor(0, 1);
      lcd.print("WATER PUMP ");
      lcd.print(pumpstatus);
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
      lcd.print(lightvalue);
      lcd.setCursor(0, 1);
      lcd.print("LIGHTS ");
      lcd.print(lightstatus);
      break;
  }
}