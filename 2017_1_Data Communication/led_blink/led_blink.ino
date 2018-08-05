const int ledPin=13;
int blinkRate=0;

void blink()
{
  digitalWrite(ledPin,HIGH);
  delay(blinkRate);
  digitalWrite(ledPin,LOW);
  delay(blinkRate);
}

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
}

void loop()
{
  if(Serial.available()){
    char ch=Serial.read();
    if(isDigit(ch))
    {
      blinkRate=(ch-'0');
      blinkRate=blinkRate*100;
    }
  }
  blink();
}

