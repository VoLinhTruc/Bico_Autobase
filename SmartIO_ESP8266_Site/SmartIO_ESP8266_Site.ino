#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define DEBUG 0
 
const char* ssid = "Autobase VN";
const char* password = "ATC@Scada";
 
void setup () {
 
  Serial.begin(57600);
  Serial.setTimeout(200);

  WifiConnect();
  delay(1000);
  Serial.println("Free");
}
 
void loop() {

  if(WiFi.status() != WL_CONNECTED)
  {
    WifiConnect();
  }

  if(Serial.available() > 0)
  {
    String temp_str = Serial.readString();
    
    #if DEBUG == 1
    Serial.print(temp_str);
    Serial.println(temp_str.indexOf("\r\n"));
    #endif // DEBUG == 1
    
    if(temp_str.indexOf("\r\n") != -1)
    {
      temp_str.replace("\r\n", "");
      if (WiFi.status() == WL_CONNECTED) //Check WiFi connection status
      { 
        HTTPClient temp_http_client;
        temp_http_client.begin(temp_str);
        int http_response_code = temp_http_client.GET();

        #if DEBUG == 1
        Serial.println(http_response_code);
        #endif // DEBUG == 
          
        if(http_response_code > 0)
        {
          String payload = temp_http_client.getString();
          
          Serial.print(payload);

          #if DEBUG == 1
          Serial.println();
          #endif // DEBUG == 1
        }
        temp_http_client.end();
      }
    }

    delay(500);
    Serial.println("Free");
  }
}

void WifiConnect()
{
  WiFi.begin(ssid, password);

  #if DEBUG == 1
  Serial.println("Connecting !!!");
  #endif // DEBUG == 1
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    
    #if DEBUG == 1
    Serial.print(".");
    #endif // DEBUG == 1
  }
  
  #if DEBUG == 1
  Serial.println();
  #endif // DEBUG == 1
}
