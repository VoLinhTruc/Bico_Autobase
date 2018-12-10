#include <SoftwareSerial.h>

SoftwareSerial my_soft(2,3);

#define ESP_RESET A5
#define ESP_POLLING_TIMEOUT 7000
long last_esp_polling = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  my_soft.begin(9600);
  pinMode(ESP_RESET, OUTPUT);
  digitalWrite(ESP_RESET, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0)
  {
    while(Serial.available() > 0)
    {
      my_soft.write(Serial.read());
    }
  }

  if(my_soft.available() > 0)
  {
    while(my_soft.available() > 0)
    {
      Serial.write(my_soft.read());
    }
  }

  if(millis() - last_esp_polling > ESP_POLLING_TIMEOUT)
  {
    digitalWrite(ESP_RESET, LOW);
    delay(10);
    digitalWrite(ESP_RESET, HIGH);

    last_esp_polling = millis();
  }
}

void serialEvent() 
{
  last_esp_polling = millis();
}
