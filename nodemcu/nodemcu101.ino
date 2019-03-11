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
}

void loop()
{ // run over and over
  if (Serial.available())
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
    else if (ch == '\n')
    {
      Serial.print("T:");
      Serial.print(temp);
      Serial.print("\tL:");
      Serial.println(load);
    }
    // Serial.print(":");
    // Serial.print();
  }
}