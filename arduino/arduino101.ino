#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);

int temp;
String str;

#define N 8
int led[N] = {2, 3, 4, 5, 6, 7, 8, 9};
bool led_status[N] = {0, 0, 0, 0, 0, 0, 0, 0};

int load_value[N] = {1000, 1500, 2000, 2500, 2500, 2000, 1500, 1000};

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
  delay(10000);
}

void updateLed(int i, bool status)
{
  digitalWrite(led[i], status);

  led_status[i] = status;
}

void updateLeds(bool status)
{
  for (int i = 0; i < N; i++)
    updateLed(i, status);
}

int getLoad()
{
  int total_load = 0;

  for (int i = 0; i < N; i++)
    if (led_status[i])
      total_load += load_value[i];

  return total_load;
}