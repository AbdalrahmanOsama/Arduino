#include <LiquidCrystal_I2C.h>
#include <DHT.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN A1
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//pins setup
int buzzer = 2;
int redled = 3;
int greenled = 5;
int blueled = 6;
int relay1 = 13;
int relay2 = 12;

int smokesensor = A0;
int dht11sensor = A1;
int moistsensor = A2;
int ldrsensor = A3;

//variables
int smokevalue;
int tempvalue;
int humidvalue;
int moistvalue;
int lightvalue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();

  pinMode(smokesensor, INPUT);
  pinMode(dht11sensor, INPUT);
  pinMode(moistsensor, INPUT);
  pinMode(ldrsensor, INPUT);

  pinMode(buzzer, OUTPUT);
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(blueled, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);

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
  // put your main code here, to run repeatedly:

  // //smoke
  // smokevalue = analogRead(smokesensor);
  // Serial.print("Sensor Value: ");
  // Serial.println(smokevalue);
  // if (smokevalue > 200)
  // {
  //   Serial.print("SMOKE DETECTED!!!!!!!!!!!!!!!!!!!!");
  //   digitalWrite(buzzer, HIGH);
  //   tone(buzzer,494,500);

  //   lcd.clear();
  //   lcd.setCursor(0, 0);
  //   lcd.print("WARNING");
  //   lcd.setCursor(1, 0);
  //   lcd.print("GAS DETECTED!");
  // }
  // else
  // {
  //   digitalWrite(buzzer, LOW);
  // }
  // delay(2000);

  //temperature & humidity
  delay(2000);  // Wait for 2 seconds between measurements
  float temperature = dht.readTemperature(); // Read temperature in Celsius
  float humidity = dht.readHumidity();       // Read humidity
  if (isnan(temperature) || isnan(humidity)) 
    {
      Serial.println("Failed to read from DHT sensor!");
    } 
  else 
    {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("H:");
    lcd.print(humidity);
    lcd.setCursor(0, 8);
    lcd.print("T:");
    lcd.print(temperature);
    }

  //moisture
  int moistvalue = analogRead(moistsensor);
  Serial.println(moistvalue);
  if (moistvalue > 950) {
    digitalWrite(relay1, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Water Pump is ON ");
  } else {
    digitalWrite(relay1, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Water Pump is OFF");
  }
  if (moistvalue < 300) {
    lcd.setCursor(0, 0);
    lcd.print("M:HIGH");
  } else if (moistvalue > 300 && moistvalue < 950) {
    lcd.setCursor(0, 0);
    lcd.print("M:MEDIUM ");
  } else if (moistvalue > 950) {
    lcd.setCursor(0, 0);
    lcd.print("M:LOW ");
  }

  //Light
  int lightvalue = analogRead(ldrsensor);
  if (lightvalue <= 100)
  {
    digitalWrite(relay2, HIGH);
    Serial.print("Light Value: ");
    Serial.println(lightvalue);
    delay(100);
  }
  else
  {
    digitalWrite(relay2, LOW);
  }

}
