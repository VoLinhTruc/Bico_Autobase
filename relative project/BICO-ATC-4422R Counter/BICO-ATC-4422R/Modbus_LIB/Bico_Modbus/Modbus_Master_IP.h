#ifndef __MODBUS_MASTER_IP__
#define __MODBUS_MASTER_IP__


#include "Modbus_Master.h"

#ifndef PROTOCOL_ID_0
#define PROTOCOL_ID_0 0 // Presently, I can't specify how many protocols are.
#endif // PROTOCOL_ID_0

#define MAX_REQUEST_IP_ADU_LENGTH MAX_REQUEST_PDU_LENGTH+7 // = 2byte Transaction ID + 2byte Protocol Identifier + 2byte Remain length + 1byte for slave ID + MAX_REQUEST_PDU_LENGTH

uint8_t built_request_IP_ADU[MAX_REQUEST_IP_ADU_LENGTH];
uint8_t request_IP_ADU_length = 0;
uint16_t transaction_id = 0;
uint16_t protocol_id = PROTOCOL_ID_0;


void IP_ADU_readCoilsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_coils);
void IP_ADU_readDiscreteInputsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_inputs);
void IP_ADU_readHoldingRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers);
void IP_ADU_readInputRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_input_registers);

void IP_ADU_writeSingleCoilRequest(uint8_t slave_id, uint16_t output_address, uint16_t output_value);
void IP_ADU_writeSingleRegisterRequest(uint8_t slave_id, uint16_t register_address, register_t register_value);

void IP_ADU_writeMultipleCoilsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_outputs, uint8_t byte_count, uint8_t* output_value);
void IP_ADU_writeMultipleRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers, uint8_t byte_count/* =N* x 2Byte*/, register_t* registers_value);





uint16_t IP_ADU_getTransactionID(uint8_t* ADU);
uint16_t IP_ADU_getResposeSlaveID(uint8_t* ADU);
void IP_ADU_getPDU(uint8_t* ADU, uint16_t length, uint8_t* PDU_buffer, uint8_t* PDU_length);



Function_Code IP_ADU_getFunctionCode(uint8_t* ADU);
Exception_Code IP_ADU_getExceptionCode(uint8_t* ADU);


uint8_t IP_ADU_getReadCoilByteCount(uint8_t* ADU);
void IP_ADU_getReadCoilStatus(uint8_t* ADU, uint8_t length, uint8_t* coil_status_buffer);

uint8_t IP_ADU_getReadDiscreteInputByteCount(uint8_t* ADU);
void IP_ADU_getReadDiscreteInputStatus(uint8_t* ADU, uint8_t length, uint8_t* discrete_input_status_buffer);

uint8_t IP_ADU_getReadHoldingRegistersByteCount(uint8_t* ADU);
void IP_ADU_getReadHoldingRegistersValue(uint8_t* ADU, uint8_t length, register_t* holding_register_value_buffer);
uint8_t IP_ADU_getReadHoldingRegistersNumberOfRegister(uint8_t* ADU);

uint8_t IP_ADU_getReadInputRegistersByteCount(uint8_t* ADU);
void IP_ADU_getReadInputRegistersValue(uint8_t* ADU, uint8_t length, register_t* input_register_value_buffer);
uint8_t IP_ADU_getReadInputRegistersNumberOfRegister(uint8_t* ADU);


uint16_t IP_ADU_getResponseWriteSingleCoilOutputAddress(uint8_t* ADU);
uint16_t IP_ADU_getWriteSingleCoilOutputValue(uint8_t* ADU);

uint16_t IP_ADU_getWriteSingleRegisterOutputAddress(uint8_t* ADU);
uint16_t IP_ADU_getWriteSingleRegisterOutputValue(uint8_t* ADU);

uint16_t IP_ADU_getWriteMultipleCoilsStartingAddress(uint8_t* ADU);
uint16_t IP_ADU_getWriteMultipleCoilsStartingQuantityOfOutputs(uint8_t* ADU);

uint16_t IP_ADU_getWriteMultipleRegistersStartingAddress(uint8_t* ADU);
uint16_t IP_ADU_getWriteMultipleRegistersStartingQuantityOfRegisters(uint8_t* ADU);






void IP_ADU_readCoilsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_coils)
{
	request_IP_ADU_length = 0;
	built_request_IP_ADU[request_IP_ADU_length++] = 
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(transaction_id & 0x00FF);
	transaction_id++;

	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(protocol_id >> 8);
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(protocol_id & 0x00FF);

	readCoilsRequest(starting_address, quantity_of_coils);
	uint16_t remain_length = sizeof(slave_id) + request_PDU_length;

	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(remain_length >> 8);
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(remain_length & 0x00FF);

	built_request_IP_ADU[request_IP_ADU_length++] = slave_id;

	for(uint8_t i = 0; i < request_PDU_length; i++)
	{
		built_request_IP_ADU[request_IP_ADU_length++] = built_request_PDU[i];
	}
}

void IP_ADU_readDiscreteInputsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_inputs)
{
	request_IP_ADU_length = 0;
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(transaction_id >> 8);
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(transaction_id & 0x00FF);
	transaction_id++;

	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(protocol_id >> 8);
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(protocol_id & 0x00FF);

	readDiscreteInputsRequest(starting_address, quantity_of_inputs);
	uint16_t remain_length = sizeof(slave_id) + request_PDU_length;

	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(remain_length >> 8);
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(remain_length & 0x00FF);

	built_request_IP_ADU[request_IP_ADU_length++] = slave_id;

	for(uint8_t i = 0; i < request_PDU_length; i++)
	{
		built_request_IP_ADU[request_IP_ADU_length++] = built_request_PDU[i];
	}
}

void IP_ADU_readHoldingRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers)
{
	request_IP_ADU_length = 0;
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(transaction_id >> 8);
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(transaction_id & 0x00FF);
	transaction_id++;

	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(protocol_id >> 8);
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(protocol_id & 0x00FF);

	readHoldingRegistersRequest(starting_address, quantity_of_registers);
	uint16_t remain_length = sizeof(slave_id) + request_PDU_length;

	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(remain_length >> 8);
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(remain_length & 0x00FF);

	built_request_IP_ADU[request_IP_ADU_length++] = slave_id;

	for(uint8_t i = 0; i < request_PDU_length; i++)
	{
		built_request_IP_ADU[request_IP_ADU_length++] = built_request_PDU[i];
	}
}

void IP_ADU_readInputRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_input_registers)
{
	request_IP_ADU_length = 0;
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(transaction_id >> 8);
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(transaction_id & 0x00FF);
	transaction_id++;

	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(protocol_id >> 8);
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(protocol_id & 0x00FF);

	readInputRegistersRequest(starting_address, quantity_of_input_registers);
	uint16_t remain_length = sizeof(slave_id) + request_PDU_length;

	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(remain_length >> 8);
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(remain_length & 0x00FF);

	built_request_IP_ADU[request_IP_ADU_length++] = slave_id;

	for(uint8_t i = 0; i < request_PDU_length; i++)
	{
		built_request_IP_ADU[request_IP_ADU_length++] = built_request_PDU[i];
	}
}

void IP_ADU_writeSingleCoilRequest(uint8_t slave_id, uint16_t output_address, uint16_t output_value)
{
	request_IP_ADU_length = 0;
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(transaction_id >> 8);
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(transaction_id & 0x00FF);
	transaction_id++;

	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(protocol_id >> 8);
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(protocol_id & 0x00FF);

	writeSingleCoilRequest(output_address, output_value);
	uint16_t remain_length = sizeof(slave_id) + request_PDU_length;

	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(remain_length >> 8);
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(remain_length & 0x00FF);

	built_request_IP_ADU[request_IP_ADU_length++] = slave_id;

	for(uint8_t i = 0; i < request_PDU_length; i++)
	{
		built_request_IP_ADU[request_IP_ADU_length++] = built_request_PDU[i];
	}
}

void IP_ADU_writeSingleRegisterRequest(uint8_t slave_id, uint16_t register_address, register_t register_value)
{
	request_IP_ADU_length = 0;
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(transaction_id >> 8);
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(transaction_id & 0x00FF);
	transaction_id++;

	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(protocol_id >> 8);
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(protocol_id & 0x00FF);

	writeSingleRegisterRequest(register_address, register_value);
	uint16_t remain_length = sizeof(slave_id) + request_PDU_length;

	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(remain_length >> 8);
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(remain_length & 0x00FF);

	built_request_IP_ADU[request_IP_ADU_length++] = slave_id;

	for(uint8_t i = 0; i < request_PDU_length; i++)
	{
		built_request_IP_ADU[request_IP_ADU_length++] = built_request_PDU[i];
	}
}

void IP_ADU_writeMultipleCoilsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_outputs, uint8_t byte_count, uint8_t* output_value)
{
	request_IP_ADU_length = 0;
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(transaction_id >> 8);
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(transaction_id & 0x00FF);
	transaction_id++;

	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(protocol_id >> 8);
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(protocol_id & 0x00FF);

	writeMultipleCoilsRequest(starting_address, quantity_of_outputs, byte_count, output_value);
	uint16_t remain_length = sizeof(slave_id) + request_PDU_length;

	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(remain_length >> 8);
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(remain_length & 0x00FF);

	built_request_IP_ADU[request_IP_ADU_length++] = slave_id;

	for(uint8_t i = 0; i < request_PDU_length; i++)
	{
		built_request_IP_ADU[request_IP_ADU_length++] = built_request_PDU[i];
	}
}

void IP_ADU_writeMultipleRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers, uint8_t byte_count/* =N* x 2Byte*/, register_t* registers_value)
{
	request_IP_ADU_length = 0;
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(transaction_id >> 8);
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(transaction_id & 0x00FF);
	transaction_id++;

	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(protocol_id >> 8);
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(protocol_id & 0x00FF);

	writeMultipleRegistersRequest(starting_address, quantity_of_registers, byte_count/* =N* x 2Byte*/, registers_value);
	uint16_t remain_length = sizeof(slave_id) + request_PDU_length;

	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(remain_length >> 8);
	built_request_IP_ADU[request_IP_ADU_length++] = (uint8_t)(remain_length & 0x00FF);

	built_request_IP_ADU[request_IP_ADU_length++] = slave_id;

	for(uint8_t i = 0; i < request_PDU_length; i++)
	{
		built_request_IP_ADU[request_IP_ADU_length++] = built_request_PDU[i];
	}
}







uint16_t IP_ADU_getTransactionID(uint8_t* ADU)
{
	return (((uint16_t)ADU[0] << 8) | ADU[1]);
}

uint16_t IP_ADU_getResposeSlaveID(uint8_t* ADU)
{
	return ADU[6];
}

void IP_ADU_getPDU(uint8_t* ADU, uint16_t length, uint8_t* PDU_buffer, uint8_t* PDU_length)
{
	for(uint16_t i = 0; i < length-7; i++)
	{
		PDU_buffer[i] = ADU[i+7];
	}

	(*PDU_length) = length - 7;
}



Function_Code IP_ADU_getFunctionCode(uint8_t* ADU)
{
	return (Function_Code)ADU[7];
}

Exception_Code IP_ADU_getExceptionCode(uint8_t* ADU)
{
	return (Exception_Code)ADU[8];
}



uint8_t IP_ADU_getReadCoilByteCount(uint8_t* ADU)
{
	return ADU[8];
}

void IP_ADU_getReadCoilStatus(uint8_t* ADU, uint8_t length, uint8_t* coil_status_buffer)
{
	for(uint8_t i = 9; i < length; i++)
	{
		coil_status_buffer[i] = ADU[i];
	}
}


uint8_t IP_ADU_getReadDiscreteInputByteCount(uint8_t* ADU)
{
	return ADU[8];
}

void IP_ADU_getReadDiscreteInputStatus(uint8_t* ADU, uint8_t length, uint8_t* discrete_input_status_buffer)
{
	for(uint8_t i = 9; i < length; i++)
	{
		discrete_input_status_buffer[i] = ADU[i];
	}
}


uint8_t IP_ADU_getReadHoldingRegistersByteCount(uint8_t* ADU)
{
	return ADU[8];
}

void IP_ADU_getReadHoldingRegistersValue(uint8_t* ADU, uint8_t length, register_t* holding_register_value_buffer)
{
	uint8_t num_of_register = IP_ADU_getReadHoldingRegistersByteCount(ADU)/2;
	for(uint8_t i = 0; i < num_of_register; i++)
	{
		holding_register_value_buffer[i] = (register_t)(((uint16_t)ADU[9 + 2*i] << 8) | (ADU[9 + 2*i + 1]));
	}
}

uint8_t IP_ADU_getReadHoldingRegistersNumberOfRegister(uint8_t* ADU)
{
	return IP_ADU_getReadHoldingRegistersByteCount(ADU)/2;
}


uint8_t IP_ADU_getReadInputRegistersByteCount(uint8_t* ADU)
{
	return ADU[8];
}

void IP_ADU_getReadInputRegistersValue(uint8_t* ADU, uint8_t length, register_t* input_register_value_buffer)
{
	uint8_t num_of_register = IP_ADU_getReadInputRegistersByteCount(ADU)/2;
	for(uint8_t i = 0; i < num_of_register; i++)
	{
		input_register_value_buffer[i] = (register_t)(((uint16_t)ADU[9 + 2*i] << 8) | (ADU[9 + 2*i + 1]));
	}
}

uint8_t IP_ADU_getReadInputRegistersNumberOfRegister(uint8_t* ADU)
{
	return IP_ADU_getReadInputRegistersByteCount(ADU)/2;
}


uint16_t IP_ADU_getResponseWriteSingleCoilOutputAddress(uint8_t* ADU)
{
	return (((uint16_t)ADU[8] << 8) | ADU[9]);
}

uint16_t IP_ADU_getWriteSingleCoilOutputValue(uint8_t* ADU)
{
	return (((uint16_t)ADU[10] << 8) | ADU[11]);
}


uint16_t IP_ADU_getWriteSingleRegisterOutputAddress(uint8_t* ADU)
{
	return (((uint16_t)ADU[8] << 8) | ADU[9]);
}

uint16_t IP_ADU_getWriteSingleRegisterOutputValue(uint8_t* ADU)
{
	return (((uint16_t)ADU[10] << 8) | ADU[11]);
}


uint16_t IP_ADU_getWriteMultipleCoilsStartingAddress(uint8_t* ADU)
{
	return (((uint16_t)ADU[8] << 8) | ADU[9]);
}

uint16_t IP_ADU_getWriteMultipleCoilsStartingQuantityOfOutputs(uint8_t* ADU)
{
	return (((uint16_t)ADU[10] << 8) | ADU[11]);
}


uint16_t IP_ADU_getWriteMultipleRegistersStartingAddress(uint8_t* ADU)
{
	return (((uint16_t)ADU[8] << 8) | ADU[9]);
}

uint16_t IP_ADU_getWriteMultipleRegistersStartingQuantityOfRegisters(uint8_t* ADU)
{
	return (((uint16_t)ADU[10] << 8) | ADU[11]);
}



#endif // __MODBUS_MASTER_IP__