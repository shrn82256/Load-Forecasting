#include <SoftwareSerial.h>
SoftwareSerial mySerial(6, 7);

/* #include <LiquidCrystal.h>
LiquidCrystal lcd(11, 12, 5, 4, 3, 2); */

#include <dht.h>
#define DHT11_PIN A0
dht DHT;

int temp, humi;
String str;

void setup()
{
  /* lcd.begin(16, 2);
  lcd.setCursor(0, 0); */

  Serial.begin(115200);
  mySerial.begin(115200);
  delay(2000);
}
void loop()
{
  DHT.read11(DHT11_PIN);
  humi = DHT.humidity;
  temp = DHT.temperature;
  str = String('T') + String(temp) + String('L') + String(humi * 10);
  Serial.println(str);
  mySerial.println(str);

  /* lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(str); */
  delay(5000);
}