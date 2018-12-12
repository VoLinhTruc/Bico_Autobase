#define DI0 7 
#define DI1 6 
#define DI2 5 
#define DI3 4 

// OUTPUT active as low level
// OUTPUT tich cuc muc thap
#define DO0 14 // A0
#define DO1 15 // A1
#define DO2 16 // A2
#define DO3 17 // A3

#define AI0 A6
#define AI1 A7

#define AO0 10
#define AO1 9

#define ESP_RESET A5

#include "Arduino_Master_RTU_Soft_Serial.h"
#include "Arduino_Slave_RTU_Serial.h"

Arduino_Master_RTU_Soft_Serial master(2,3);
Arduino_Slave_RTU_Serial slave;

void setup() {
  // put your setup code here, to run once:
  master.begin(9600);
  slave.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  updateAnalogIn(); // cap nhat gia tri analog vao thanh ghi holding
  slave.fullHanlde();

  
  #define POLL_INTERVAL 1000  // 1 giay poll mot lan
  static uint32_t last_time = millis();
  if((millis() - last_time) > POLL_INTERVAL)
  {
    #define PERIPHERAL_ID 1 // ID cua Slave
    #define START_ADDRESS 0 // Dia chi thanh ghi dau tien
    #define NUM_OF_REG 3  // So thanh ghi can doc
    master.RTUSoftSerialReadInputRegistersRequest(PERIPHERAL_ID, START_ADDRESS, NUM_OF_REG);  // poll
    delay(2); // chi slave phan hoi lai
  
    if(master.available())
    {
      register_t temp_reg[NUM_OF_REG];  // tao mang tam thoi
      master.RTUSoftSerialGetReadHoldingRegistersValue(temp_reg); // lay gia tri cac thanh ghi vua nhan duoc tu slave dua vao cac thanh ghi tam thoi
  
      #define FIRST_LOCATION_FOR_PERIPHERAL_REG 0
      for(uint8_t i = 0; i < NUM_OF_REG; i++)
      {
        slave_analog_output_holding_register_list[FIRST_LOCATION_FOR_PERIPHERAL_REG + i] = temp_reg[i];
      }
    }

    last_time = millis();
  }

// Doan code duoi day la de hien thi gia tri cua 10 thanh holding 0-10 ra Monitor cho de kiem tra
//
//  #define POLL_INTERVAL_1 1000
//  static uint32_t last_time_1 = millis();
//  if((millis() - last_time_1) > POLL_INTERVAL_1)
//  {
//    Serial.println();
//    for(uint8_t i = 0; i < 10; i++)
//    {
//      Serial.print(i);
//      Serial.print(": ");
//      Serial.println(slave_analog_output_holding_register_list[i]);
//    }
//    Serial.println();
//
//    last_time_1 = millis();
//  }
}



void updateAnalogIn()
{
  #define LOCATION_FOR_ANALOG_INPUT_0 4
  #define LOCATION_FOR_ANALOG_INPUT_1 5
  slave_analog_output_holding_register_list[LOCATION_FOR_ANALOG_INPUT_0] = analogRead(AI0);
  slave_analog_output_holding_register_list[LOCATION_FOR_ANALOG_INPUT_1] = analogRead(AI1);
}
