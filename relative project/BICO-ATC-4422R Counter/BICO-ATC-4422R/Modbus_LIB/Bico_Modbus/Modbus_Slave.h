#ifndef __MODBUS_SLAVE__
#define __MODBUS_SLAVE__

#include "Modbus_Definition.h"



#define SLAVE_DEFAULT_ID (uint8_t)1 // it can be another number

#define SLAVE_MAX_DISCRETE_OUTPUT_COIL			 	80	// 10 bytes <-> 80 coil <-> 80bit in this case, it can be another number
#define	SLAVE_MAX_DISCRETE_OUTPUT_COIL_IN_BYTE		SLAVE_MAX_DISCRETE_OUTPUT_COIL/SIZE_OF_BYTE
#define SLAVE_MAX_DISCRETE_INPUT_CONTACT				80	// 10 bytes <-> 80 coil <-> 80bit in this case, it can be another number
#define SLAVE_MAX_DISCRETE_INPUT_CONTACT_IN_BYTE		SLAVE_MAX_DISCRETE_INPUT_CONTACT/SIZE_OF_BYTE
#define SLAVE_MAX_ANALOG_INPUT_REGISTER				100	// 200 bytes <-> 100*int <-> 100*16bit in this case, it can be another number
#define SLAVE_MAX_ANALOG_OUTPUT_HOLDING_REGISTER		100	// 200 bytes <-> 100*int <-> 100*16bit in this case, it can be another number

#define MAX_RESPONSE_PDU_LENGTH					100 // Maximum is 253 (256 -3) bytes, see Modbus_Application_Protocol_V1_1b.pdf page 5 for more detail
													// Note: MAX_RESPONSE_PDU_LENGTH depend on memory-element (coil, discrete input, holding register, input register) size, if memory-element size get bigger, MAX_RESPONSE_PDU_LENGTH must extend according memory-element size


uint8_t slave_discrete_output_coil_list[SLAVE_MAX_DISCRETE_OUTPUT_COIL_IN_BYTE];
uint8_t	slave_discrete_input_contact_list[SLAVE_MAX_DISCRETE_INPUT_CONTACT_IN_BYTE];

register_t slave_analog_input_register_list[SLAVE_MAX_ANALOG_INPUT_REGISTER];
register_t slave_analog_output_holding_register_list[SLAVE_MAX_ANALOG_OUTPUT_HOLDING_REGISTER];

uint8_t built_response_PDU[MAX_RESPONSE_PDU_LENGTH];
uint8_t response_PDU_length = 0;

uint8_t slave_device_id = SLAVE_DEFAULT_ID;




void readCoilsResponse(uint8_t byte_count, uint8_t* coil_status); //referrence: MODBUS APPLICATION PROTOCOL SPECIFICATION V1.1b.pdf page 12
void readDiscreteInputsResponse(uint8_t byte_count, uint8_t* input_status);	//referrence: MODBUS APPLICATION PROTOCOL SPECIFICATION V1.1b.pdf page 13
void readHoldingRegistersResponse(uint8_t byte_count, register_t* register_value);	//referrence: MODBUS APPLICATION PROTOCOL SPECIFICATION V1.1b.pdf page 15
void readInputRegistersResponse(uint8_t byte_count, register_t* input_registers);	//referrence: MODBUS APPLICATION PROTOCOL SPECIFICATION V1.1b.pdf page 16

void writeSingleCoilResponse(uint16_t output_address, uint16_t output_value);	//referrence: MODBUS APPLICATION PROTOCOL SPECIFICATION V1.1b.pdf page 17,18
void writeSingleRegisterResponse(uint16_t register_address, register_t register_value);	//referrence: MODBUS APPLICATION PROTOCOL SPECIFICATION V1.1b.pdf page 19

void writeMultipleCoilsResponse(uint16_t starting_address, uint16_t quantity_of_outputs);	//referrence: MODBUS APPLICATION PROTOCOL SPECIFICATION V1.1b.pdf page 29
void writeMultipleRegistersResponse(uint16_t starting_address, uint16_t quantity_of_registers);	//referrence: MODBUS APPLICATION PROTOCOL SPECIFICATION V1.1b.pdf page 30,31



void functionCodeExceptionResponse(uint8_t f_code);

void readCoilsExceptionResponse(Exception_Code e_code); //referrence: MODBUS APPLICATION PROTOCOL SPECIFICATION V1.1b.pdf page 12
void readDiscreteInputsExceptionResponse(Exception_Code e_code);	//referrence: MODBUS APPLICATION PROTOCOL SPECIFICATION V1.1b.pdf page 13
void readHoldingRegistersExceptionResponse(Exception_Code e_code);	//referrence: MODBUS APPLICATION PROTOCOL SPECIFICATION V1.1b.pdf page 15
void readInputRegistersExceptionResponse(Exception_Code e_code);	//referrence: MODBUS APPLICATION PROTOCOL SPECIFICATION V1.1b.pdf page 16

void writeSingleCoilExceptionResponse(Exception_Code e_code);	//referrence: MODBUS APPLICATION PROTOCOL SPECIFICATION V1.1b.pdf page 17,18
void writeSingleRegisterExceptionResponse(Exception_Code e_code);	//referrence: MODBUS APPLICATION PROTOCOL SPECIFICATION V1.1b.pdf page 19

void writeMultipleCoilsExceptionResponse(Exception_Code e_code);	//referrence: MODBUS APPLICATION PROTOCOL SPECIFICATION V1.1b.pdf page 29
void writeMultipleRegistersExceptionResponse(Exception_Code e_code);	//referrence: MODBUS APPLICATION PROTOCOL SPECIFICATION V1.1b.pdf page 30,31






void readCoilsResponse(uint8_t byte_count, uint8_t* coil_status)
{
	response_PDU_length = 0;
	built_response_PDU[response_PDU_length++] = READ_COILS;
	built_response_PDU[response_PDU_length++] = byte_count;
	for(uint8_t i = 0; i < byte_count; i++)
	{
		built_response_PDU[response_PDU_length++] = coil_status[i];
	}
}

void readDiscreteInputsResponse(uint8_t byte_count, uint8_t* input_status)
{
	response_PDU_length = 0;
	built_response_PDU[response_PDU_length++] = READ_DISCRETE_INPUTS;
	built_response_PDU[response_PDU_length++] = byte_count;
	for(uint8_t i = 0; i < byte_count; i++)
	{
		built_response_PDU[response_PDU_length++] = input_status[i];
	}
}

void readHoldingRegistersResponse(uint8_t byte_count, register_t* register_value)
{
	response_PDU_length = 0;
	built_response_PDU[response_PDU_length++] = READ_HOLDING_REGISTERS;
	built_response_PDU[response_PDU_length++] = byte_count;

	uint8_t quantity_of_register = byte_count/2;
	for(uint8_t i = 0; i < quantity_of_register; i++)
	{
		built_response_PDU[response_PDU_length++] = (uint8_t)((unsigned register_t)register_value[i] >> 8);
		built_response_PDU[response_PDU_length++] = (uint8_t)((unsigned register_t)register_value[i] & 0x00FF);
	}
}

void readInputRegistersResponse(uint8_t byte_count, register_t* input_registers)
{
	response_PDU_length = 0;
	built_response_PDU[response_PDU_length++] = READ_INPUT_REGISTERS;
	built_response_PDU[response_PDU_length++] = byte_count;

	uint8_t quantity_of_register = byte_count/2;
	for(uint8_t i = 0; i < quantity_of_register; i++)
	{
		built_response_PDU[response_PDU_length++] = (uint8_t)((unsigned register_t)input_registers[i] >> 8);
		built_response_PDU[response_PDU_length++] = (uint8_t)((unsigned register_t)input_registers[i] & 0x00FF);
	}
}

void writeSingleCoilResponse(uint16_t output_address, uint16_t output_value)
{
	response_PDU_length = 0;
	built_response_PDU[response_PDU_length++] = WRITE_SINGLE_COIL;
	built_response_PDU[response_PDU_length++] = (uint8_t)(output_address >> 8);
	built_response_PDU[response_PDU_length++] = (uint8_t)(output_address & 0x00FF);
	built_response_PDU[response_PDU_length++] = (uint8_t)(output_value >> 8);
	built_response_PDU[response_PDU_length++] = (uint8_t)(output_value & 0x00FF);
}

void writeSingleRegisterResponse(uint16_t register_address, register_t register_value)
{
	response_PDU_length = 0;
	built_response_PDU[response_PDU_length++] = WRITE_SINGLE_REGISTER;
	built_response_PDU[response_PDU_length++] = (uint8_t)((unsigned register_t)register_address >> 8);
	built_response_PDU[response_PDU_length++] = (uint8_t)((unsigned register_t)register_address & 0x00FF);
	built_response_PDU[response_PDU_length++] = (uint8_t)((unsigned register_t)register_value >> 8);
	built_response_PDU[response_PDU_length++] = (uint8_t)((unsigned register_t)register_value & 0x00FF);
}

void writeMultipleCoilsResponse(uint16_t starting_address, uint16_t quantity_of_outputs)
{
	response_PDU_length = 0;
	built_response_PDU[response_PDU_length++] = WRITE_MULTIPLE_COILS;
	built_response_PDU[response_PDU_length++] = (uint8_t)(starting_address >> 8);
	built_response_PDU[response_PDU_length++] = (uint8_t)(starting_address & 0x00FF);
	built_response_PDU[response_PDU_length++] = (uint8_t)(quantity_of_outputs >> 8);
	built_response_PDU[response_PDU_length++] = (uint8_t)(quantity_of_outputs & 0x00FF);
}

void writeMultipleRegistersResponse(uint16_t starting_address, uint16_t quantity_of_registers)
{
	response_PDU_length = 0;
	built_response_PDU[response_PDU_length++] = WRITE_MULTIPLE_REGISTERS;
	built_response_PDU[response_PDU_length++] = (uint8_t)(starting_address >> 8);
	built_response_PDU[response_PDU_length++] = (uint8_t)(starting_address & 0x00FF);
	built_response_PDU[response_PDU_length++] = (uint8_t)(quantity_of_registers >> 8);
	built_response_PDU[response_PDU_length++] = (uint8_t)(quantity_of_registers & 0x00FF);
}



void functionCodeExceptionResponse(uint8_t f_code)
{
	response_PDU_length = 0;
	built_response_PDU[response_PDU_length++] = f_code + 0x80;
	built_response_PDU[response_PDU_length++] = ILLEGAL_FUNCTION;
}


void readCoilsExceptionResponse(Exception_Code e_code)
{
	response_PDU_length = 0;
	built_response_PDU[response_PDU_length++] = READ_COILS + 0x80;
	built_response_PDU[response_PDU_length++] = e_code;
}

void readDiscreteInputsExceptionResponse(Exception_Code e_code)
{
	response_PDU_length = 0;
	built_response_PDU[response_PDU_length++] = READ_DISCRETE_INPUTS + 0x80;
	built_response_PDU[response_PDU_length++] = e_code;
}

void readHoldingRegistersExceptionResponse(Exception_Code e_code)
{
	response_PDU_length = 0;
	built_response_PDU[response_PDU_length++] = READ_HOLDING_REGISTERS + 0x80;
	built_response_PDU[response_PDU_length++] = e_code;
}

void readInputRegistersExceptionResponse(Exception_Code e_code)
{
	response_PDU_length = 0;
	built_response_PDU[response_PDU_length++] = READ_INPUT_REGISTERS + 0x80;
	built_response_PDU[response_PDU_length++] = e_code;
}

void writeSingleCoilExceptionResponse(Exception_Code e_code)
{
	response_PDU_length = 0;
	built_response_PDU[response_PDU_length++] = WRITE_SINGLE_COIL + 0x80;
	built_response_PDU[response_PDU_length++] = e_code;
}

void writeSingleRegisterExceptionResponse(Exception_Code e_code)
{
	response_PDU_length = 0;
	built_response_PDU[response_PDU_length++] = WRITE_SINGLE_REGISTER + 0x80;
	built_response_PDU[response_PDU_length++] = e_code;
}

void writeMultipleCoilsExceptionResponse(Exception_Code e_code)
{
	response_PDU_length = 0;
	built_response_PDU[response_PDU_length++] = WRITE_MULTIPLE_COILS + 0x80;
	built_response_PDU[response_PDU_length++] = e_code;
}

void writeMultipleRegistersExceptionResponse(Exception_Code e_code)
{
	response_PDU_length = 0;
	built_response_PDU[response_PDU_length++] = WRITE_MULTIPLE_REGISTERS + 0x80;
	built_response_PDU[response_PDU_length++] = e_code;
}


#endif //__MODBUS_SLAVE__