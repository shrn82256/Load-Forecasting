#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "abcd";
const char *password = "abcdefgh";

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

      HTTPClient http;

      String base_url = "http://000.asisodia.com/tarp/";
      String user = "aryan3";

      http.begin(get_url(base_url, user, temp, load));

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

String get_url(String base_url, String user, float temperature, float load)
{
  return base_url + "?user=" + user + "&temperature=" + String(temperature) + "&load=" + String(load);
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
