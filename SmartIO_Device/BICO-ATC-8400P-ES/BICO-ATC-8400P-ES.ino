#include "Arduino_Slave_IP_Soft_Serial.h"

#define DI0 14 // A0
#define DI1 15 // A1
#define DI2 16 // A2
#define DI3 17 // A3
#define DI4 18 // A4
#define DI5 19 // A5
#define DI6 5 // 5
#define DI7 4 // 4

// OUTPUT active as low level
// OUTPUT tich cuc muc thap
#define DO0 9
#define DO1 8
#define DO2 7
#define DO3 6

#define soft_rx 2
#define soft_tx 3
Arduino_Slave_IP_Soft_Serial modbus(2, 3);

void setup() {
  // put your setup code here, to run once:
  modbus.begin(9600);
  IOSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  modbus.fullHanlde();
  IOUpdate();
  

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
  setBitToArray(slave_discrete_input_contact_list, 4, digitalRead(DI4));
  setBitToArray(slave_discrete_input_contact_list, 5, digitalRead(DI5));
  setBitToArray(slave_discrete_input_contact_list, 6, digitalRead(DI6));
  setBitToArray(slave_discrete_input_contact_list, 7, digitalRead(DI7));

  digitalWrite(DO0, getBitFromArray(slave_discrete_output_coil_list, 0));
  digitalWrite(DO1, getBitFromArray(slave_discrete_output_coil_list, 1));
  digitalWrite(DO2, getBitFromArray(slave_discrete_output_coil_list, 2));
  digitalWrite(DO3, getBitFromArray(slave_discrete_output_coil_list, 3));
}
