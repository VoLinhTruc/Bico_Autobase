#ifndef __MODBUS_DEFINITION__
#define __MODBUS_DEFINITION__


//-------------------------------------------------------
typedef short int register_t; //int <-> 16 bit in this case
#define SIZE_OF_BYTE	8	// 1byte <-> 8bit in this case
//-------------------------------------------------------


//-------------------------------------------------------
typedef uint8_t Function_Code;

#define READ_COILS					(uint8_t)0x01
#define READ_DISCRETE_INPUTS		(uint8_t)0x02
#define READ_HOLDING_REGISTERS		(uint8_t)0x03
#define READ_INPUT_REGISTERS		(uint8_t)0x04

#define WRITE_SINGLE_COIL			(uint8_t)0x05
#define WRITE_SINGLE_REGISTER		(uint8_t)0x06

#define WRITE_MULTIPLE_COILS		(uint8_t)0x0F
#define WRITE_MULTIPLE_REGISTERS	(uint8_t)0x10

//referrence: MODBUS APPLICATION PROTOCOL SPECIFICATION V1.1b.pdf
//-------------------------------------------------------


//-------------------------------------------------------
typedef uint8_t Exception_Code;

#define ILLEGAL_FUNCTION          (uint8_t)0x01
#define ILLEGAL_DATA_ADDRESS    (uint8_t)0x02
#define ILLEGAL_DATA_VALUE    (uint8_t)0x03
#define SLAVE_DEVICE_FAILURE    (uint8_t)0x04

#define ACKNOWLEDGE     (uint8_t)0x05
#define SLAVE_DEVICE_BUSY   (uint8_t)0x06

#define MEMORY_PARITY_ERROR    (uint8_t)0x08
#define GATEWAY_PATH_UNAVAILABLE  (uint8_t)0x0A
#define GATEWAY_TARGET_DEVICE_FAILED_TO_RESPOND   (uint8_t)0x0B

//referrence: MODBUS APPLICATION PROTOCOL SPECIFICATION V1.1b.pdf
//-------------------------------------------------------


//-------------------------------------------------------
typedef uint32_t Base_Address; 

#define DISCRETE_OUTPUT_COILS_BASE_ADDRESS				(uint32_t)1
#define DISCRETE_INPUT_CONTACTS_BASE_ADDRESS			(uint32_t)10001
#define	ANALOG_INPUT_REGISTERS_BASE_ADDRESS				(uint32_t)30001
#define ANALOG_OUTPUT_HOLDING_REGISTERS_BASE_ADDRESS	(uint32_t)40001

//referrence: http://www.simplymodbus.ca/FAQ.htm
//-------------------------------------------------------


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



uint8_t getBitFromArray(uint8_t* array_in, uint16_t bit_order)
{
  //|------------------------------------------------------------------------------------------|bit_order                                 
  //  _   _   _   _   _   _   _   _        _   _   _   _   _   _   _   _       _   _   _   _   _   _   _   _
  // |_| |_| |_| |_| |_| |_| |_| |_| .... |_| |_| |_| |_| |_| |_| |_| |_|   |_| |_| |_| |_| |o| |_| |_| |_|  ... (array_in)
  //|-------------------------------------------------------------------------|byte_index
  //                                              bit_index|------------|
  //                                      MSB             LSB
  uint16_t index_byte = bit_order/8;
  uint8_t index_bit = bit_order%8;

  return !!(array_in[index_byte] & ((uint8_t)1 << index_bit));
}

void setBitToArray(uint8_t* array_in, uint16_t bit_order, uint8_t value)
{
  //|------------------------------------------------------------------------------------------|bit_order                                 
  //  _   _   _   _   _   _   _   _        _   _   _   _   _   _   _   _       _   _   _   _   _   _   _   _
  // |_| |_| |_| |_| |_| |_| |_| |_| .... |_| |_| |_| |_| |_| |_| |_| |_|   |_| |_| |_| |_| |o| |_| |_| |_|  ... (array_in)
  //|-------------------------------------------------------------------------|byte_index
  //                                              bit_index|------------|
  //                                      MSB             LSB
  uint16_t index_byte = bit_order/8;
  uint8_t index_bit = bit_order%8;

  if(!value)
  {
    array_in[index_byte] &= ~(1 << index_bit);
  }
  else
  {
    array_in[index_byte] |= (1 << index_bit);
  }
}



#endif //__MODBUS_DEFINITION__