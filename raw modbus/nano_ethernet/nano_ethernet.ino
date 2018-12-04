#include <SoftwareSerial.h>

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

SoftwareSerial rs485(2,3);

uint16_t holding_register[10];
uint16_t rs485_value_in = 0;


uint16_t ModRTU_CRC(uint8_t* buf, uint16_t len)
{
  uint16_t crc = 0xFFFF;
  
  for (uint16_t pos = 0; pos < len; pos++) {
    crc ^= (uint16_t)buf[pos];          // XOR byte into least sig. byte of crc
  
    for (uint16_t i = 8; i != 0; i--) {    // Loop over each bit
      if ((crc & 0x0001) != 0) {      // If the LSB is set
        crc >>= 1;                    // Shift right and XOR 0xA001
        crc ^= 0xA001;
      }
      else                            // Else LSB is not set
        crc >>= 1;                    // Just shift right
    }
  }
  // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
  return crc;  
}


void setup() {
  // put your setup code here, to run once:
  rs485.begin(9600);
  rs485.setTimeout(50);
  Serial.begin(9600);
  Serial.setTimeout(50);

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
}

void loop() {
  
  if(rs485.available() > 0)
  {
    uint8_t high_byte = rs485.read();
    delay(1);
    uint8_t low_byte = rs485.read();
    rs485_value_in = ((uint16_t)high_byte << 8) | low_byte;

    while(rs485.available() > 0)
    {
      rs485.read();
    }
  }
  
  if(Serial.available() > 0)
  {
    String temp_str;
    while(Serial.available() > 0)
    {
      temp_str = Serial.readString();
    }
    
#define MB_TRADITIONAL_PROTOCOL 0
#define MB_IP_PROTOCOL 1

    // check protoccol depend on whether message has "remain-length" element or not
    uint8_t protocol_check_result = [&]() -> uint8_t
    {
      uint16_t remain_length = ((uint16_t)temp_str[4] << 8) | (uint8_t)temp_str[5];
      if(remain_length == (temp_str.length() - 6))
      {
        return MB_IP_PROTOCOL;
      }
      else
      {
        return MB_TRADITIONAL_PROTOCOL;
      }
    }();
    
    if(protocol_check_result == MB_IP_PROTOCOL)
    {
      // find out response message length and init response message ------------------------------------
      uint16_t num_of_requested_reg = ((uint16_t)temp_str[10] << 8) | (uint8_t)temp_str[11];
      uint8_t message_length = 9+num_of_requested_reg*2;
      uint8_t response_message[message_length];
      // find out response message length and init response message ------------------------------------

      // package ID -------------------------
      response_message[0] = temp_str[0];
      response_message[1] = temp_str[1];
      // package ID -------------------------

      // reserve for future protocol ----------------------------
      response_message[2] = temp_str[2];
      response_message[3] = temp_str[3];
      // reserve for future protocol ----------------------------

      // remain length ---------------------------------------------------
      uint16_t response_remain_length = num_of_requested_reg*2 + 3;
      response_message[4] = (uint8_t)response_remain_length>>8;
      response_message[5] = (uint8_t)(response_remain_length & 0x00FF);
      // remain length ---------------------------------------------------

      // device ID and function code ------------
      response_message[6] = temp_str[6];
      response_message[7] = temp_str[7];
      // device ID and function code ------------

      // num of data byte (= num_of_register * 2) ------------------
      response_message[8] = num_of_requested_reg*2;
      // num of data byte (= num_of_register * 2) ------------------

      // data ----------------------------------------
      int analog_in_0 = analogRead(AI0);
      int analog_in_1 = analogRead(AI1);
      
      // belong to Mr.Hieu ------------------------------------------------
      int outputIW00 = map(analog_in_0, 8, 1024, 0, 1024);
      int outputIW01 = map(analog_in_1, 8, 1024, 0, 1024);
      
      int output_mA0 = map(outputIW00, 0, 1024, 4, 2000);
      int output_mA1 = map(outputIW01, 0, 1024, 4, 2000);
         
      if(outputIW00 < 0){ outputIW00 = 0;output_mA0 = 0;}
      if(outputIW01 < 0){ outputIW01 = 0;output_mA1 = 0;}
      
      response_message[9] = (uint8_t)(analog_in_0 >> 8);
      response_message[10] = (uint8_t)(analog_in_0 & 0x00FF);
      response_message[11] = (uint8_t)(analog_in_1 >> 8);
      response_message[12] = (uint8_t)(analog_in_1 & 0x00FF);
      response_message[13] = (uint8_t)(output_mA0 >> 8);
      response_message[14] = (uint8_t)(output_mA0 & 0x00FF);
      response_message[15] = (uint8_t)(output_mA1 >> 8);
      response_message[16] = (uint8_t)(output_mA1 & 0x00FF);
      // belong to Mr.Hieu ------------------------------------------------
      
      response_message[17] = rs485_value_in >> 8;
      response_message[18] = rs485_value_in & 0x00FF;

      for(int i = 19; i < message_length; i++)
      {
        response_message[i] = 0;
      }
      // data ----------------------------------------

      // send back response message --------------------------------------------------
      for(int i = 0; i < message_length; i++)
      {
        Serial.write(response_message[i]);
      }
      // send back response message --------------------------------------------------
    }
    else
    {
      // get and caculate crc ------------------------------------------------------------------------------------------
      uint16_t ADU_without_crc_length = temp_str.length()-2;
      uint8_t ADU_without_crc[ADU_without_crc_length];
      for(int i = 0; i < ADU_without_crc_length; i++)
      {
        ADU_without_crc[i] = (char)temp_str[i];
      }
      
      uint16_t crc_check = ModRTU_CRC(ADU_without_crc, ADU_without_crc_length);
      uint16_t crc_in = ((uint16_t)temp_str[temp_str.length()-1] << 8) | (uint8_t)temp_str[temp_str.length()-2];
      // get and caculate crc ------------------------------------------------------------------------------------------
  
      // if crc ok ---------------------------------------------------------------------------------------------------------------
      uint8_t check_crc_ok = (crc_check == crc_in);
      if(check_crc_ok)
      {
        // find out response message length and init response message ------------------------------------
        uint16_t num_of_requested_reg = ((uint16_t)temp_str[4] << 8) | (uint8_t)temp_str[5];
        uint8_t message_length = 3+num_of_requested_reg*2+2;
        uint8_t response_message[message_length];
        // find out response message length and init response message ------------------------------------
  
  
        // function and num of register --------------------------------------------------
        response_message[0] = (uint8_t)temp_str[0];
        response_message[1] = (uint8_t)temp_str[1];
        response_message[2] = (uint8_t)num_of_requested_reg*2;
        // function and num of register --------------------------------------------------
  
        
        // get ready the required registers --------------------------------------------------
        response_message[3] = 0;
        response_message[4] = 0;
        response_message[5] = 0;
        response_message[6] = 0;
  
        int analog_in_0 = analogRead(AI0);
        int analog_in_1 = analogRead(AI1);
        
        // belong to Mr.Hieu ------------------------------------------------
        int outputIW00 = map(analog_in_0, 8, 1024, 0, 1024);
        int outputIW01 = map(analog_in_1, 8, 1024, 0, 1024);
        
        int output_mA0 = map(outputIW00, 0, 1024, 4, 2000);
        int output_mA1 = map(outputIW01, 0, 1024, 4, 2000);
           
        if(outputIW00 < 0){ outputIW00 = 0;output_mA0 = 0;}
        if(outputIW01 < 0){ outputIW01 = 0;output_mA1 = 0;}
        
        response_message[3] = (uint8_t)(analog_in_0 >> 8);
        response_message[4] = (uint8_t)(analog_in_0 & 0x00FF);
        response_message[5] = (uint8_t)(analog_in_1 >> 8);
        response_message[6] = (uint8_t)(analog_in_1 & 0x00FF);
        response_message[7] = (uint8_t)(output_mA0 >> 8);
        response_message[8] = (uint8_t)(output_mA0 & 0x00FF);
        response_message[9] = (uint8_t)(output_mA1 >> 8);
        response_message[10] = (uint8_t)(output_mA1 & 0x00FF);
        // belong to Mr.Hieu ------------------------------------------------
        
        response_message[11] = rs485_value_in >> 8;
        response_message[12] = rs485_value_in & 0x00FF;
        
        for(int i = 13; i < message_length-2; i++)
        {
          response_message[i] = 0;
        }
        // get ready required registers --------------------------------------------------
  
  
        // make crc -------------------------------------------------------------------
        uint16_t response_crc = ModRTU_CRC(response_message, message_length-2);
        response_message[message_length-1] = (uint8_t)(response_crc >> 8);
        response_message[message_length-2] = (uint8_t)(response_crc & 0x00FF);
        // make crc -------------------------------------------------------------------
  
        // send back response message --------------------------------------------------
        for(int i = 0; i < message_length; i++)
        {
          Serial.write(response_message[i]);
        }
        // send back response message --------------------------------------------------
        
      }
      // if crc ok ---------------------------------------------------------------------------------------------------------------
    }
  }
}
