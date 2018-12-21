#include <ESP8266WiFi.h>

// Station properties -----------------------------
const char ssid[] = "kim long";
const char pwd[] = "88888888";

IPAddress ip(192, 168, 1, 20);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
// Station properties -----------------------------

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(100);
  delay(10);

  // Turn on station ----------------------------------------------------
  WiFi.softAPdisconnect(true);
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  delay(100);
  
  Serial.println();

  //WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, pwd);
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(500);
  }
  Serial.println();
  Serial.printf("Connected to %s \r\n", ssid);
  Serial.printf("Static IP: %s\r\n", ip.toString().c_str());
  // Turn on station ----------------------------------------------------
    
}

void loop() {  
  if(Serial.available() > 0)
  {
    String full_uri = Serial.readString();
  
    WiFiClient client;
    uint8_t start_of_host = full_uri.indexOf("Host: ") + String("Host: ").length();
    uint8_t end_of_host = full_uri.indexOf("\r\n", start_of_host);
    String host = full_uri.substring(start_of_host, end_of_host);
    const int httpPort = 80;
    
    if (!client.connect(host, httpPort)) {
      return;
    }
    
    client.print(full_uri);
                 
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        client.stop();
        return;
      }
    }
  }
}
