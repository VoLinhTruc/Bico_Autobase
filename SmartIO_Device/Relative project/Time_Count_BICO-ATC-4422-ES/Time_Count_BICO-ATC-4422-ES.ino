// Dia chi cua cac thanh ghi, go to line 60

#include "Arduino_Slave_RTU_Serial.h"
#include "Bico_Check_Bit_Change.h"

#define DI0 5
#define DI1 4
#define DI2 3
#define DI3 2

#define DO0 9 // A0
#define DO1 8 // A1
#define DO2 7 // A2
#define DO3 6 // A3

//#define AI0 A6
//#define AI1 A7
//
//#define AO0 10
//#define AO1 9

#define ESP_RESET 13

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
  analogUpdate();

  if(millis() - last_esp_polling > ESP_POLLING_TIMEOUT)
  {
    digitalWrite(ESP_RESET, LOW);
    delay(10);
    digitalWrite(ESP_RESET, HIGH);

    last_esp_polling = millis();
  }




  #define INPUT_0 getBitFromArray(slave_discrete_input_contact_list, 0)
  #define INPUT_1 getBitFromArray(slave_discrete_input_contact_list, 1)
  #define INPUT_2 getBitFromArray(slave_discrete_input_contact_list, 2)
  #define INPUT_3 getBitFromArray(slave_discrete_input_contact_list, 3)

  #define INPUT_0_STATE_REGISTER slave_analog_output_holding_register_list[10]
  #define INPUT_1_STATE_REGISTER slave_analog_output_holding_register_list[11]
  #define INPUT_2_STATE_REGISTER slave_analog_output_holding_register_list[12]
  #define INPUT_3_STATE_REGISTER slave_analog_output_holding_register_list[13]
  
  #define COUNTING_VALUE_0 slave_analog_output_holding_register_list[0]
  #define COUNTING_VALUE_1 slave_analog_output_holding_register_list[1]
  #define COUNTING_VALUE_2 slave_analog_output_holding_register_list[2]
  #define COUNTING_VALUE_3 slave_analog_output_holding_register_list[3]

  #define TIMING_0 slave_analog_output_holding_register_list[5]
  #define TIMING_1 slave_analog_output_holding_register_list[6]
  #define TIMING_2 slave_analog_output_holding_register_list[7]
  #define TIMING_3 slave_analog_output_holding_register_list[8]


  INPUT_0_STATE_REGISTER = INPUT_0;
  INPUT_1_STATE_REGISTER = INPUT_1;
  INPUT_2_STATE_REGISTER = INPUT_2;
  INPUT_3_STATE_REGISTER = INPUT_3;

  #define IO_ACTIVE_STATE HIGH
  #define IO_DEACTIVE_STATE LOW
  static uint32_t last_active_0 = 0;
  static uint32_t last_active_1 = 0;
  static uint32_t last_active_2 = 0;
  static uint32_t last_active_3 = 0;


  static Bico_Check_Bit_Change check_couting_0_bit_change(INPUT_0);
  uint8_t changing_type_0 = check_couting_0_bit_change.isChanging(INPUT_0);
    if(changing_type_0 == RISING)
    {
      delay(10);
      COUNTING_VALUE_0++;

      TIMING_0 = 0;
      last_active_0 = millis();
    }
    if(INPUT_0 == IO_ACTIVE_STATE)
    {
      TIMING_0 = millis() - last_active_0;
    }

  static Bico_Check_Bit_Change check_couting_1_bit_change(INPUT_1);
  uint8_t changing_type_1 = check_couting_1_bit_change.isChanging(INPUT_1);
    if(changing_type_1 == RISING)
    {
      delay(10);
      COUNTING_VALUE_1++;

      TIMING_1 = 0;
      last_active_1 = millis();
    }
    if(INPUT_1 == IO_ACTIVE_STATE)
    {
      TIMING_1 = millis() - last_active_1;
    }

  static Bico_Check_Bit_Change check_couting_2_bit_change(INPUT_2);
  uint8_t changing_type_2 = check_couting_2_bit_change.isChanging(INPUT_2);
    if(changing_type_2 == RISING)
    {
      delay(10);
      COUNTING_VALUE_2++;

      TIMING_2 = 0;
      last_active_2 = millis();
    }
    if(INPUT_2 == IO_ACTIVE_STATE)
    {
      TIMING_2 = millis() - last_active_2;
    }


  static Bico_Check_Bit_Change check_couting_3_bit_change(INPUT_3);
  uint8_t changing_type_3 = check_couting_3_bit_change.isChanging(INPUT_3);
    if(changing_type_3 == RISING)
    {
      delay(10);
      COUNTING_VALUE_3++;

      TIMING_3 = 0;
      last_active_3 = millis();
    }
    if(INPUT_3 == IO_ACTIVE_STATE)
    {
      TIMING_3 = millis() - last_active_3;
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

void analogUpdate()
{
//  slave_analog_output_holding_register_list[0] = analogRead(AI0);
//  slave_analog_output_holding_register_list[1] = analogRead(AI1);
}

void serialEvent() 
{
  last_esp_polling = millis();
}
