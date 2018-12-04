#ifndef __MODBUS_MASTER_RTU__
#define __MODBUS_MASTER_RTU__

#include "Modbus_Master.h"

#define MAX_REQUEST_RTU_ADU_LENGTH MAX_REQUEST_PDU_LENGTH+3 // = 1byte for slave ID + MAX_REQUEST_PDU_LENGTH + 2byte for CRC

uint8_t built_request_RTU_ADU[MAX_REQUEST_RTU_ADU_LENGTH];
uint8_t request_RTU_ADU_length = 0;





void RTU_ADU_readCoilsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_coils);
void RTU_ADU_readDiscreteInputsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_inputs);
void RTU_ADU_readHoldingRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers);
void RTU_ADU_readInputRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_input_registers);

void RTU_ADU_writeSingleCoilRequest(uint8_t slave_id, uint16_t output_address, uint16_t output_value);
void RTU_ADU_writeSingleRegisterRequest(uint8_t slave_id, uint16_t register_address, register_t register_value);

void RTU_ADU_writeMultipleCoilsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_outputs, uint8_t byte_count, uint8_t* output_value);
void RTU_ADU_writeMultipleRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers, uint8_t byte_count/* =N* x 2Byte*/, register_t* registers_value);








uint16_t RTU_ADU_getResposeSlaveID(uint8_t* ADU);
uint16_t RTU_ADU_getCRC(uint8_t* ADU, uint16_t length);
void RTU_ADU_getPDU(uint8_t* ADU, uint16_t length, uint8_t* PDU_buffer, uint8_t* PDU_length);



Function_Code RTU_ADU_getFunctionCode(uint8_t* ADU);
Exception_Code RTU_ADU_getExceptionCode(uint8_t* ADU);


uint8_t RTU_ADU_getReadCoilByteCount(uint8_t* ADU);
void RTU_ADU_getReadCoilStatus(uint8_t* ADU, uint8_t length, uint8_t* coil_status_buffer);

uint8_t RTU_ADU_getReadDiscreteInputByteCount(uint8_t* ADU);
void RTU_ADU_getReadDiscreteInputStatus(uint8_t* ADU, uint8_t length, uint8_t* discrete_input_status_buffer);

uint8_t RTU_ADU_getReadHoldingRegistersByteCount(uint8_t* ADU);
void RTU_ADU_getReadHoldingRegistersValue(uint8_t* ADU, uint8_t length, register_t* holding_register_value_buffer);
uint8_t RTU_ADU_getReadHoldingRegistersNumberOfRegister(uint8_t* ADU);

uint8_t RTU_ADU_getReadInputRegistersByteCount(uint8_t* ADU);
void RTU_ADU_getReadInputRegistersValue(uint8_t* ADU, uint8_t length, register_t* input_register_value_buffer);
uint8_t RTU_ADU_getReadInputRegistersNumberOfRegister(uint8_t* ADU);


uint16_t RTU_ADU_getResponseWriteSingleCoilOutputAddress(uint8_t* ADU);
uint16_t RTU_ADU_getWriteSingleCoilOutputValue(uint8_t* ADU);

uint16_t RTU_ADU_getWriteSingleRegisterOutputAddress(uint8_t* ADU);
uint16_t RTU_ADU_getWriteSingleRegisterOutputValue(uint8_t* ADU);

uint16_t RTU_ADU_getWriteMultipleCoilsStartingAddress(uint8_t* ADU);
uint16_t RTU_ADU_getWriteMultipleCoilsStartingQuantityOfOutputs(uint8_t* ADU);

uint16_t RTU_ADU_getWriteMultipleRegistersStartingAddress(uint8_t* ADU);
uint16_t RTU_ADU_getWriteMultipleRegistersStartingQuantityOfRegisters(uint8_t* ADU);








void RTU_ADU_readCoilsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_coils)
{
	request_RTU_ADU_length = 0;
	built_request_RTU_ADU[request_RTU_ADU_length++] = slave_id;

	readCoilsRequest(starting_address, quantity_of_coils);
	for(uint8_t i = 0; i < request_PDU_length; i++)
	{
		built_request_RTU_ADU[request_RTU_ADU_length++] = built_request_PDU[i];
	}

	uint16_t crc = ModRTU_CRC(built_request_RTU_ADU, request_RTU_ADU_length);
	built_request_RTU_ADU[request_RTU_ADU_length++] = (uint8_t)(crc & 0x00FF);
	built_request_RTU_ADU[request_RTU_ADU_length++] = (uint8_t)(crc >> 8);
}

void RTU_ADU_readDiscreteInputsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_inputs)
{
	request_RTU_ADU_length = 0;
	built_request_RTU_ADU[request_RTU_ADU_length++] = slave_id;

	readDiscreteInputsRequest(starting_address, quantity_of_inputs);
	for(uint8_t i = 0; i < request_PDU_length; i++)
	{
		built_request_RTU_ADU[request_RTU_ADU_length++] = built_request_PDU[i];
	}

	uint16_t crc = ModRTU_CRC(built_request_RTU_ADU, request_RTU_ADU_length);
	built_request_RTU_ADU[request_RTU_ADU_length++] = (uint8_t)(crc & 0x00FF);
	built_request_RTU_ADU[request_RTU_ADU_length++] = (uint8_t)(crc >> 8);
}

void RTU_ADU_readHoldingRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers)
{
	request_RTU_ADU_length = 0;
	built_request_RTU_ADU[request_RTU_ADU_length++] = slave_id;

	readHoldingRegistersRequest(starting_address, quantity_of_registers);
	for(uint8_t i = 0; i < request_PDU_length; i++)
	{
		built_request_RTU_ADU[request_RTU_ADU_length++] = built_request_PDU[i];
	}

	uint16_t crc = ModRTU_CRC(built_request_RTU_ADU, request_RTU_ADU_length);
	built_request_RTU_ADU[request_RTU_ADU_length++] = (uint8_t)(crc & 0x00FF);
	built_request_RTU_ADU[request_RTU_ADU_length++] = (uint8_t)(crc >> 8);
}

void RTU_ADU_readInputRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_input_registers)
{
	request_RTU_ADU_length = 0;
	built_request_RTU_ADU[request_RTU_ADU_length++] = slave_id;

	readInputRegistersRequest(starting_address, quantity_of_input_registers);
	for(uint8_t i = 0; i < request_PDU_length; i++)
	{
		built_request_RTU_ADU[request_RTU_ADU_length++] = built_request_PDU[i];
	}

	uint16_t crc = ModRTU_CRC(built_request_RTU_ADU, request_RTU_ADU_length);
	built_request_RTU_ADU[request_RTU_ADU_length++] = (uint8_t)(crc & 0x00FF);
	built_request_RTU_ADU[request_RTU_ADU_length++] = (uint8_t)(crc >> 8);	
}

void RTU_ADU_writeSingleCoilRequest(uint8_t slave_id, uint16_t output_address, uint16_t output_value)
{
	request_RTU_ADU_length = 0;
	built_request_RTU_ADU[request_RTU_ADU_length++] = slave_id;

	writeSingleCoilRequest(output_address, output_value);
	for(uint8_t i = 0; i < request_PDU_length; i++)
	{
		built_request_RTU_ADU[request_RTU_ADU_length++] = built_request_PDU[i];
	}

	uint16_t crc = ModRTU_CRC(built_request_RTU_ADU, request_RTU_ADU_length);
	built_request_RTU_ADU[request_RTU_ADU_length++] = (uint8_t)(crc & 0x00FF);
	built_request_RTU_ADU[request_RTU_ADU_length++] = (uint8_t)(crc >> 8);	
}

void RTU_ADU_writeSingleRegisterRequest(uint8_t slave_id, uint16_t register_address, register_t register_value)
{
	request_RTU_ADU_length = 0;
	built_request_RTU_ADU[request_RTU_ADU_length++] = slave_id;

	writeSingleRegisterRequest(register_address, register_value);
	for(uint8_t i = 0; i < request_PDU_length; i++)
	{
		built_request_RTU_ADU[request_RTU_ADU_length++] = built_request_PDU[i];
	}

	uint16_t crc = ModRTU_CRC(built_request_RTU_ADU, request_RTU_ADU_length);
	built_request_RTU_ADU[request_RTU_ADU_length++] = (uint8_t)(crc & 0x00FF);
	built_request_RTU_ADU[request_RTU_ADU_length++] = (uint8_t)(crc >> 8);	
}

void RTU_ADU_writeMultipleCoilsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_outputs, uint8_t byte_count, uint8_t* output_value)
{
	request_RTU_ADU_length = 0;
	built_request_RTU_ADU[request_RTU_ADU_length++] = slave_id;

	writeMultipleCoilsRequest(starting_address, quantity_of_outputs, byte_count, output_value);
	for(uint8_t i = 0; i < request_PDU_length; i++)
	{
		built_request_RTU_ADU[request_RTU_ADU_length++] = built_request_PDU[i];
	}

	uint16_t crc = ModRTU_CRC(built_request_RTU_ADU, request_RTU_ADU_length);
	built_request_RTU_ADU[request_RTU_ADU_length++] = (uint8_t)(crc & 0x00FF);
	built_request_RTU_ADU[request_RTU_ADU_length++] = (uint8_t)(crc >> 8);
}

void RTU_ADU_writeMultipleRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers, uint8_t byte_count/* =N* x 2Byte*/, register_t* registers_value)
{
	request_RTU_ADU_length = 0;
	built_request_RTU_ADU[request_RTU_ADU_length++] = slave_id;

	writeMultipleRegistersRequest(starting_address, quantity_of_registers, byte_count/* =N* x 2Byte*/, registers_value);
	for(uint8_t i = 0; i < request_PDU_length; i++)
	{
		built_request_RTU_ADU[request_RTU_ADU_length++] = built_request_PDU[i];
	}

	uint16_t crc = ModRTU_CRC(built_request_RTU_ADU, request_RTU_ADU_length);
	built_request_RTU_ADU[request_RTU_ADU_length++] = (uint8_t)(crc & 0x00FF);
	built_request_RTU_ADU[request_RTU_ADU_length++] = (uint8_t)(crc >> 8);
}





uint16_t RTU_ADU_getResposeSlaveID(uint8_t* ADU)
{
	return ADU[0];
}

uint16_t RTU_ADU_getCRC(uint8_t* ADU, uint16_t length)
{
	return (((uint16_t)ADU[length-1] << 8) | ADU[length-2]);
}

void RTU_ADU_getPDU(uint8_t* ADU, uint16_t length, uint8_t* PDU_buffer, uint8_t* PDU_length)
{
	for(uint16_t i = 0; i < length-3; i++)
	{
		PDU_buffer[i] = ADU[i+1];
	}

	(*PDU_length) = length - 3;
}






Function_Code RTU_ADU_getFunctionCode(uint8_t* ADU)
{
	return (Function_Code)ADU[1];
}

Exception_Code RTU_ADU_getExceptionCode(uint8_t* ADU)
{
	return (Exception_Code)ADU[2];
}



uint8_t RTU_ADU_getReadCoilByteCount(uint8_t* ADU)
{
	return ADU[2];
}

void RTU_ADU_getReadCoilStatus(uint8_t* ADU, uint8_t length, uint8_t* coil_status_buffer)
{
	for(uint8_t i = 3; i < length; i++)
	{
		coil_status_buffer[i] = ADU[i];
	}
}


uint8_t RTU_ADU_getReadDiscreteInputByteCount(uint8_t* ADU)
{
	return ADU[2];
}

void RTU_ADU_getReadDiscreteInputStatus(uint8_t* ADU, uint8_t length, uint8_t* discrete_input_status_buffer)
{
	for(uint8_t i = 3; i < length; i++)
	{
		discrete_input_status_buffer[i] = ADU[i];
	}
}


uint8_t RTU_ADU_getReadHoldingRegistersByteCount(uint8_t* ADU)
{
	return ADU[2];
}

void RTU_ADU_getReadHoldingRegistersValue(uint8_t* ADU, uint8_t length, register_t* holding_register_value_buffer)
{
	uint8_t num_of_register = RTU_ADU_getReadHoldingRegistersByteCount(ADU)/2;
	for(uint8_t i = 0; i < num_of_register; i++)
	{
		holding_register_value_buffer[i] = (register_t)(((uint16_t)ADU[3 + 2*i] << 8) | (ADU[3 + 2*i + 1]));
	}
}

uint8_t RTU_ADU_getReadHoldingRegistersNumberOfRegister(uint8_t* ADU)
{
	return RTU_ADU_getReadHoldingRegistersByteCount(ADU)/2;
}


uint8_t RTU_ADU_getReadInputRegistersByteCount(uint8_t* ADU)
{
	return ADU[2];
}

void RTU_ADU_getReadInputRegistersValue(uint8_t* ADU, uint8_t length, register_t* input_register_value_buffer)
{
	uint8_t num_of_register = RTU_ADU_getReadInputRegistersByteCount(ADU)/2;
	for(uint8_t i = 0; i < num_of_register; i++)
	{
		input_register_value_buffer[i] = (register_t)(((uint16_t)ADU[3 + 2*i] << 8) | (ADU[3 + 2*i + 1]));
	}
}

uint8_t RTU_ADU_getReadInputRegistersNumberOfRegister(uint8_t* ADU)
{
	return RTU_ADU_getReadInputRegistersByteCount(ADU)/2;
}


uint16_t RTU_ADU_getResponseWriteSingleCoilOutputAddress(uint8_t* ADU)
{
	return (((uint16_t)ADU[2] << 8) | ADU[3]);
}

uint16_t RTU_ADU_getWriteSingleCoilOutputValue(uint8_t* ADU)
{
	return (((uint16_t)ADU[4] << 8) | ADU[5]);
}


uint16_t RTU_ADU_getWriteSingleRegisterOutputAddress(uint8_t* ADU)
{
	return (((uint16_t)ADU[2] << 8) | ADU[3]);
}

uint16_t RTU_ADU_getWriteSingleRegisterOutputValue(uint8_t* ADU)
{
	return (((uint16_t)ADU[4] << 8) | ADU[5]);
}


uint16_t RTU_ADU_getWriteMultipleCoilsStartingAddress(uint8_t* ADU)
{
	return (((uint16_t)ADU[2] << 8) | ADU[3]);
}

uint16_t RTU_ADU_getWriteMultipleCoilsStartingQuantityOfOutputs(uint8_t* ADU)
{
	return (((uint16_t)ADU[4] << 8) | ADU[5]);
}


uint16_t RTU_ADU_getWriteMultipleRegistersStartingAddress(uint8_t* ADU)
{
	return (((uint16_t)ADU[2] << 8) | ADU[3]);
}

uint16_t RTU_ADU_getWriteMultipleRegistersStartingQuantityOfRegisters(uint8_t* ADU)
{
	return (((uint16_t)ADU[4] << 8) | ADU[5]);
}




#endif // __MODBUS_MASTER_RTU__