#include "ArduinoJson.h"
#include "Bico_Pin_State_Change.h"

#define DEBUG 0

#define ACTIVE_CHANGING_STATE RISING
#define DEACTIVE_CHANGING_STATE FALLING
#define ACTIVE_STATE HIGH
#define DEACTIVE_STATE LOW

#define DI0 4
#define DI1 5
#define DI2 6
#define DI3 7

#define AI0 A6
#define AI1 A7

#define DO0 A0
#define DO1 A1
#define DO2 A2
#define DO3 A3

/***********************************
Bico_Pin_State_Change DI0_pin;
Bico_Pin_State_Change DI1_pin;
Bico_Pin_State_Change DI2_pin;
Bico_Pin_State_Change DI3_pin;
***********************************/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  Serial.setTimeout(100);

  pinMode(DO0, OUTPUT);
  pinMode(DO1, OUTPUT);
  pinMode(DO2, OUTPUT);
  pinMode(DO3, OUTPUT);

  digitalWrite(DO0, DEACTIVE_STATE);
  digitalWrite(DO1, DEACTIVE_STATE);
  digitalWrite(DO2, DEACTIVE_STATE);
  digitalWrite(DO3, DEACTIVE_STATE);

  pinMode(DI0, INPUT);
  pinMode(DI1, INPUT);
  pinMode(DI2, INPUT);
  pinMode(DI3, INPUT);

/***********************************
  DI0_pin.begin(DI0, INPUT);
  DI1_pin.begin(DI1, INPUT);
  DI2_pin.begin(DI2, INPUT);
  DI3_pin.begin(DI3, INPUT);
***********************************/

}

void loop() {
  // put your main code here, to run repeatedly:
  static String ESP8266_say = "";

  if(Serial.available() > 0)
  {
    ESP8266_say = Serial.readString();
  }

  //Uart detect incomming data--------------------------------------------------------
  if((ESP8266_say.indexOf("Free") == -1) && (ESP8266_say != ""))
  {
    String received_str = ESP8266_say;

    //Create Json Object-------------------------------------
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(received_str);
    //-------------------------------------------------------

  
    //Get data from Json Object------------------------------
    uint8_t relay0_state = root["RELAY0"];
    uint8_t relay1_state = root["RELAY1"];
    uint8_t relay2_state = root["RELAY2"];
    uint8_t relay3_state = root["RELAY3"];
    //-------------------------------------------------------


    //Routines after get data--------------------------------
    digitalWrite(DO0, relay0_state);
    digitalWrite(DO1, relay1_state);
    digitalWrite(DO2, relay2_state);
    digitalWrite(DO3, relay3_state);

    ESP8266_say = "";

    #if DEBUG == 1
    Serial.print(relay0_state);
    Serial.print('\t');
    Serial.print(relay1_state);
    Serial.print('\t');
    Serial.print(relay2_state);
    Serial.print('\t');
    Serial.print(relay3_state);
    Serial.println();
    #endif // DEBUG == 1
    //-------------------------------------------------------
  }
  //------------------------------------------------------------------------------------


  //Usual routines----------------------------------------------------------------------
  if(ESP8266_say.indexOf("Free") != -1)
  {
    static const String url = "http://bicotruc.000webhostapp.com/SmartIO/regular_request_handling.php/";
    static const String device_name = "SmartIO_01";
  
    uint8_t input0 = digitalRead(DI0);
    uint8_t input1 = digitalRead(DI1);
    uint8_t input2 = digitalRead(DI2);
    uint8_t input3 = digitalRead(DI3);
    int analog1 = analogRead(AI1);
    
    Serial.print(url);
    Serial.print('?');
    Serial.print("DEVICE_NAME="+String("%22")+device_name+"%22");
    Serial.print('&');
    Serial.print("INPUT0="+String(input0));
    Serial.print('&');
    Serial.print("INPUT1="+String(input1));
    Serial.print('&');
    Serial.print("INPUT2="+String(input2));
    Serial.print('&');
    Serial.print("INPUT3="+String(input3));
    Serial.print('&');
    Serial.print("ANALOG1="+String(analog1));
    Serial.println();

    ESP8266_say = "";
  }
  

  
  /*******************************************************************************
  //Get the changing state of DIx
  uint8_t DI0_state_change = DI0_pin.isChanging();
  uint8_t DI1_state_change = DI1_pin.isChanging();
  uint8_t DI2_state_change = DI2_pin.isChanging();
  uint8_t DI3_state_change = DI3_pin.isChanging();

  
  //Executed routine when the DI0's state change--------------------------
  if(DI0_state_change == ACTIVE_CHANGING_STATE)
  {
    String data_builder = "?DEVICE_NAME=%22SmartIO_01%22&INPUT_PIN=%22DI0%22&STATE="+String(ACTIVE_STATE);
    
    Serial.print("http://");
    Serial.print(host);
    Serial.println(data_builder);
    
    #if DEBUG == 1
    Serial.println("DI0 ACTIVE");
    #endif // DEBUG == 1
  }
  else if(DI0_state_change == DEACTIVE_CHANGING_STATE) 
  {
    String data_builder = "?DEVICE_NAME=%22SmartIO_01%22&INPUT_PIN=%22DI0%22&STATE="+String(DEACTIVE_STATE);
    
    Serial.print("http://");
    Serial.print(host);
    Serial.println(data_builder);
    
    #if DEBUG == 1
    Serial.println("DI0 DEACTIVE");
    #endif // DEBUG == 1
  }
  //----------------------------------------------------------------------

  
  //Executed routine when the DI1's state change--------------------------
  if(DI1_state_change == ACTIVE_CHANGING_STATE)
  {
    String data_builder = "?DEVICE_NAME=%22SmartIO_01%22&INPUT_PIN=%22DI1%22&STATE="+String(ACTIVE_STATE);
    
    Serial.print("http://");
    Serial.print(host);
    Serial.println(data_builder);
    
    #if DEBUG == 1
    Serial.println("DI1 ACTIVE");
    #endif // DEBUG == 1
  }
  else if(DI1_state_change == DEACTIVE_CHANGING_STATE) 
  {
    String data_builder = "?DEVICE_NAME=%22SmartIO_01%22&INPUT_PIN=%22DI1%22&STATE="+String(DEACTIVE_STATE);
    
    Serial.print("http://");
    Serial.print(host);
    Serial.println(data_builder);
    
    #if DEBUG == 1
    Serial.println("DI1 DEACTIVE");
    #endif // DEBUG == 1
  }
  //----------------------------------------------------------------------


  //Executed routine when the DI2's state change--------------------------
  if(DI2_state_change == ACTIVE_CHANGING_STATE)
  {
    String data_builder = "?DEVICE_NAME=%22SmartIO_01%22&INPUT_PIN=%22DI2%22&STATE="+String(ACTIVE_STATE);
    
    Serial.print("http://");
    Serial.print(host);
    Serial.println(data_builder);
    
    #if DEBUG == 1
    Serial.println("DI2 ACTIVE");
    #endif // DEBUG == 1
  }
  else if(DI2_state_change == DEACTIVE_CHANGING_STATE) 
  {
    String data_builder = "?DEVICE_NAME=%22SmartIO_01%22&INPUT_PIN=%22DI2%22&STATE="+String(DEACTIVE_STATE);
    
    Serial.print("http://");
    Serial.print(host);
    Serial.println(data_builder);
    
    #if DEBUG == 1
    Serial.println("DI2 DEACTIVE");
    #endif // DEBUG == 1
  }
  //----------------------------------------------------------------------


  //Executed routine when the DI3's state change--------------------------
  if(DI3_state_change == ACTIVE_CHANGING_STATE)
  {
    String data_builder = "?DEVICE_NAME=%22SmartIO_01%22&INPUT_PIN=%22DI3%22&STATE="+String(ACTIVE_STATE);
    
    Serial.print("http://");
    Serial.print(host);
    Serial.println(data_builder);
    
    #if DEBUG == 1
    Serial.println("DI3 ACTIVE");
    #endif // DEBUG == 1
  }
  else if(DI3_state_change == DEACTIVE_CHANGING_STATE) 
  {
    String data_builder = "?DEVICE_NAME=%22SmartIO_01%22&INPUT_PIN=%22DI3%22&STATE="+String(DEACTIVE_STATE);
    
    Serial.print("http://");
    Serial.print(host);
    Serial.println(data_builder);
    
    #if DEBUG == 1
    Serial.println("DI3 DEACTIVE");
    #endif // DEBUG == 1
  }
  //----------------------------------------------------------------------
  *******************************************************************************/
  
  //------------------------------------------------------------------------------------
}
