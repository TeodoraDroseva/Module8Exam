//Libraries.
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

//Constants.
#define DHTPIN 3
#define DHTYPE DHT22
LiquidCrystal_I2C lcd (0x23, 16, 2);
DHT dht(DHTPIN, DHTYPE);

//Variables.
byte celsius[] = { 0x0E, 0x11, 0x10, 0x10, 0x10, 0x10, 0x11, 0x0E };
byte degree[] = { 0x1C, 0x14, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00 };
byte droplet[] = { 0x04, 0x04, 0x0A, 0x0A, 0x11, 0x11, 0x11, 0x0E };
byte percentage[] = { 0x18, 0x19, 0x02, 0x04, 0x08, 0x13, 0x03, 0x00 };
byte thermostat[] = { 0x04, 0x0A, 0x0A, 0x0E, 0x0E, 0x1F, 0x1F, 0x0E };

void setup() 
{
  Serial.begin(9600);
   
  //Initialize the LCD.
  lcd.init();
  lcd.backlight();

  //Add custom characters.
  lcd.createChar(0, celsius);
  lcd.createChar(1, degree);
  lcd.createChar(2, droplet);
  lcd.createChar(3, percentage);
  lcd.createChar(4, thermostat);

  //Start DHT.
  dht.begin();
  //Use digital 5V to power DHT sensor.
  digitalWrite(7, HIGH);

  //Second row character positioning.
  //blankSpace = " ";
  //" ", thermostat, " ", " ", " ", degree, celsius, " ", " ", " ", droplet, " ", " ", " ", percentage, " ".
  //Position of thermostat character.
  lcd.setCursor(1,1);
  lcd.write(4);

  //Position of degree character.
  lcd.setCursor(5,1);
  lcd.write(1);

  //Position of celsius character.
  lcd.setCursor(6,1);
  lcd.write(0);

  //Position of droplet character.
  lcd.setCursor(10,1);
  lcd.write(2);

  //Position of percentage character.
  lcd.setCursor(14,1);
  lcd.write(3);
}

void loop() 
{
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  //Print values to serial monitor.
  Serial.print("TMP=");
  Serial.print(t);
  Serial.print(";HMD=");
  Serial.print(h);
  Serial.print("<cr>\n");

  //Print values to LCD.
  if(!isnan(t))
  {
    if(t < 10)
    {
      lcd.setCursor(4,1);
    }

    if(t >= 10)
    {
      lcd.setCursor(3,1);
    }

    if(t >= 100)
    {
      lcd.setCursor(2,1);
    }
    
    lcd.print(String((int)t));
  }

  if(!isnan(h))
  {
    if(h < 10)
    {
      lcd.setCursor(13,1);
    }

    if(h >= 10)
    {
      lcd.setCursor(12,1);
    }

    if(h >= 100)
    {
      lcd.setCursor(11,1);
    }
    
    lcd.print(String((int)h));
  }

  delay(10000);
}
