// *** Luu y: board nay khong con chan de reset ESP

#include "Arduino_Slave_RTU_Serial.h"

#define DI0 11
#define DI1 10
#define DI2 9
#define DI3 8
#define DI4 7
#define DI5 6
#define DI6 5
#define DI7 4
#define DI8 3
#define DI9 2

#define DO0 12
#define DO1 13
#define DO2 14 // A0
#define DO3 15 // A1
#define DO4 16 // A2
#define DO5 17 // A3
#define DO6 18 // A4
#define DO7 19 // A5

//#define ESP_RESET 20

Arduino_Slave_RTU_Serial modbus;

#define ESP_POLLING_TIMEOUT 5000
long last_esp_polling = 0;

void setup() {
  // put your setup code here, to run once:
  modbus.begin(9600);
  IOSetup();
//  pinMode(ESP_RESET, OUTPUT);
//  digitalWrite(ESP_RESET, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  modbus.fullHanlde();
  IOUpdate();

//  if(millis() - last_esp_polling > ESP_POLLING_TIMEOUT)
//  {
//    digitalWrite(ESP_RESET, LOW);
//    delay(10);
//    digitalWrite(ESP_RESET, HIGH);
//
//    last_esp_polling = millis();
//  }

  
}


void IOSetup()
{
  pinMode(DI0, INPUT);
  pinMode(DI1, INPUT);
  pinMode(DI2, INPUT);
  pinMode(DI3, INPUT);
  pinMode(DI4, INPUT);
  pinMode(DI5, INPUT);
  pinMode(DI6, INPUT);
  pinMode(DI7, INPUT);
  pinMode(DI8, INPUT);
  pinMode(DI9, INPUT);

  pinMode(DO0, OUTPUT);
  pinMode(DO1, OUTPUT);
  pinMode(DO2, OUTPUT);
  pinMode(DO3, OUTPUT);
  pinMode(DO4, OUTPUT);
  pinMode(DO5, OUTPUT);
  pinMode(DO6, OUTPUT);
  pinMode(DO7, OUTPUT);
}

void IOUpdate()
{
  setBitToArray(slave_discrete_input_contact_list, 0, digitalRead(DI0));
  setBitToArray(slave_discrete_input_contact_list, 1, digitalRead(DI1));
  setBitToArray(slave_discrete_input_contact_list, 2, digitalRead(DI2));
  setBitToArray(slave_discrete_input_contact_list, 3, digitalRead(DI3));
  setBitToArray(slave_discrete_input_contact_list, 4, digitalRead(DI4));
  setBitToArray(slave_discrete_input_contact_list, 5, digitalRead(DI5));
  setBitToArray(slave_discrete_input_contact_list, 6, digitalRead(DI6));
  setBitToArray(slave_discrete_input_contact_list, 7, digitalRead(DI7));
  setBitToArray(slave_discrete_input_contact_list, 8, digitalRead(DI8));
  setBitToArray(slave_discrete_input_contact_list, 9, digitalRead(DI9));

  digitalWrite(DO0, getBitFromArray(slave_discrete_output_coil_list, 0));
  digitalWrite(DO1, getBitFromArray(slave_discrete_output_coil_list, 1));
  digitalWrite(DO2, getBitFromArray(slave_discrete_output_coil_list, 2));
  digitalWrite(DO3, getBitFromArray(slave_discrete_output_coil_list, 3));
  digitalWrite(DO4, getBitFromArray(slave_discrete_output_coil_list, 4));
  digitalWrite(DO5, getBitFromArray(slave_discrete_output_coil_list, 5));
  digitalWrite(DO6, getBitFromArray(slave_discrete_output_coil_list, 6));
  digitalWrite(DO7, getBitFromArray(slave_discrete_output_coil_list, 7));
}
