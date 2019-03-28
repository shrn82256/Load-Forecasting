#include <SoftwareSerial.h>
SoftwareSerial mySerial(0, 1);

int temp;
String str;

#define N 8
int led[N] = {2, 3, 4, 5, 6, 7, 8, 9};
bool led_status[N] = {0, 0, 0, 0, 0, 0, 0, 0};

int load_value[N] = {10000, 15000, 20000, 25000, 25000, 20000, 15000, 10000};

void setup()
{

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

  temp = 32;
  str = String('T') + String(temp) + String('L') + String(getLoad());

  Serial.println(str);
  mySerial.println(str);

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

    led_status[i] = status;
  }
}

int getLoad()
{
  int total_load = 0;

  for (int i = 0; i < N; i++)
    if (led_status[i])
      total_load += load_value[i];

  return total_load;
}