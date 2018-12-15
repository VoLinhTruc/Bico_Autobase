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

#define ESP_POLLING_TIMEOUT 7000
long last_esp_polling = 0;

void setup() {
  // put your setup code here, to run once:
  master.begin(9600);
  slave.begin(9600);

  pinMode(ESP_RESET, OUTPUT);
  digitalWrite(ESP_RESET, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  updateAnalogIn(); // cap nhat gia tri analog vao thanh ghi holding
  slave.fullHanlde();

  if(millis() - last_esp_polling > ESP_POLLING_TIMEOUT)
  {
    digitalWrite(ESP_RESET, LOW);
    delay(10);
    digitalWrite(ESP_RESET, HIGH);

    last_esp_polling = millis();
  }
  
  #define POLL_INTERVAL 1000  // 1 giay poll mot lan
  static uint32_t last_time = millis();
  if((millis() - last_time) > POLL_INTERVAL)
  {
    #define PERIPHERAL_ID 1 // ID cua Slave
    #define START_ADDRESS 0 // Dia chi thanh ghi dau tien
    #define NUM_OF_REG 3  // So thanh ghi can doc
    
    master.RTUSoftSerialReadInputRegistersRequest(PERIPHERAL_ID, 1000, NUM_OF_REG);  // poll
    #define DELAY_DEPEND_ON_PERIPHERAL 50 // in millis
    delay(DELAY_DEPEND_ON_PERIPHERAL); // cho slave phan hoi lai
  
    if(master.available())
    {
      register_t temp_reg[NUM_OF_REG];  // tao mang tam thoi
      master.RTUSoftSerialGetReadInputRegistersValue(temp_reg); // lay gia tri cac thanh ghi vua nhan duoc tu slave dua vao cac thanh ghi tam thoi
  
      for(uint8_t i = 0; i < NUM_OF_REG; i++)
      {
        slave_analog_output_holding_register_list[0 + i] = temp_reg[i];
      }
    }

    //--------------------------------------
    delay(100);
    //--------------------------------------
    
    master.RTUSoftSerialReadHoldingRegistersRequest(PERIPHERAL_ID, 0, NUM_OF_REG);  // poll
    delay(DELAY_DEPEND_ON_PERIPHERAL); // cho slave phan hoi lai
  
    if(master.available())
    {
      register_t temp_reg[NUM_OF_REG];  // tao mang tam thoi
      master.RTUSoftSerialGetReadHoldingRegistersValue(temp_reg); // lay gia tri cac thanh ghi vua nhan duoc tu slave dua vao cac thanh ghi tam thoi
  
      for(uint8_t i = 0; i < NUM_OF_REG; i++)
      {
        slave_analog_output_holding_register_list[10 + i] = temp_reg[i];
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
  slave_analog_output_holding_register_list[4] = analogRead(AI0)*(20-4)/1024 + 4;
  slave_analog_output_holding_register_list[5] = analogRead(AI1)*(20-4)/1024 + 4;
  
  slave_analog_output_holding_register_list[6] = analogRead(AI0);
  slave_analog_output_holding_register_list[7] = analogRead(AI1);
}

void serialEvent() 
{
  last_esp_polling = millis();
}
