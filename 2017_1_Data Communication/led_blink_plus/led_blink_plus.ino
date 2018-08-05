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
char ch;
int number=0;

void loop()
{
  if(Serial.available()){
    number=0;
    while(Serial.available()){
    ch=Serial.read();
    if(isDigit(ch))
    {
      number=number*10;
      number=number+(ch-'0');
    }
  }
  blinkRate=number;
  blinkRate=blinkRate*100;
  }
  blink();
}

