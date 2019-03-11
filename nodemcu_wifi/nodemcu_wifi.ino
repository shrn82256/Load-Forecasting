#include <dht.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

dht DHT;
const char *ssid = "abcd";
const char *password = "abcdefgh";

#define DHT11_PIN 2
#define RED_LED_PIN 15
#define WHITE_LED_PIN 13
#define GREEN_LED_PIN 14

void setup()
{
  Serial.begin(115200);

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(WHITE_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {

    delay(1000);
    Serial.println("Connecting..");
    blink_led(RED_LED_PIN);
  }
  Serial.println("Connected");
}

float prev_temperature = -999;
float prev_humidity = -999;

void loop()
{

  if (WiFi.status() == WL_CONNECTED)
  {

    HTTPClient http;
    DHT.read11(DHT11_PIN);

    String base_url = "http://000.asisodia.com/tarp/";
    String user = "aryan2";

    float temperature = DHT.temperature;
    float humidity = DHT.humidity;

    if (temperature == -999 || humidity == -999 || (temperature == prev_temperature && humidity == prev_humidity))
    {
      blink_led(RED_LED_PIN);
      return;
    }
    else
    {
      blink_led(GREEN_LED_PIN);
    }

    Serial.print("Temperature = ");
    Serial.println(temperature);
    Serial.print("Humidity = ");
    Serial.println(humidity);
    http.begin(get_url(base_url, user, temperature, humidity));

    int httpCode = http.GET();

    if (httpCode > 0)
    {
      blink_led(WHITE_LED_PIN);

      String payload = http.getString();
      Serial.println(payload);
    }
    else
    {
      blink_led(RED_LED_PIN);
    }

    http.end();

    prev_temperature = temperature;
    prev_humidity = humidity;

    delay(10000);
  }
  else
  {
    blink_led(RED_LED_PIN);

    delay(2000);
  }
}

String get_url(String base_url, String user, float temperature, float humidity)
{
  return base_url + "?user=" + user + "&temperature=" + String(temperature) + "&humidity=" + String(humidity);
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
