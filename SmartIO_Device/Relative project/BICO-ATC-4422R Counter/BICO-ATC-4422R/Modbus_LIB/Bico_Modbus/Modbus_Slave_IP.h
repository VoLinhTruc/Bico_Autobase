	#ifndef __MODBUS_SLAVE_IP__
#define __MODBUS_SLAVE_IP__


#include "Modbus_Slave.h"

#ifndef PROTOCOL_ID_0
#define PROTOCOL_ID_0 0 // Presently, I can't specify how many protocols are.
#endif // PROTOCOL_ID_0

#define MAX_RESPONSE_IP_ADU_LENGTH MAX_RESPONSE_PDU_LENGTH+7 // = 2byte Transaction ID + 2byte Protocol Identifier + 2byte Remain length + 1byte for slave ID + MAX_RESPONSE_PDU_LENGTH

uint8_t built_response_IP_ADU[MAX_RESPONSE_IP_ADU_LENGTH];
uint8_t response_IP_ADU_length = 0;



void IP_ADU_ReadCoilsResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, uint8_t byte_count, uint8_t* coil_status);
void IP_ADU_readDiscreteInputsResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, uint8_t byte_count, uint8_t* input_status);
void IP_ADU_readHoldingRegistersResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, uint8_t byte_count, register_t* register_value);
void IP_ADU_readInputRegistersResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, uint8_t byte_count, register_t* input_registers);

void IP_ADU_writeSingleCoilResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, uint16_t output_address, uint16_t output_value);
void IP_ADU_writeSingleRegisterResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, uint16_t register_address, register_t register_value);

void IP_ADU_writeMultipleCoilsResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_outputs);
void IP_ADU_writeMultipleRegistersResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers);





void IP_ADU_functionCodeExceptionResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, uint8_t f_code);

void IP_ADU_readCoilsExceptionResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, Exception_Code e_code);
void IP_ADU_readDiscreteInputsExceptionResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, Exception_Code e_code);
void IP_ADU_readHoldingRegistersExceptionResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, Exception_Code e_code);
void IP_ADU_readInputRegistersExceptionResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, Exception_Code e_code);

void IP_ADU_writeSingleCoilExceptionResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, Exception_Code e_code);
void IP_ADU_writeSingleRegisterExceptionResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, Exception_Code e_code);

void IP_ADU_writeMultipleCoilsExceptionResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, Exception_Code e_code);
void IP_ADU_writeMultipleRegistersExceptionResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, Exception_Code e_code);






void IP_ADU_incomingHandling(uint8_t* ADU, uint16_t length);



void IP_ADU_ReadCoilsResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, uint8_t byte_count, uint8_t* coil_status)
{
	response_IP_ADU_length = 0;
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id & 0x00FF);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id & 0x00FF);

	readCoilsResponse(byte_count, coil_status);
	uint16_t remain_length = sizeof(slave_id) + response_PDU_length;

	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length & 0x00FF);

	built_response_IP_ADU[response_IP_ADU_length++] = slave_id;

	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_IP_ADU[response_IP_ADU_length++] = built_response_PDU[i];
	}
}

void IP_ADU_readDiscreteInputsResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, uint8_t byte_count, uint8_t* input_status)
{
	response_IP_ADU_length = 0;
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id & 0x00FF);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id & 0x00FF);

	readDiscreteInputsResponse(byte_count, input_status);
	uint16_t remain_length = sizeof(slave_id) + response_PDU_length;

	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length & 0x00FF);

	built_response_IP_ADU[response_IP_ADU_length++] = slave_id;

	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_IP_ADU[response_IP_ADU_length++] = built_response_PDU[i];
	}
}

void IP_ADU_readHoldingRegistersResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, uint8_t byte_count, register_t* register_value)
{
	response_IP_ADU_length = 0;
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id & 0x00FF);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id & 0x00FF);

	readHoldingRegistersResponse(byte_count, register_value);
	uint16_t remain_length = sizeof(slave_id) + response_PDU_length;

	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length & 0x00FF);

	built_response_IP_ADU[response_IP_ADU_length++] = slave_id;

	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_IP_ADU[response_IP_ADU_length++] = built_response_PDU[i];
	}
}

void IP_ADU_readInputRegistersResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, uint8_t byte_count, register_t* input_registers)
{
	response_IP_ADU_length = 0;
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id & 0x00FF);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id & 0x00FF);

	readInputRegistersResponse(byte_count, input_registers);
	uint16_t remain_length = sizeof(slave_id) + response_PDU_length;

	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length & 0x00FF);

	built_response_IP_ADU[response_IP_ADU_length++] = slave_id;

	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_IP_ADU[response_IP_ADU_length++] = built_response_PDU[i];
	}
}

void IP_ADU_writeSingleCoilResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, uint16_t output_address, uint16_t output_value)
{
	response_IP_ADU_length = 0;
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id & 0x00FF);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id & 0x00FF);

	writeSingleCoilResponse(output_address, output_value);
	uint16_t remain_length = sizeof(slave_id) + response_PDU_length;

	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length & 0x00FF);

	built_response_IP_ADU[response_IP_ADU_length++] = slave_id;

	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_IP_ADU[response_IP_ADU_length++] = built_response_PDU[i];
	}
}

void IP_ADU_writeSingleRegisterResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, uint16_t register_address, register_t register_value)
{
	response_IP_ADU_length = 0;
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id & 0x00FF);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id & 0x00FF);

	writeSingleRegisterResponse(register_address, register_value);
	uint16_t remain_length = sizeof(slave_id) + response_PDU_length;

	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length & 0x00FF);

	built_response_IP_ADU[response_IP_ADU_length++] = slave_id;

	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_IP_ADU[response_IP_ADU_length++] = built_response_PDU[i];
	}
}

void IP_ADU_writeMultipleCoilsResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_outputs)
{
	response_IP_ADU_length = 0;
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id & 0x00FF);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id & 0x00FF);

	writeMultipleCoilsResponse(starting_address, quantity_of_outputs);
	uint16_t remain_length = sizeof(slave_id) + response_PDU_length;

	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length & 0x00FF);

	built_response_IP_ADU[response_IP_ADU_length++] = slave_id;

	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_IP_ADU[response_IP_ADU_length++] = built_response_PDU[i];
	}
}

void IP_ADU_writeMultipleRegistersResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers)
{
	response_IP_ADU_length = 0;
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id & 0x00FF);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id & 0x00FF);

	writeMultipleRegistersResponse(starting_address, quantity_of_registers);
	uint16_t remain_length = sizeof(slave_id) + response_PDU_length;

	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length & 0x00FF);

	built_response_IP_ADU[response_IP_ADU_length++] = slave_id;

	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_IP_ADU[response_IP_ADU_length++] = built_response_PDU[i];
	}
}






void IP_ADU_functionCodeExceptionResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, uint8_t f_code)
{
	response_IP_ADU_length = 0;
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id & 0x00FF);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id & 0x00FF);

	functionCodeExceptionResponse(f_code);
	uint16_t remain_length = sizeof(slave_id) + response_PDU_length;

	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length & 0x00FF);

	built_response_IP_ADU[response_IP_ADU_length++] = slave_id;

	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_IP_ADU[response_IP_ADU_length++] = built_response_PDU[i];
	}
}

void IP_ADU_readCoilsExceptionResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, Exception_Code e_code)
{
	response_IP_ADU_length = 0;
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id & 0x00FF);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id & 0x00FF);

	readCoilsExceptionResponse(e_code);
	uint16_t remain_length = sizeof(slave_id) + response_PDU_length;

	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length & 0x00FF);

	built_response_IP_ADU[response_IP_ADU_length++] = slave_id;

	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_IP_ADU[response_IP_ADU_length++] = built_response_PDU[i];
	}
}

void IP_ADU_readDiscreteInputsExceptionResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, Exception_Code e_code)
{
	response_IP_ADU_length = 0;
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id & 0x00FF);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id & 0x00FF);

	readDiscreteInputsExceptionResponse(e_code);
	uint16_t remain_length = sizeof(slave_id) + response_PDU_length;

	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length & 0x00FF);

	built_response_IP_ADU[response_IP_ADU_length++] = slave_id;

	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_IP_ADU[response_IP_ADU_length++] = built_response_PDU[i];
	}
}

void IP_ADU_readHoldingRegistersExceptionResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, Exception_Code e_code)
{
	response_IP_ADU_length = 0;
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id & 0x00FF);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id & 0x00FF);

	readHoldingRegistersExceptionResponse(e_code);
	uint16_t remain_length = sizeof(slave_id) + response_PDU_length;

	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length & 0x00FF);

	built_response_IP_ADU[response_IP_ADU_length++] = slave_id;

	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_IP_ADU[response_IP_ADU_length++] = built_response_PDU[i];
	}
}

void IP_ADU_readInputRegistersExceptionResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, Exception_Code e_code)
{
	response_IP_ADU_length = 0;
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id & 0x00FF);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id & 0x00FF);

	readInputRegistersExceptionResponse(e_code);
	uint16_t remain_length = sizeof(slave_id) + response_PDU_length;

	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length & 0x00FF);

	built_response_IP_ADU[response_IP_ADU_length++] = slave_id;

	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_IP_ADU[response_IP_ADU_length++] = built_response_PDU[i];
	}
}

void IP_ADU_writeSingleCoilExceptionResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, Exception_Code e_code)
{
	response_IP_ADU_length = 0;
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id & 0x00FF);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id & 0x00FF);

	writeSingleCoilExceptionResponse(e_code);
	uint16_t remain_length = sizeof(slave_id) + response_PDU_length;

	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length & 0x00FF);

	built_response_IP_ADU[response_IP_ADU_length++] = slave_id;

	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_IP_ADU[response_IP_ADU_length++] = built_response_PDU[i];
	}
}

void IP_ADU_writeSingleRegisterExceptionResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, Exception_Code e_code)
{
	response_IP_ADU_length = 0;
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id & 0x00FF);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id & 0x00FF);

	writeSingleRegisterExceptionResponse(e_code);
	uint16_t remain_length = sizeof(slave_id) + response_PDU_length;

	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length & 0x00FF);

	built_response_IP_ADU[response_IP_ADU_length++] = slave_id;

	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_IP_ADU[response_IP_ADU_length++] = built_response_PDU[i];
	}
}

void IP_ADU_writeMultipleCoilsExceptionResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, Exception_Code e_code)
{
	response_IP_ADU_length = 0;
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id & 0x00FF);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id & 0x00FF);

	writeMultipleCoilsExceptionResponse(e_code);
	uint16_t remain_length = sizeof(slave_id) + response_PDU_length;

	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length & 0x00FF);

	built_response_IP_ADU[response_IP_ADU_length++] = slave_id;

	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_IP_ADU[response_IP_ADU_length++] = built_response_PDU[i];
	}
}

void IP_ADU_writeMultipleRegistersExceptionResponse(uint16_t echo_transaction_id, uint16_t echo_protocol_id, uint8_t slave_id, Exception_Code e_code)
{
	response_IP_ADU_length = 0;
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_transaction_id & 0x00FF);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(echo_protocol_id & 0x00FF);

	writeMultipleRegistersExceptionResponse(e_code);
	uint16_t remain_length = sizeof(slave_id) + response_PDU_length;

	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length >> 8);
	built_response_IP_ADU[response_IP_ADU_length++] = (uint8_t)(remain_length & 0x00FF);

	built_response_IP_ADU[response_IP_ADU_length++] = slave_id;

	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_IP_ADU[response_IP_ADU_length++] = built_response_PDU[i];
	}
}






void IP_ADU_incomingHandling(uint8_t* ADU, uint16_t length)
{
	uint16_t transaction_id = ((uint16_t)ADU[0] << 8) | ADU[1];
	uint16_t protocol_id = ((uint16_t)ADU[2] << 8) | ADU[3];
	uint16_t remain_length = ((uint16_t)ADU[4] << 8) | ADU[5];
	uint8_t incoming_slave_id = ADU[6];

	Function_Code f_code = ADU[7];
	Exception_Code e_code = 0;

	switch(f_code)
	{
		case READ_COILS:
		{
			uint16_t start_address = ((uint16_t)ADU[8] << 8) | ADU[9];
			uint16_t quantity_of_coils = ((uint16_t)ADU[10] << 8) | ADU[11];

			uint8_t byte_count;
			uint8_t coil_status[SLAVE_MAX_DISCRETE_OUTPUT_COIL_IN_BYTE];
			for(uint8_t i = 0; i < SLAVE_MAX_DISCRETE_OUTPUT_COIL_IN_BYTE; i++)
			{
				coil_status[i] = 0;
			}

			if( (quantity_of_coils >= 0x0001) && (quantity_of_coils <= 0x07D0) )
			{
				if( (start_address + quantity_of_coils) < SLAVE_MAX_DISCRETE_OUTPUT_COIL)
				{
					readCoilsRequestHandling(start_address, quantity_of_coils, &byte_count, coil_status);

					IP_ADU_ReadCoilsResponse(transaction_id, protocol_id, slave_device_id, byte_count, coil_status);
				}
				else
				{
					e_code = ILLEGAL_DATA_ADDRESS;
					IP_ADU_readCoilsExceptionResponse(transaction_id, protocol_id, slave_device_id, e_code);
				}
			}
			else
			{
				e_code = ILLEGAL_DATA_VALUE;
				IP_ADU_readCoilsExceptionResponse(transaction_id, protocol_id, slave_device_id, e_code);
			}
			break;
		}

		case READ_DISCRETE_INPUTS:
		{
			uint16_t start_address = ((uint16_t)ADU[8] << 8) | ADU[9];
			uint16_t quantity_of_inputs = ((uint16_t)ADU[10] << 8) | ADU[11];

			uint8_t byte_count;
			uint8_t input_status[SLAVE_MAX_DISCRETE_INPUT_CONTACT_IN_BYTE];
			for(uint8_t i = 0; i < SLAVE_MAX_DISCRETE_INPUT_CONTACT_IN_BYTE; i++)
			{
				input_status[i] = 0;
			}

			if( (quantity_of_inputs >= 0x0001) && (quantity_of_inputs <= 0x07D0) )
			{
				if( (start_address + quantity_of_inputs) < SLAVE_MAX_DISCRETE_INPUT_CONTACT)
				{
					readDiscreteInputsRequestHandling(start_address, quantity_of_inputs, &byte_count, input_status);

					IP_ADU_readDiscreteInputsResponse(transaction_id, protocol_id, slave_device_id, byte_count, input_status);
				}
				else
				{
					e_code = ILLEGAL_DATA_ADDRESS;
					IP_ADU_readDiscreteInputsExceptionResponse(transaction_id, protocol_id, slave_device_id, e_code);
				}
			}
			else
			{
				e_code = ILLEGAL_DATA_VALUE;
				IP_ADU_readDiscreteInputsExceptionResponse(transaction_id, protocol_id, slave_device_id, e_code);
			}
			break;
		}

		case READ_HOLDING_REGISTERS:
		{
			uint16_t starting_address = ((uint16_t)ADU[8] << 8) | ADU[9];
			uint16_t quantity_of_registers = ((uint16_t)ADU[10] << 8) | ADU[11];

			uint8_t byte_count;
			register_t response_register_value[SLAVE_MAX_ANALOG_OUTPUT_HOLDING_REGISTER];

			if( (quantity_of_registers >= 0x0001) && (quantity_of_registers <= 0x007D) )
			{
				if( (starting_address + quantity_of_registers) < SLAVE_MAX_ANALOG_OUTPUT_HOLDING_REGISTER)
				{
					readHoldingRegistersRequestHandling(starting_address, quantity_of_registers, &byte_count, response_register_value);

					IP_ADU_readHoldingRegistersResponse(transaction_id, protocol_id, slave_device_id, byte_count, response_register_value);
				}
				else
				{
					e_code = ILLEGAL_DATA_ADDRESS;
					IP_ADU_readHoldingRegistersExceptionResponse(transaction_id, protocol_id, slave_device_id, e_code);
				}
			}
			else
			{
				e_code = ILLEGAL_DATA_VALUE;
				IP_ADU_readHoldingRegistersExceptionResponse(transaction_id, protocol_id, slave_device_id, e_code);
			}
			break;	
		}

		case READ_INPUT_REGISTERS:
		{
			uint16_t starting_address = ((uint16_t)ADU[8] << 8) | ADU[9];
			uint16_t quantity_of_input_registers = ((uint16_t)ADU[10] << 8) | ADU[11];

			uint8_t byte_count;
			register_t response_input_registers[SLAVE_MAX_ANALOG_INPUT_REGISTER];

			if( (quantity_of_input_registers >= 0x0001) && (quantity_of_input_registers <= 0x007D) )
			{
				if( (starting_address + quantity_of_input_registers) < SLAVE_MAX_ANALOG_INPUT_REGISTER)
				{
					readInputRegistersRequestHandling(starting_address, quantity_of_input_registers, &byte_count, response_input_registers);

					IP_ADU_readInputRegistersResponse(transaction_id, protocol_id, slave_device_id, byte_count, response_input_registers);
				}
				else
				{
					e_code = ILLEGAL_DATA_ADDRESS;
					IP_ADU_readInputRegistersExceptionResponse(transaction_id, protocol_id, slave_device_id, e_code);
				}
			}
			else
			{
				e_code = ILLEGAL_DATA_VALUE;
				IP_ADU_readInputRegistersExceptionResponse(transaction_id, protocol_id, slave_device_id, e_code);
			}
			break;	
		}

		case WRITE_SINGLE_COIL:
		{
			uint16_t request_output_address = ((uint16_t)ADU[8] << 8) | ADU[9];
			uint16_t request_output_value = ((uint16_t)ADU[10] << 8) | ADU[11];

			uint16_t response_output_address;
			uint16_t response_output_value;

			if( (request_output_value == 0x0000) || (request_output_value == 0xFF00) )
			{
				if( request_output_address < SLAVE_MAX_DISCRETE_OUTPUT_COIL)
				{
					writeSingleCoilRequestHandling(request_output_address, request_output_value, &response_output_address, &response_output_value);

					IP_ADU_writeSingleCoilResponse(transaction_id, protocol_id, slave_device_id, response_output_address, response_output_value);
				}
				else
				{
					e_code = ILLEGAL_DATA_ADDRESS;
					IP_ADU_writeSingleCoilExceptionResponse(transaction_id, protocol_id, slave_device_id, e_code);
				}
			}
			else
			{
				e_code = ILLEGAL_DATA_VALUE;
				IP_ADU_writeSingleCoilExceptionResponse(transaction_id, protocol_id, slave_device_id, e_code);
			}
			break;
		}

		case WRITE_SINGLE_REGISTER:
		{
			uint16_t request_register_address = ((uint16_t)ADU[8] << 8) | ADU[9];
			register_t request_register_value = ((uint16_t)ADU[10] << 8) | ADU[11];

			uint16_t response_register_address;
			register_t response_register_value;

			if( (request_register_value >= 0x0000) && (request_register_value <= 0xFFFF) ) // this condition is quite nonsense :v
			{
				if( request_register_address < SLAVE_MAX_ANALOG_OUTPUT_HOLDING_REGISTER)
				{
					writeSingleRegisterHandling(request_register_address, request_register_value, &response_register_address, &response_register_value);

					IP_ADU_writeSingleRegisterResponse(transaction_id, protocol_id, slave_device_id, response_register_address, response_register_value);
				}
				else
				{
					e_code = ILLEGAL_DATA_ADDRESS;
					IP_ADU_writeSingleRegisterExceptionResponse(transaction_id, protocol_id, slave_device_id, e_code);
				}
			}
			else
			{
				e_code = ILLEGAL_DATA_VALUE;
				IP_ADU_writeSingleRegisterExceptionResponse(transaction_id, protocol_id, slave_device_id, e_code);
			}
			break;
		}

		case WRITE_MULTIPLE_COILS:
		{	
			uint16_t request_starting_address = ((uint16_t)ADU[8] << 8) | ADU[9];
			uint16_t request_quantity_of_outputs = ((uint16_t)ADU[10] << 8) | ADU[11];

			uint8_t request_byte_count = ADU[12];
			uint8_t request_output_value[request_byte_count];
			for(uint8_t i = 0; i < request_byte_count; i++)
			{
				request_output_value[i] = ADU[13 + i];
			}

			uint16_t response_starting_address;
			uint16_t response_quantity_of_outputst;
			
			if( (request_quantity_of_outputs >= 0x0001) && (request_quantity_of_outputs <= 0x07B0) && (request_byte_count == (request_quantity_of_outputs/8 + ((request_quantity_of_outputs % 8)? 1:0))) )
			{
				if( request_starting_address +  request_quantity_of_outputs < SLAVE_MAX_DISCRETE_OUTPUT_COIL)
				{
					writeMultipleCoilsRequestHandling(request_starting_address, request_quantity_of_outputs, request_byte_count, request_output_value, &response_starting_address, &response_quantity_of_outputst);					

					IP_ADU_writeMultipleCoilsResponse(transaction_id, protocol_id, slave_device_id, response_starting_address, response_quantity_of_outputst);
				}
				else
				{
					e_code = ILLEGAL_DATA_ADDRESS;
					IP_ADU_writeMultipleCoilsExceptionResponse(transaction_id, protocol_id, slave_device_id, e_code);
				}
			}
			else
			{
				e_code = ILLEGAL_DATA_VALUE;
				IP_ADU_writeMultipleCoilsExceptionResponse(transaction_id, protocol_id, slave_device_id, e_code);
			}
			break;
		}

		case WRITE_MULTIPLE_REGISTERS:
		{
			uint16_t request_starting_address = ((uint16_t)ADU[8] << 8) | ADU[9];
			uint16_t request_quantity_of_registers = ((uint16_t)ADU[10] << 8) | ADU[11];

			uint8_t request_byte_count = ADU[12];
			uint8_t quantity_of_registers = request_byte_count/2;
			register_t request_registers_value[quantity_of_registers];
			for(uint8_t i = 0; i < quantity_of_registers; i++)
			{
				request_registers_value[i] = (register_t)(((uint16_t)ADU[13 + 2*i] << 8) | (ADU[13 + 2*i + 1]));
			}

			uint16_t response_starting_address;
			uint16_t response_quantity_of_registerst;

			if( (request_quantity_of_registers >= 0x0001) && (request_quantity_of_registers <= 0x007B) && (request_byte_count == request_quantity_of_registers * 2) )
			{
				if( request_starting_address +  request_quantity_of_registers < SLAVE_MAX_ANALOG_OUTPUT_HOLDING_REGISTER)
				{
					writeMultipleRegistersRequestHandling(request_starting_address, request_quantity_of_registers, request_byte_count/* =N* x 2Byte*/, request_registers_value, &response_starting_address, &response_quantity_of_registerst);

					IP_ADU_writeMultipleRegistersResponse(transaction_id, protocol_id, slave_device_id, response_starting_address, response_quantity_of_registerst);
				}
				else
				{
					e_code = ILLEGAL_DATA_ADDRESS;
					IP_ADU_readCoilsExceptionResponse(transaction_id, protocol_id, slave_device_id, e_code);
				}
			}
			else
			{
				e_code = ILLEGAL_DATA_VALUE;
				IP_ADU_writeMultipleRegistersExceptionResponse(transaction_id, protocol_id, slave_device_id, e_code);
			}
			break;
		}

		default:
		{
			e_code = ILLEGAL_FUNCTION;
			IP_ADU_writeMultipleRegistersExceptionResponse(transaction_id, protocol_id, slave_device_id, f_code);
		}
	}
}


#endif // __MODBUS_SLAVE_IP__