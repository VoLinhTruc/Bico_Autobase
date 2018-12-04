#ifndef __MODBUS_MASTER__
#define __MODBUS_MASTER__


#include "Modbus_Definition.h"

#define MASTER_MAX_DISCRETE_OUTPUT_COIL			 	80	// 10 bytes <-> 80 coil <-> 80bit in this case, it can be another number
#define	MASTER_MAX_DISCRETE_OUTPUT_COIL_IN_BYTE		MASTER_MAX_DISCRETE_OUTPUT_COIL/SIZE_OF_BYTE
#define MASTER_MAX_DISCRETE_INPUT_CONTACT				80	// 10 bytes <-> 80 coil <-> 80bit in this case, it can be another number
#define MASTER_MAX_DISCRETE_INPUT_CONTACT_IN_BYTE		MASTER_MAX_DISCRETE_INPUT_CONTACT/SIZE_OF_BYTE
#define MASTER_MAX_ANALOG_INPUT_REGISTER				25	// 50 bytes <-> 25*int <-> 25*16bit in this case, it can be another number
#define MASTER_MAX_ANALOG_OUTPUT_HOLDING_REGISTER		25	// 50 bytes <-> 25*int <-> 25*16bit in this case, it can be another number

#define MAX_REQUEST_PDU_LENGTH 100	// it can be another number. Maximum is 253 bytes(256 -3), see Modbus_Application_Protocol_V1_1b.pdf page 5 for more detail


uint8_t master_discrete_output_coil_list[MASTER_MAX_DISCRETE_OUTPUT_COIL_IN_BYTE];
uint8_t	master_discrete_input_contact_list[MASTER_MAX_DISCRETE_INPUT_CONTACT_IN_BYTE];

register_t master_analog_input_register_list[MASTER_MAX_ANALOG_INPUT_REGISTER];
register_t master_analog_output_holding_register_list[MASTER_MAX_ANALOG_OUTPUT_HOLDING_REGISTER];


uint8_t built_request_PDU[MAX_REQUEST_PDU_LENGTH];
uint8_t request_PDU_length = 0;

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
void readCoilsRequest(uint16_t starting_address, uint16_t quantity_of_coils);
void readDiscreteInputsRequest(uint16_t starting_address, uint16_t quantity_of_inputs);
void readHoldingRegistersRequest(uint16_t starting_address, uint16_t quantity_of_registers);
void readInputRegistersRequest(uint16_t starting_address, uint16_t quantity_of_input_registers);

void writeSingleCoilRequest(uint16_t output_address, uint16_t output_value);
void writeSingleRegisterRequest(uint16_t register_address, register_t register_value);

void writeMultipleCoilsRequest(uint16_t starting_address, uint16_t quantity_of_outputs, uint8_t byte_count, uint8_t* output_value);
void writeMultipleRegistersRequest(uint16_t starting_address, uint16_t quantity_of_registers, uint8_t byte_count/* =N* x 2Byte*/, register_t* registers_value);



Function_Code getFunctionCode(uint8_t* PDU);
Exception_Code getExceptionCode(uint8_t* PDU);


uint8_t getReadCoilByteCount(uint8_t* PDU);
void getReadCoilStatus(uint8_t* PDU, uint8_t length, uint8_t* coil_status_buffer);

uint8_t getReadDiscreteInputByteCount(uint8_t* PDU);
void getReadDiscreteInputStatus(uint8_t* PDU, uint8_t length, uint8_t* discrete_input_status_buffer);

uint8_t getReadHoldingRegistersByteCount(uint8_t* PDU);
void getReadHoldingRegistersValue(uint8_t* PDU, uint8_t length, register_t* holding_register_value_buffer);
uint8_t getReadHoldingRegistersNumberOfRegister(uint8_t* PDU);

uint8_t getReadInputRegistersByteCount(uint8_t* PDU);
void getReadInputRegistersValue(uint8_t* PDU, uint8_t length, register_t* input_register_value_buffer);
uint8_t getReadInputRegistersNumberOfRegister(uint8_t* PDU);


uint16_t getResponseWriteSingleCoilOutputAddress(uint8_t* PDU);
uint16_t getWriteSingleCoilOutputValue(uint8_t* PDU);

uint16_t getWriteSingleRegisterOutputAddress(uint8_t* PDU);
uint16_t getWriteSingleRegisterOutputValue(uint8_t* PDU);

uint16_t getWriteMultipleCoilsStartingAddress(uint8_t* PDU);
uint16_t getWriteMultipleCoilsStartingQuantityOfOutputs(uint8_t* PDU);

uint16_t getWriteMultipleRegistersStartingAddress(uint8_t* PDU);
uint16_t getWriteMultipleRegistersStartingQuantityOfRegisters(uint8_t* PDU);





void readCoilsRequest(uint16_t starting_address, uint16_t quantity_of_coils)
{
	request_PDU_length = 0;
	built_request_PDU[request_PDU_length++] = READ_COILS;
	built_request_PDU[request_PDU_length++] = (uint8_t)(starting_address >> 8);
	built_request_PDU[request_PDU_length++] = (uint8_t)(starting_address & 0x00FF);
	built_request_PDU[request_PDU_length++] = (uint8_t)(quantity_of_coils >> 8);
	built_request_PDU[request_PDU_length++] = (uint8_t)(quantity_of_coils & 0x00FF);
}

void readDiscreteInputsRequest(uint16_t starting_address, uint16_t quantity_of_inputs)
{
	request_PDU_length = 0;
	built_request_PDU[request_PDU_length++] = READ_DISCRETE_INPUTS;
	built_request_PDU[request_PDU_length++] = (uint8_t)(starting_address >> 8);
	built_request_PDU[request_PDU_length++] = (uint8_t)(starting_address & 0x00FF);
	built_request_PDU[request_PDU_length++] = (uint8_t)(quantity_of_inputs >> 8);
	built_request_PDU[request_PDU_length++] = (uint8_t)(quantity_of_inputs & 0x00FF);
}

void readHoldingRegistersRequest(uint16_t starting_address, uint16_t quantity_of_registers)
{
	request_PDU_length = 0;
	built_request_PDU[request_PDU_length++] = READ_HOLDING_REGISTERS;
	built_request_PDU[request_PDU_length++] = (uint8_t)(starting_address >> 8);
	built_request_PDU[request_PDU_length++] = (uint8_t)(starting_address & 0x00FF);
	built_request_PDU[request_PDU_length++] = (uint8_t)(quantity_of_registers >> 8);
	built_request_PDU[request_PDU_length++] = (uint8_t)(quantity_of_registers & 0x00FF);
}

void readInputRegistersRequest(uint16_t starting_address, uint16_t quantity_of_input_registers)
{
	request_PDU_length = 0;
	built_request_PDU[request_PDU_length++] = READ_INPUT_REGISTERS;
	built_request_PDU[request_PDU_length++] = (uint8_t)(starting_address >> 8);
	built_request_PDU[request_PDU_length++] = (uint8_t)(starting_address & 0x00FF);
	built_request_PDU[request_PDU_length++] = (uint8_t)(quantity_of_input_registers >> 8);
	built_request_PDU[request_PDU_length++] = (uint8_t)(quantity_of_input_registers & 0x00FF);
}



void writeSingleCoilRequest(uint16_t output_address, uint16_t output_value)
{
	request_PDU_length = 0;
	built_request_PDU[request_PDU_length++] = WRITE_SINGLE_COIL;
	built_request_PDU[request_PDU_length++] = (uint8_t)(output_address >> 8);
	built_request_PDU[request_PDU_length++] = (uint8_t)(output_address & 0x00FF);
	built_request_PDU[request_PDU_length++] = (uint8_t)(output_value >> 8);
	built_request_PDU[request_PDU_length++] = (uint8_t)(output_value & 0x00FF);
}

void writeSingleRegisterRequest(uint16_t register_address, register_t register_value)
{
	request_PDU_length = 0;
	built_request_PDU[request_PDU_length++] = WRITE_SINGLE_REGISTER;
	built_request_PDU[request_PDU_length++] = (uint8_t)(register_address >> 8);
	built_request_PDU[request_PDU_length++] = (uint8_t)(register_address & 0x00FF);
	built_request_PDU[request_PDU_length++] = (uint8_t)((unsigned register_t)register_value >> 8);
	built_request_PDU[request_PDU_length++] = (uint8_t)((unsigned register_t)register_value & 0x00FF);
}



void writeMultipleCoilsRequest(uint16_t starting_address, uint16_t quantity_of_outputs, uint8_t byte_count, uint8_t* output_value)
{
	request_PDU_length = 0;
	built_request_PDU[request_PDU_length++] = WRITE_MULTIPLE_COILS;
	built_request_PDU[request_PDU_length++] = (uint8_t)(starting_address >> 8);
	built_request_PDU[request_PDU_length++] = (uint8_t)(starting_address & 0x00FF);
	built_request_PDU[request_PDU_length++] = (uint8_t)(quantity_of_outputs >> 8);
	built_request_PDU[request_PDU_length++] = (uint8_t)(quantity_of_outputs & 0x00FF);

	built_request_PDU[request_PDU_length++] = byte_count;
	for(uint8_t i = 0; i < byte_count; i++)
	{
		built_request_PDU[request_PDU_length++] = output_value[i];
	}
}

void writeMultipleRegistersRequest(uint16_t starting_address, uint16_t quantity_of_registers, uint8_t byte_count/* =N* x 2Byte*/, register_t* registers_value)
{
	request_PDU_length = 0;
	built_request_PDU[request_PDU_length++] = WRITE_MULTIPLE_REGISTERS;
	built_request_PDU[request_PDU_length++] = (uint8_t)(starting_address >> 8);
	built_request_PDU[request_PDU_length++] = (uint8_t)(starting_address & 0x00FF);
	built_request_PDU[request_PDU_length++] = (uint8_t)(quantity_of_registers >> 8);
	built_request_PDU[request_PDU_length++] = (uint8_t)(quantity_of_registers & 0x00FF);

	built_request_PDU[request_PDU_length++] = byte_count;
	uint8_t quantity_of_register = byte_count/2;
	for(uint8_t i = 0; i < quantity_of_register; i++)
	{
		built_request_PDU[request_PDU_length++] = (uint8_t)((unsigned register_t)registers_value[i] >> 8);
		built_request_PDU[request_PDU_length++] = (uint8_t)((unsigned register_t)registers_value[i] & 0x00FF);
	}
}





Function_Code getFunctionCode(uint8_t* PDU)
{
	return (Function_Code)PDU[0];
}

Exception_Code getExceptionCode(uint8_t* PDU)
{
	return (Exception_Code)PDU[1];
}



uint8_t getReadCoilByteCount(uint8_t* PDU)
{
	return PDU[1];
}

void getReadCoilStatus(uint8_t* PDU, uint8_t length, uint8_t* coil_status_buffer)
{
	for(uint8_t i = 2; i < length; i++)
	{
		coil_status_buffer[i] = PDU[i];
	}
}


uint8_t getReadDiscreteInputByteCount(uint8_t* PDU)
{
	return PDU[1];
}

void getReadDiscreteInputStatus(uint8_t* PDU, uint8_t length, uint8_t* discrete_input_status_buffer)
{
	for(uint8_t i = 2; i < length; i++)
	{
		discrete_input_status_buffer[i] = PDU[i];
	}
}


uint8_t getReadHoldingRegistersByteCount(uint8_t* PDU)
{
	return PDU[1];
}

void getReadHoldingRegistersValue(uint8_t* PDU, uint8_t length, register_t* holding_register_value_buffer)
{
	uint8_t num_of_register = getReadHoldingRegistersByteCount(PDU)/2;
	for(uint8_t i = 0; i < num_of_register; i++)
	{
		holding_register_value_buffer[i] = (register_t)(((uint16_t)PDU[2 + 2*i] << 8) | (PDU[2 + 2*i + 1]));
	}
}

uint8_t getReadHoldingRegistersNumberOfRegister(uint8_t* PDU)
{
	return getReadHoldingRegistersByteCount(PDU)/2;
}


uint8_t getReadInputRegistersByteCount(uint8_t* PDU)
{
	return PDU[1];
}

void getReadInputRegistersValue(uint8_t* PDU, uint8_t length, register_t* input_register_value_buffer)
{
	uint8_t num_of_register = getReadInputRegistersByteCount(PDU)/2;
	for(uint8_t i = 0; i < num_of_register; i++)
	{
		input_register_value_buffer[i] = (register_t)(((uint16_t)PDU[2 + 2*i] << 8) | (PDU[2 + 2*i + 1]));
	}
}

uint8_t getReadInputRegistersNumberOfRegister(uint8_t* PDU)
{
	return getReadInputRegistersByteCount(PDU)/2;
}


uint16_t getResponseWriteSingleCoilOutputAddress(uint8_t* PDU)
{
	return (((uint16_t)PDU[1] << 8) | PDU[2]);
}

uint16_t getWriteSingleCoilOutputValue(uint8_t* PDU)
{
	return (((uint16_t)PDU[3] << 8) | PDU[4]);
}


uint16_t getWriteSingleRegisterOutputAddress(uint8_t* PDU)
{
	return (((uint16_t)PDU[1] << 8) | PDU[2]);
}

uint16_t getWriteSingleRegisterOutputValue(uint8_t* PDU)
{
	return (((uint16_t)PDU[3] << 8) | PDU[4]);
}


uint16_t getWriteMultipleCoilsStartingAddress(uint8_t* PDU)
{
	return (((uint16_t)PDU[1] << 8) | PDU[2]);
}

uint16_t getWriteMultipleCoilsStartingQuantityOfOutputs(uint8_t* PDU)
{
	return (((uint16_t)PDU[3] << 8) | PDU[4]);
}


uint16_t getWriteMultipleRegistersStartingAddress(uint8_t* PDU)
{
	return (((uint16_t)PDU[1] << 8) | PDU[2]);
}

uint16_t getWriteMultipleRegistersStartingQuantityOfRegisters(uint8_t* PDU)
{
	return (((uint16_t)PDU[3] << 8) | PDU[4]);
}






//referrence: MODBUS APPLICATION PROTOCOL SPECIFICATION V1.1b.pdf
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif //__MODBUS_MASTER__