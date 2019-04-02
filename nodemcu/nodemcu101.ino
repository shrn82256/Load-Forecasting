#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "abcd";
const char *password = "abcdefgh";

#include <dht.h>
#define DHT11_PIN A0
dht DHT;

#define WHITE_LED_PIN 4

bool loadFlag = false;
bool tempFlag = false;

int load = 0;
int temp = 0;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  pinMode(WHITE_LED_PIN, OUTPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {

    delay(1000);
    Serial.println("Connecting..");
    // blink_led(RED_LED_PIN);
  }
  Serial.println("Connected");
}

void loop()
{ // run over and over
  if (Serial.available() && WiFi.status() == WL_CONNECTED)
  {
    char ch = Serial.read();
    if (ch == 'T')
    {
      loadFlag = false;
      tempFlag = true;
      temp = 0;
    }
    else if (ch == 'L')
    {
      loadFlag = true;
      tempFlag = false;
      load = 0;
    }
    else if (ch >= '0' && ch <= '9')
    {
      if (loadFlag)
      {
        load = load * 10 + ch - '0';
      }
      else if (tempFlag)
      {
        temp = temp * 10 + ch - '0';
      }
    }
    else if (ch == '\n' && temp != 0 && load != 0)
    {
      Serial.print("T:");
      Serial.print(temp);
      Serial.print("\tL:");
      Serial.println(load);

      temp = DHT.temperature;

      HTTPClient http;

      String url = get_url(user, temp, load);

      http.begin(url);
      Serial.println(url);

      int httpCode = http.GET();

      if (httpCode > 0)
      {
        blink_led(WHITE_LED_PIN);

        String payload = http.getString();
        Serial.println(payload);
      }
      http.end();
    }
  }
}

void blink_led(int ledPinNumber)
{
  digitalWrite(ledPinNumber, HIGH);
  delay(500);
  digitalWrite(ledPinNumber, LOW);
  delay(500);
  digitalWrite(ledPinNumber, HIGH);
  delay(500);
  digitalWrite(ledPinNumber, LOW);
}

String get_url(String user, int temp, int load)
{
  return "http://minimal-pile.000webhostapp.com/seqload?user=" + user + "&temp=" + String(temp) + "&load=" + String(load);
}
