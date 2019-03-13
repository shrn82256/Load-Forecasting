#include <SoftwareSerial.h>
SoftwareSerial mySerial(6, 7);

/* #include <LiquidCrystal.h>
LiquidCrystal lcd(11, 12, 5, 4, 3, 2); */

#include <dht.h>
#define DHT11_PIN A0
dht DHT;

int temp;
String str;

#define N 4
int led[N] = {2, 3, 4, 5};
bool led_status[N] = {0, 0, 0, 0};

int load[N] = {8, 9, 10, 11};
bool load_status[N] = {0, 0, 0, 0};
int load_value[N] = {1000, 1500, 2000, 2500};

void setup()
{
  /* lcd.begin(16, 2);
  lcd.setCursor(0, 0); */

  Serial.begin(115200);
  mySerial.begin(115200);

  for (int i = 0; i < N; i++)
  {
    pinMode(led[i], OUTPUT);
  }

  delay(2000);
}

int j = 0, k = 1;
void loop()
{

  updateLeds(0);
  updateLed(j, 1);
  updateLed(k, 1);

  DHT.read11(DHT11_PIN);
  temp = DHT.temperature;
  str = String('T') + String(temp) + String('L') + String(getLoad());

  Serial.println(str);
  mySerial.println(str);

  /* lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(str); */

  j = (j + 1) % N;
  k = (k + 1) % N;
  delay(5000);
}

void updateLed(int i, bool status)
{
  if (status)
    digitalWrite(led[i], HIGH);
  else
    digitalWrite(led[i], LOW);

  led_status[i] = status;
}

void updateLeds(bool status)
{
  for (int i = 0; i < N; i++)
  {
    if (status)
      digitalWrite(led[i], HIGH);
    else
      digitalWrite(led[i], LOW);
  }
}

void updateLoads()
{
  for (int i = 0; i < N; i++)
    load_status[i] = digitalRead(load[i]);
}

int getLoad()
{
  updateLoads();

  int total_load = 0;

  for (int i = 0; i < N; i++)
    if (load_status[i])
      total_load += load_value[i];

  return total_load;
}