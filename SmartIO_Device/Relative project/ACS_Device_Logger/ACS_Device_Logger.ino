#include "Arduino_Slave_RTU_Serial.h"
#include "Bico_Check_Bit_Change.h"

#define DI0 10
#define DI1 9
#define DI2 8
#define DI3 7

#define DO0 12
#define DO1 11
#define DO2 3
#define DO3 2

#define AO0 7
#define AO1 6

#define RTD0 A6
#define RTD1 A7

#define ESP_RESET 4

Arduino_Slave_RTU_Serial modbus;

#define ESP_POLLING_TIMEOUT 5000
long last_esp_polling = 0;

void setup() {
  // put your setup code here, to run once:
  modbus.begin(9600);
  IOSetup();
  pinMode(ESP_RESET, OUTPUT);
  digitalWrite(ESP_RESET, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  modbus.fullHanlde();
  IOUpdate();
  updateAnalogIn();

//  if(millis() - last_esp_polling > ESP_POLLING_TIMEOUT)
//  {
//    digitalWrite(ESP_RESET, LOW);
//    delay(10);
//    digitalWrite(ESP_RESET, HIGH);
//
//    last_esp_polling = millis();
//  }


  #define INPUT_0 getBitFromArray(slave_discrete_input_contact_list, 0)
  #define INPUT_1 getBitFromArray(slave_discrete_input_contact_list, 1)
  #define INPUT_2 getBitFromArray(slave_discrete_input_contact_list, 2)
  #define INPUT_3 getBitFromArray(slave_discrete_input_contact_list, 3)
  String host = "bicotruc.000webhostapp.com";
  
  static Bico_Check_Bit_Change input_0(INPUT_0);
  uint8_t changing_type_0 = input_0.isChanging(INPUT_0);
  if(changing_type_0 == RISING)
  {
    delay(20);
    pushRequest(host, 1, 1);
  }
  if(changing_type_0 == FALLING)
  {
    delay(20);
    pushRequest(host, 1, 0);
  }


  static Bico_Check_Bit_Change input_1(INPUT_1);
  uint8_t changing_type_1 = input_1.isChanging(INPUT_1);
  if(changing_type_1 == RISING)
  {
    delay(20);
    pushRequest(host, 2, 1);
  }
  if(changing_type_1 == FALLING)
  {
    delay(20);
    pushRequest(host, 2, 0);
  }
  

  static Bico_Check_Bit_Change input_2(INPUT_2);
  uint8_t changing_type_2 = input_2.isChanging(INPUT_2);
  if(changing_type_2 == RISING)
  {
    delay(20);
    pushRequest(host, 3, 1);
  }
  if(changing_type_2 == FALLING)
  {
    delay(20);
    pushRequest(host, 3, 0);
  }
  

  static Bico_Check_Bit_Change input_3(INPUT_3);
  uint8_t changing_type_3 = input_3.isChanging(INPUT_3);
  if(changing_type_3 == RISING)
  {
    delay(20);
    pushRequest(host, 4, 1);
  }
  if(changing_type_3 == FALLING)
  {
    delay(20);
    pushRequest(host, 4, 0);
  }
  

//  static long last_time = millis();
//  if(millis() - last_time > 10)
//  {
//    slave_analog_output_holding_register_list[0]+=2;
//    slave_analog_output_holding_register_list[1]+=3;
//    slave_analog_output_holding_register_list[2]+=4;
//    slave_analog_output_holding_register_list[3]+=5;
//    slave_analog_output_holding_register_list[4]+=6;
//    slave_analog_output_holding_register_list[5]+=2;
//    slave_analog_output_holding_register_list[6]+=3;
//    slave_analog_output_holding_register_list[7]+=4;
//    slave_analog_output_holding_register_list[8]+=5;
//    slave_analog_output_holding_register_list[9]+=6;
//    last_time = millis();
//  }

}













void pushRequest(String host, uint8_t input, uint8_t value)
{
  String uri = "/subm.php?";
    uri += "INP="; uri += String(input);
    uri += "&";
    uri += "STA="; uri += String(value);
  String full_uri =
  String("GET ") + uri + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n";

  Serial.println(full_uri);
}












void IOSetup()
{
  pinMode(DI0, INPUT);
  pinMode(DI1, INPUT);
  pinMode(DI2, INPUT);
  pinMode(DI3, INPUT);

  pinMode(DO0, OUTPUT);
  pinMode(DO1, OUTPUT);
  pinMode(DO2, OUTPUT);
  pinMode(DO3, OUTPUT);
}

void IOUpdate()
{
  setBitToArray(slave_discrete_input_contact_list, 0, digitalRead(DI0));
  setBitToArray(slave_discrete_input_contact_list, 1, digitalRead(DI1));
  setBitToArray(slave_discrete_input_contact_list, 2, digitalRead(DI2));
  setBitToArray(slave_discrete_input_contact_list, 3, digitalRead(DI3));

  digitalWrite(DO0, getBitFromArray(slave_discrete_output_coil_list, 0));
  digitalWrite(DO1, getBitFromArray(slave_discrete_output_coil_list, 1));
  digitalWrite(DO2, getBitFromArray(slave_discrete_output_coil_list, 2));
  digitalWrite(DO3, getBitFromArray(slave_discrete_output_coil_list, 3));
}

void updateAnalogIn()
{
  slave_analog_output_holding_register_list[6] = analogRead(RTD0);
  slave_analog_output_holding_register_list[7] = analogRead(RTD1);
}


void serialEvent() 
{
  last_esp_polling = millis();
}
