#ifndef __MODBUS_SLAVE_RTU__
#define __MODBUS_SLAVE_RTU__


#include "Modbus_Slave.h"

#define MAX_RESPONSE_RTU_ADU_LENGTH MAX_RESPONSE_PDU_LENGTH+3 // = 1byte for slave ID + MAX_RESPONSE_PDU_LENGTH + 2byte for CRC


uint8_t built_response_RTU_ADU[MAX_RESPONSE_PDU_LENGTH];
uint8_t response_RTU_ADU_length = 0;




void RTU_ADU_readCoilsResponse(uint8_t slave_id, uint8_t byte_count, uint8_t* coil_status);
void RTU_ADU_readDiscreteInputsResponse(uint8_t slave_id, uint8_t byte_count, uint8_t* input_status);
void RTU_ADU_readHoldingRegistersResponse(uint8_t slave_id, uint8_t byte_count, register_t* register_value);
void RTU_ADU_readInputRegistersResponse(uint8_t slave_id, uint8_t byte_count, register_t* input_registers);

void RTU_ADU_writeSingleCoilResponse(uint8_t slave_id, uint16_t output_address, uint16_t output_value);
void RTU_ADU_writeSingleRegisterResponse(uint8_t slave_id, uint16_t register_address, register_t register_value);

void RTU_ADU_writeMultipleCoilsResponse(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_outputs);
void RTU_ADU_writeMultipleRegistersResponse(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers);



void RTU_ADU_functionCodeExceptionResponse(uint8_t slave_id, uint8_t f_code);

void RTU_ADU_readCoilsExceptionResponse(uint8_t slave_id, Exception_Code e_code);
void RTU_ADU_readDiscreteInputsExceptionResponse(uint8_t slave_id, Exception_Code e_code);
void RTU_ADU_readHoldingRegistersExceptionResponse(uint8_t slave_id, Exception_Code e_code);
void RTU_ADU_readInputRegistersExceptionResponse(uint8_t slave_id, Exception_Code e_code);

void RTU_ADU_writeSingleCoilExceptionResponse(uint8_t slave_id, Exception_Code e_code);
void RTU_ADU_writeSingleRegisterExceptionResponse(uint8_t slave_id, Exception_Code e_code);

void RTU_ADU_writeMultipleCoilsExceptionResponse(uint8_t slave_id, Exception_Code e_code);
void RTU_ADU_writeMultipleRegistersExceptionResponse(uint8_t slave_id, Exception_Code e_code);



void RTU_ADU_incomingHandling(uint8_t* ADU, uint16_t length);




void RTU_ADU_readCoilsResponse(uint8_t slave_id, uint8_t byte_count, uint8_t* coil_status)
{
	response_RTU_ADU_length = 0;
	built_response_RTU_ADU[response_RTU_ADU_length++] = slave_id;

	readCoilsResponse(byte_count, coil_status);
	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_RTU_ADU[response_RTU_ADU_length++] = built_response_PDU[i];
	}

	uint16_t crc = ModRTU_CRC(built_response_RTU_ADU, response_RTU_ADU_length);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc & 0x00FF);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc >> 8);
}

void RTU_ADU_readDiscreteInputsResponse(uint8_t slave_id, uint8_t byte_count, uint8_t* input_status)
{
	response_RTU_ADU_length = 0;
	built_response_RTU_ADU[response_RTU_ADU_length++] = slave_id;

	readDiscreteInputsResponse(byte_count, input_status);
	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_RTU_ADU[response_RTU_ADU_length++] = built_response_PDU[i];
	}

	uint16_t crc = ModRTU_CRC(built_response_RTU_ADU, response_RTU_ADU_length);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc & 0x00FF);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc >> 8);
}

void RTU_ADU_readHoldingRegistersResponse(uint8_t slave_id, uint8_t byte_count, register_t* register_value)
{
	response_RTU_ADU_length = 0;
	built_response_RTU_ADU[response_RTU_ADU_length++] = slave_id;

	readHoldingRegistersResponse(byte_count, register_value);
	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_RTU_ADU[response_RTU_ADU_length++] = built_response_PDU[i];
	}

	uint16_t crc = ModRTU_CRC(built_response_RTU_ADU, response_RTU_ADU_length);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc & 0x00FF);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc >> 8);
}

void RTU_ADU_readInputRegistersResponse(uint8_t slave_id, uint8_t byte_count, register_t* input_registers)
{
	response_RTU_ADU_length = 0;
	built_response_RTU_ADU[response_RTU_ADU_length++] = slave_id;

	readInputRegistersResponse(byte_count, input_registers);
	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_RTU_ADU[response_RTU_ADU_length++] = built_response_PDU[i];
	}

	uint16_t crc = ModRTU_CRC(built_response_RTU_ADU, response_RTU_ADU_length);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc & 0x00FF);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc >> 8);
}

void RTU_ADU_writeSingleCoilResponse(uint8_t slave_id, uint16_t output_address, uint16_t output_value)
{
	response_RTU_ADU_length = 0;
	built_response_RTU_ADU[response_RTU_ADU_length++] = slave_id;

	writeSingleCoilResponse(output_address, output_value);
	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_RTU_ADU[response_RTU_ADU_length++] = built_response_PDU[i];
	}

	uint16_t crc = ModRTU_CRC(built_response_RTU_ADU, response_RTU_ADU_length);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc & 0x00FF);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc >> 8);
}

void RTU_ADU_writeSingleRegisterResponse(uint8_t slave_id, uint16_t register_address, register_t register_value)
{
	response_RTU_ADU_length = 0;
	built_response_RTU_ADU[response_RTU_ADU_length++] = slave_id;

	writeSingleRegisterResponse(register_address, register_value);
	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_RTU_ADU[response_RTU_ADU_length++] = built_response_PDU[i];
	}

	uint16_t crc = ModRTU_CRC(built_response_RTU_ADU, response_RTU_ADU_length);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc & 0x00FF);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc >> 8);
}

void RTU_ADU_writeMultipleCoilsResponse(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_outputs)
{
	response_RTU_ADU_length = 0;
	built_response_RTU_ADU[response_RTU_ADU_length++] = slave_id;

	writeMultipleCoilsResponse(starting_address, quantity_of_outputs);
	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_RTU_ADU[response_RTU_ADU_length++] = built_response_PDU[i];
	}

	uint16_t crc = ModRTU_CRC(built_response_RTU_ADU, response_RTU_ADU_length);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc & 0x00FF);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc >> 8);
}

void RTU_ADU_writeMultipleRegistersResponse(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers)
{
	response_RTU_ADU_length = 0;
	built_response_RTU_ADU[response_RTU_ADU_length++] = slave_id;

	writeMultipleRegistersResponse(starting_address, quantity_of_registers);
	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_RTU_ADU[response_RTU_ADU_length++] = built_response_PDU[i];
	}

	uint16_t crc = ModRTU_CRC(built_response_RTU_ADU, response_RTU_ADU_length);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc & 0x00FF);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc >> 8);
}




void RTU_ADU_functionCodeExceptionResponse(uint8_t slave_id, uint8_t f_code)
{
	response_RTU_ADU_length = 0;
	built_response_RTU_ADU[response_RTU_ADU_length++] = slave_id;

	functionCodeExceptionResponse(f_code);
	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_RTU_ADU[response_RTU_ADU_length++] = built_response_PDU[i];
	}

	uint16_t crc = ModRTU_CRC(built_response_RTU_ADU, response_RTU_ADU_length);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc & 0x00FF);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc >> 8);
}

void RTU_ADU_readCoilsExceptionResponse(uint8_t slave_id, Exception_Code e_code)
{
	response_RTU_ADU_length = 0;
	built_response_RTU_ADU[response_RTU_ADU_length++] = slave_id;

	readCoilsExceptionResponse(e_code);
	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_RTU_ADU[response_RTU_ADU_length++] = built_response_PDU[i];
	}

	uint16_t crc = ModRTU_CRC(built_response_RTU_ADU, response_RTU_ADU_length);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc & 0x00FF);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc >> 8);
}

void RTU_ADU_readDiscreteInputsExceptionResponse(uint8_t slave_id, Exception_Code e_code)
{
	response_RTU_ADU_length = 0;
	built_response_RTU_ADU[response_RTU_ADU_length++] = slave_id;

	readDiscreteInputsExceptionResponse(e_code);
	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_RTU_ADU[response_RTU_ADU_length++] = built_response_PDU[i];
	}

	uint16_t crc = ModRTU_CRC(built_response_RTU_ADU, response_RTU_ADU_length);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc & 0x00FF);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc >> 8);
}

void RTU_ADU_readHoldingRegistersExceptionResponse(uint8_t slave_id, Exception_Code e_code)
{
	response_RTU_ADU_length = 0;
	built_response_RTU_ADU[response_RTU_ADU_length++] = slave_id;

	readHoldingRegistersExceptionResponse(e_code);
	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_RTU_ADU[response_RTU_ADU_length++] = built_response_PDU[i];
	}

	uint16_t crc = ModRTU_CRC(built_response_RTU_ADU, response_RTU_ADU_length);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc & 0x00FF);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc >> 8);
}

void RTU_ADU_readInputRegistersExceptionResponse(uint8_t slave_id, Exception_Code e_code)
{
	response_RTU_ADU_length = 0;
	built_response_RTU_ADU[response_RTU_ADU_length++] = slave_id;

	readInputRegistersExceptionResponse(e_code);
	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_RTU_ADU[response_RTU_ADU_length++] = built_response_PDU[i];
	}

	uint16_t crc = ModRTU_CRC(built_response_RTU_ADU, response_RTU_ADU_length);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc & 0x00FF);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc >> 8);
}

void RTU_ADU_writeSingleCoilExceptionResponse(uint8_t slave_id, Exception_Code e_code)
{
	response_RTU_ADU_length = 0;
	built_response_RTU_ADU[response_RTU_ADU_length++] = slave_id;

	writeSingleCoilExceptionResponse(e_code);
	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_RTU_ADU[response_RTU_ADU_length++] = built_response_PDU[i];
	}

	uint16_t crc = ModRTU_CRC(built_response_RTU_ADU, response_RTU_ADU_length);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc & 0x00FF);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc >> 8);
}

void RTU_ADU_writeSingleRegisterExceptionResponse(uint8_t slave_id, Exception_Code e_code)
{
	response_RTU_ADU_length = 0;
	built_response_RTU_ADU[response_RTU_ADU_length++] = slave_id;

	writeSingleRegisterExceptionResponse(e_code);
	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_RTU_ADU[response_RTU_ADU_length++] = built_response_PDU[i];
	}

	uint16_t crc = ModRTU_CRC(built_response_RTU_ADU, response_RTU_ADU_length);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc & 0x00FF);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc >> 8);
}

void RTU_ADU_writeMultipleCoilsExceptionResponse(uint8_t slave_id, Exception_Code e_code)
{
	response_RTU_ADU_length = 0;
	built_response_RTU_ADU[response_RTU_ADU_length++] = slave_id;

	writeMultipleCoilsExceptionResponse(e_code);
	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_RTU_ADU[response_RTU_ADU_length++] = built_response_PDU[i];
	}

	uint16_t crc = ModRTU_CRC(built_response_RTU_ADU, response_RTU_ADU_length);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc & 0x00FF);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc >> 8);
}

void RTU_ADU_writeMultipleRegistersExceptionResponse(uint8_t slave_id, Exception_Code e_code)
{
	response_RTU_ADU_length = 0;
	built_response_RTU_ADU[response_RTU_ADU_length++] = slave_id;

	writeMultipleRegistersExceptionResponse(e_code);
	for(uint8_t i = 0; i < response_PDU_length; i++)
	{
		built_response_RTU_ADU[response_RTU_ADU_length++] = built_response_PDU[i];
	}

	uint16_t crc = ModRTU_CRC(built_response_RTU_ADU, response_RTU_ADU_length);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc & 0x00FF);
	built_response_RTU_ADU[response_RTU_ADU_length++] = (uint8_t)(crc >> 8);
}




void RTU_ADU_incomingHandling(uint8_t* ADU, uint16_t length)
{
	uint8_t incoming_slave_id = ADU[0];
	uint16_t receive_crc = ((uint16_t)ADU[length-1] << 8) | ADU[length-2];
	uint16_t caculated_crc = ModRTU_CRC(ADU, length-2);

	if(incoming_slave_id == slave_device_id)
	{
		if(receive_crc == caculated_crc)
		{
			Function_Code f_code = ADU[1];
			Exception_Code e_code = 0;

			switch(f_code)
			{
				case READ_COILS:
				{
					uint16_t start_address = ((uint16_t)ADU[2] << 8) | ADU[3];
					uint16_t quantity_of_coils = ((uint16_t)ADU[4] << 8) | ADU[5];

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

							RTU_ADU_readCoilsResponse(slave_device_id, byte_count, coil_status);
						}
						else
						{
							e_code = ILLEGAL_DATA_ADDRESS;
							RTU_ADU_readCoilsExceptionResponse(slave_device_id, e_code);
						}
					}
					else
					{
						e_code = ILLEGAL_DATA_VALUE;
						RTU_ADU_readCoilsExceptionResponse(slave_device_id, e_code);
					}
					break;
				}

				case READ_DISCRETE_INPUTS:
				{
					uint16_t start_address = ((uint16_t)ADU[2] << 8) | ADU[3];
					uint16_t quantity_of_inputs = ((uint16_t)ADU[4] << 8) | ADU[5];

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

							RTU_ADU_readDiscreteInputsResponse(slave_device_id, byte_count, input_status);
						}
						else
						{
							e_code = ILLEGAL_DATA_ADDRESS;
							RTU_ADU_readDiscreteInputsExceptionResponse(slave_device_id, e_code);
						}
					}
					else
					{
						e_code = ILLEGAL_DATA_VALUE;
						RTU_ADU_readDiscreteInputsExceptionResponse(slave_device_id, e_code);
					}
					break;
				}

				case READ_HOLDING_REGISTERS:
				{
					uint16_t starting_address = ((uint16_t)ADU[2] << 8) | ADU[3];
					uint16_t quantity_of_registers = ((uint16_t)ADU[4] << 8) | ADU[5];

					uint8_t byte_count;
					register_t response_register_value[SLAVE_MAX_ANALOG_OUTPUT_HOLDING_REGISTER];

					if( (quantity_of_registers >= 0x0001) && (quantity_of_registers <= 0x007D) )
					{
						if( (starting_address + quantity_of_registers) < SLAVE_MAX_ANALOG_OUTPUT_HOLDING_REGISTER)
						{
							readHoldingRegistersRequestHandling(starting_address, quantity_of_registers, &byte_count, response_register_value);

							RTU_ADU_readHoldingRegistersResponse(slave_device_id, byte_count, response_register_value);
						}
						else
						{
							e_code = ILLEGAL_DATA_ADDRESS;
							RTU_ADU_readHoldingRegistersExceptionResponse(slave_device_id, e_code);
						}
					}
					else
					{
						e_code = ILLEGAL_DATA_VALUE;
						RTU_ADU_readHoldingRegistersExceptionResponse(slave_device_id, e_code);
					}
					break;	
				}

				case READ_INPUT_REGISTERS:
				{
					uint16_t starting_address = ((uint16_t)ADU[2] << 8) | ADU[3];
					uint16_t quantity_of_input_registers = ((uint16_t)ADU[4] << 8) | ADU[5];

					uint8_t byte_count;
					register_t response_input_registers[SLAVE_MAX_ANALOG_INPUT_REGISTER];

					if( (quantity_of_input_registers >= 0x0001) && (quantity_of_input_registers <= 0x007D) )
					{
						if( (starting_address + quantity_of_input_registers) < SLAVE_MAX_ANALOG_INPUT_REGISTER)
						{
							readInputRegistersRequestHandling(starting_address, quantity_of_input_registers, &byte_count, response_input_registers);

							RTU_ADU_readInputRegistersResponse(slave_device_id, byte_count, response_input_registers);
						}
						else
						{
							e_code = ILLEGAL_DATA_ADDRESS;
							RTU_ADU_readInputRegistersExceptionResponse(slave_device_id, e_code);
						}
					}
					else
					{
						e_code = ILLEGAL_DATA_VALUE;
						RTU_ADU_readInputRegistersExceptionResponse(slave_device_id, e_code);
					}
					break;	
				}

				case WRITE_SINGLE_COIL:
				{
					uint16_t request_output_address = ((uint16_t)ADU[2] << 8) | ADU[3];
					uint16_t request_output_value = ((uint16_t)ADU[4] << 8) | ADU[5];

					uint16_t response_output_address;
					uint16_t response_output_value;

					if( (request_output_value == 0x0000) || (request_output_value == 0xFF00) )
					{
						if( request_output_address < SLAVE_MAX_DISCRETE_OUTPUT_COIL)
						{
							writeSingleCoilRequestHandling(request_output_address, request_output_value, &response_output_address, &response_output_value);

							RTU_ADU_writeSingleCoilResponse(slave_device_id, response_output_address, response_output_value);
						}
						else
						{
							e_code = ILLEGAL_DATA_ADDRESS;
							RTU_ADU_writeSingleCoilExceptionResponse(slave_device_id, e_code);
						}
					}
					else
					{
						e_code = ILLEGAL_DATA_VALUE;
						RTU_ADU_writeSingleCoilExceptionResponse(slave_device_id, e_code);
					}
					break;
				}

				case WRITE_SINGLE_REGISTER:
				{
					uint16_t request_register_address = ((uint16_t)ADU[2] << 8) | ADU[3];
					register_t request_register_value = ((uint16_t)ADU[4] << 8) | ADU[5];

					uint16_t response_register_address;
					register_t response_register_value;

					if( (request_register_value >= 0x0000) && (request_register_value <= 0xFFFF) ) // this condition is quite nonsense :v
					{
						if( request_register_address < SLAVE_MAX_ANALOG_OUTPUT_HOLDING_REGISTER)
						{
							writeSingleRegisterHandling(request_register_address, request_register_value, &response_register_address, &response_register_value);

							RTU_ADU_writeSingleRegisterResponse(slave_device_id, response_register_address, response_register_value);
						}
						else
						{
							e_code = ILLEGAL_DATA_ADDRESS;
							RTU_ADU_writeSingleRegisterExceptionResponse(slave_device_id, e_code);
						}
					}
					else
					{
						e_code = ILLEGAL_DATA_VALUE;
						RTU_ADU_writeSingleRegisterExceptionResponse(slave_device_id, e_code);
					}
					break;
				}

				case WRITE_MULTIPLE_COILS:
				{	
					uint16_t request_starting_address = ((uint16_t)ADU[2] << 8) | ADU[3];
					uint16_t request_quantity_of_outputs = ((uint16_t)ADU[4] << 8) | ADU[5];

					uint8_t request_byte_count = ADU[6];
					uint8_t request_output_value[request_byte_count];
					for(uint8_t i = 0; i < request_byte_count; i++)
					{
						request_output_value[i] = ADU[7 + i];
					}

					uint16_t response_starting_address;
					uint16_t response_quantity_of_outputst;

					if( (request_quantity_of_outputs >= 0x0001) && (request_quantity_of_outputs <= 0x07B0) && (request_byte_count == (request_quantity_of_outputs/8 + ((request_quantity_of_outputs % 8)? 1:0))) )
					{
						if( request_starting_address +  request_quantity_of_outputs < SLAVE_MAX_DISCRETE_OUTPUT_COIL)
						{
							writeMultipleCoilsRequestHandling(request_starting_address, request_quantity_of_outputs, request_byte_count, request_output_value, &response_starting_address, &response_quantity_of_outputst);					

							RTU_ADU_writeMultipleCoilsResponse(slave_device_id, response_starting_address, response_quantity_of_outputst);
						}
						else
						{
							e_code = ILLEGAL_DATA_ADDRESS;
							RTU_ADU_writeMultipleCoilsExceptionResponse(slave_device_id, e_code);
						}
					}
					else
					{
						e_code = ILLEGAL_DATA_VALUE;
						RTU_ADU_writeMultipleCoilsExceptionResponse(slave_device_id, e_code);
					}
					break;
				}

				case WRITE_MULTIPLE_REGISTERS:
				{
					uint16_t request_starting_address = ((uint16_t)ADU[2] << 8) | ADU[3];
					uint16_t request_quantity_of_registers = ((uint16_t)ADU[4] << 8) | ADU[5];

					uint8_t request_byte_count = ADU[6];
					uint8_t quantity_of_registers = request_byte_count/2;
					register_t request_registers_value[quantity_of_registers];
					for(uint8_t i = 0; i < quantity_of_registers; i++)
					{
						request_registers_value[i] = (register_t)(((uint16_t)ADU[7 + 2*i] << 8) | (ADU[7 + 2*i + 1]));
					}

					uint16_t response_starting_address;
					uint16_t response_quantity_of_registerst;

					if( (request_quantity_of_registers >= 0x0001) && (request_quantity_of_registers <= 0x007B) && (request_byte_count == request_quantity_of_registers * 2) )
					{
						if( request_starting_address +  request_quantity_of_registers < SLAVE_MAX_ANALOG_OUTPUT_HOLDING_REGISTER)
						{
							writeMultipleRegistersRequestHandling(request_starting_address, request_quantity_of_registers, request_byte_count/* =N* x 2Byte*/, request_registers_value, &response_starting_address, &response_quantity_of_registerst);

							RTU_ADU_writeMultipleRegistersResponse(slave_device_id, response_starting_address, response_quantity_of_registerst);
						}
						else
						{
							e_code = ILLEGAL_DATA_ADDRESS;
							RTU_ADU_readHoldingRegistersExceptionResponse(slave_device_id, e_code);
						}
					}
					else
					{
						e_code = ILLEGAL_DATA_VALUE;
						RTU_ADU_writeMultipleRegistersExceptionResponse(slave_device_id, e_code);
					}
					break;
				}

				default:
				{
					e_code = ILLEGAL_FUNCTION;
					RTU_ADU_writeMultipleRegistersExceptionResponse(slave_device_id, f_code);
				}
			}
		}
		else
		{

		}
	}
	else
	{

	}
}


#endif // __MODBUS_SLAVE_RTU__