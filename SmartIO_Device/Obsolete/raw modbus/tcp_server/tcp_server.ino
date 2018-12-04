#include <ESP8266WiFi.h>
#include "ESPSetup/ESPSetup.h"

WiFiServer esp_server(502);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(50);
  doAfterTurnOnESP(500);

  esp_server.begin();
  delay(1);
  Serial.printf("Web server started, open %s in a web brower \n\r", WiFi.localIP().toString().c_str());
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient new_client = esp_server.available();
  if(new_client)
  {
    new_client.setTimeout(100);
    
    Serial.println("Client connected !!!");
    while(new_client.connected())
    { 
      if(new_client.available())
      {
        // flush Serial ----------------------------
        while(Serial.available() > 0)
        {
          Serial.read();
        }
        // flush Serial ----------------------------

        // get tcp data if it's available -------------------------
        while(new_client.available())
        {
          String temp_str = new_client.readString();
          
          // pass tcp data to Serial
          Serial.print(temp_str);
        }
        // get tcp data if it's available -------------------------

        // wait Serial for 1 second -------------------------------
        int timeout = 1000;
        for(int i = 0; (!(Serial.available() > 0)); i++)
        {
          if(i > timeout)
          {
            Serial.println("TIMEOUT");
            break;
          }
          delay(1);
        }
        // wait Serial for 1 second -------------------------------

        // get Serial data if it's available --------------------------
        if(Serial.available() > 0)
        {
          String temp_str = Serial.readString();

          // pass Serial data to tcp
          new_client.print(temp_str);
        }
        // get Serial data if it's available --------------------------
      }
    }

    new_client.stop();
    Serial.println("Client stop !!!");   
  }


  // get command from arduino -------------------------------------
  if(Serial.available() > 0)
  {
    String temp_str = Serial.readString();

    // reset esp if received reset message ----------
    if(temp_str == "RESET")
    {
      ESP.restart();
    }
    // reset esp if received reset message ----------
  }
  // get command from arduino -------------------------------------
}
