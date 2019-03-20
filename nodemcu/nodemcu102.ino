#include <LiquidCrystal_I2C.h>

#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{

  lcd.begin();

  lcd.home();

  lcd.print("Hello, NodeMCU");
}

void loop()
{
  // do nothing here
}