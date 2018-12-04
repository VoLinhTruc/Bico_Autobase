#ifndef __MODBUS_SLAVE_HANDLING__
#define __MODBUS_SLAVE_HANDLING__

#include "Modbus_Slave.h"

void readCoilsRequestHandling(uint16_t request_starting_address, uint16_t request_quantity_of_coils, uint8_t* response_byte_count, uint8_t* response_coil_status);
void readDiscreteInputsRequestHandling(uint16_t request_starting_address, uint16_t request_quantity_of_inputs, uint8_t* response_byte_count, uint8_t* response_input_status);
void readHoldingRegistersRequestHandling(uint16_t request_starting_address, uint16_t request_quantity_of_registers, uint8_t* response_byte_count, register_t* response_register_value);
void readInputRegistersRequestHandling(uint16_t request_starting_address, uint16_t request_quantity_of_input_registers, uint8_t* response_byte_count, register_t* response_input_registers);

void writeSingleCoilRequestHandling(uint16_t request_output_address, uint16_t request_output_value, uint16_t* response_output_address, uint16_t* response_output_value);
void writeSingleRegisterHandling(uint16_t request_register_address, register_t request_register_value, uint16_t* response_register_address, register_t* response_register_value);

void writeMultipleCoilsRequestHandling(uint16_t request_starting_address, uint16_t request_quantity_of_outputs, uint8_t request_byte_count, uint8_t* request_output_value, uint16_t* response_starting_address, uint16_t* response_quantity_of_outputs);
void writeMultipleRegistersRequestHandling(uint16_t request_starting_address, uint16_t request_quantity_of_registers, uint8_t request_byte_count/* =N* x 2Byte*/, register_t* request_registers_value, uint16_t* response_starting_address, uint16_t* response_quantity_of_registers);



void readCoilsRequestHandling(uint16_t request_starting_address, uint16_t request_quantity_of_coils, uint8_t* response_byte_count, uint8_t* response_coil_status)
{
	for(uint16_t i = 0; i < request_quantity_of_coils; i++)
	{
		uint8_t temp_bit_state = getBitFromArray(slave_discrete_output_coil_list, request_starting_address + i);
		setBitToArray(response_coil_status, i, temp_bit_state);
	}

	(*response_byte_count) = request_quantity_of_coils/8 + ((request_quantity_of_coils%8)? 1:0);
}

void readDiscreteInputsRequestHandling(uint16_t request_starting_address, uint16_t request_quantity_of_inputs, uint8_t* response_byte_count, uint8_t* response_input_status)
{
	for(uint16_t i = 0; i < request_quantity_of_inputs; i++)
	{
		uint8_t temp_bit_state = getBitFromArray(slave_discrete_input_contact_list, request_starting_address + i);
		setBitToArray(response_input_status, i, temp_bit_state);
	}

	(*response_byte_count) = request_quantity_of_inputs/8 + ((request_quantity_of_inputs%8)? 1:0);
}


void readHoldingRegistersRequestHandling(uint16_t request_starting_address, uint16_t request_quantity_of_registers, uint8_t* response_byte_count, register_t* response_register_value)
{
	for(uint16_t i = 0; i < request_quantity_of_registers; i++)
	{
		response_register_value[i] = slave_analog_output_holding_register_list[request_starting_address + i];
	}

	(*response_byte_count) = request_quantity_of_registers*2;
}


void readInputRegistersRequestHandling(uint16_t request_starting_address, uint16_t request_quantity_of_input_registers, uint8_t* response_byte_count, register_t* response_input_registers)
{
	for(uint16_t i = 0; i < request_quantity_of_input_registers; i++)
	{
		response_input_registers[i] = slave_analog_input_register_list[request_starting_address + i];
	}

	(*response_byte_count) = request_quantity_of_input_registers*2;
}



void writeSingleCoilRequestHandling(uint16_t request_output_address, uint16_t request_output_value, uint16_t* response_output_address, uint16_t* response_output_value)
{
	setBitToArray(slave_discrete_output_coil_list, request_output_address, !!(uint8_t)(request_output_value >> 8)); // because request_output_value is 0x0000 or 0xFF00, we must shift 8 bit to right and change 0xFF00 to 0x0001

	(*response_output_address) = request_output_address;
	(*response_output_value) = request_output_value;
}


void writeSingleRegisterHandling(uint16_t request_register_address, register_t request_register_value, uint16_t* response_register_address, register_t* response_register_value)
{
	slave_analog_output_holding_register_list[request_register_address] = request_register_value;

	(*response_register_address) = request_register_address;
	(*response_register_value) = request_register_value;
}



void writeMultipleCoilsRequestHandling(uint16_t request_starting_address, uint16_t request_quantity_of_outputs, uint8_t request_byte_count, uint8_t* request_output_value, uint16_t* response_starting_address, uint16_t* response_quantity_of_outputst)
{
	for(uint16_t i = 0; i < request_quantity_of_outputs; i++)
	{
		uint8_t temp_bit_state = getBitFromArray(request_output_value, i);
		setBitToArray(slave_discrete_output_coil_list, request_starting_address + i, temp_bit_state);
	}

	(*response_starting_address) = request_starting_address;
	(*response_quantity_of_outputst) = request_quantity_of_outputs;
}


void writeMultipleRegistersRequestHandling(uint16_t request_starting_address, uint16_t request_quantity_of_registers, uint8_t request_byte_count/* =N* x 2Byte*/, register_t* request_registers_value, uint16_t* response_starting_address, uint16_t* response_quantity_of_registerst)
{
	uint8_t quantity_of_registers = request_byte_count/2;
	for(uint16_t i = 0; i < quantity_of_registers; i++)
	{
		slave_analog_output_holding_register_list[request_starting_address + i] = request_registers_value[i];
	}

	(*response_starting_address) = request_starting_address;
	(*response_quantity_of_registerst) = request_quantity_of_registers;
}





#endif // __MODBUS_SLAVE_HANDLING__
