#ifndef __ARDUINO_MASTER_RTU_SOFT_SERIAL__
#define __ARDUINO_MASTER_RTU_SOFT_SERIAL__

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "Modbus_Master.h"
#include "Modbus_Master_RTU.h"

#define ARDUINO_MASTER_RTU_SOFT_SERIAL_MAX_RESPONSE_ADU_BUFFER_SIZE 100

class Arduino_Master_RTU_Soft_Serial : SoftwareSerial
{
	public:
		Arduino_Master_RTU_Soft_Serial(uint8_t rx, uint8_t tx) : SoftwareSerial(rx, tx)
		{

		}


		void begin(long baud);
		int available();


		void RTUSoftSerialReadCoilsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_coils);
		void RTUSoftSerialReadDiscreteInputsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_inputs);
		void RTUSoftSerialReadHoldingRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers);
		void RTUSoftSerialReadInputRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_input_registers);

		void RTUSoftSerialWriteSingleCoilRequest(uint8_t slave_id, uint16_t output_address, uint16_t output_value);
		void RTUSoftSerialWriteSingleRegisterRequest(uint8_t slave_id, uint16_t register_address, register_t register_value);

		void RTUSoftSerialWriteMultipleCoilsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_outputs, uint8_t byte_count, uint8_t* output_value);
		void RTUSoftSerialWriteMultipleRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers, uint8_t byte_count/* =N* x 2Byte*/, register_t* registers_value);


		uint16_t RTUSoftSerialGetResposeSlaveID();
		uint16_t RTUSoftSerialGetCRC();
		void RTUSoftSerialGetPDU(uint8_t* PDU_buffer, uint8_t* PDU_length);



		Function_Code RTUSoftSerialGetFunctionCode();
		Exception_Code RTUSoftSerialGetExceptionCode();


		uint8_t RTUSoftSerialGetReadCoilByteCount();
		void RTUSoftSerialGetReadCoilStatus(uint8_t* coil_status_buffer);

		uint8_t RTUSoftSerialGetReadDiscreteInputByteCount();
		void RTUSoftSerialGetReadDiscreteInputStatus(uint8_t* discrete_input_status_buffer);

		uint8_t RTUSoftSerialGetReadHoldingRegistersByteCount();
		void RTUSoftSerialGetReadHoldingRegistersValue(register_t* holding_register_value_buffer);
		uint8_t RTUSoftSerialGetReadHoldingRegistersNumberOfRegister();

		uint8_t RTUSoftSerialGetReadInputRegistersByteCount();
		void RTUSoftSerialGetReadInputRegistersValue(register_t* input_register_value_buffer);
		uint8_t RTUSoftSerialGetReadInputRegistersNumberOfRegister();


		uint16_t RTUSoftSerialGetResponseWriteSingleCoilOutputAddress();
		uint16_t RTUSoftSerialGetWriteSingleCoilOutputValue();

		uint16_t RTUSoftSerialGetWriteSingleRegisterOutputAddress();
		uint16_t RTUSoftSerialGetWriteSingleRegisterOutputValue();

		uint16_t RTUSoftSerialGetWriteMultipleCoilsStartingAddress();
		uint16_t RTUSoftSerialGetWriteMultipleCoilsStartingQuantityOfOutputs();

		uint16_t RTUSoftSerialGetWriteMultipleRegistersStartingAddress();
		uint16_t RTUSoftSerialGetWriteMultipleRegistersStartingQuantityOfRegisters();


	private:
		uint8_t response_ADU_buffer[ARDUINO_MASTER_RTU_SOFT_SERIAL_MAX_RESPONSE_ADU_BUFFER_SIZE];
		uint8_t response_ADU_buffer_length = 0;
		uint16_t _baud_period_x15;
};








void Arduino_Master_RTU_Soft_Serial::begin(long baud)
{
	SoftwareSerial::begin(baud);
	_baud_period_x15 = 1000000*15/baud;
}

int Arduino_Master_RTU_Soft_Serial::available()
{
	if(SoftwareSerial::available())
	{
		response_ADU_buffer_length = 0;
		while(SoftwareSerial::available())
		{
			response_ADU_buffer[response_ADU_buffer_length++] = SoftwareSerial::read();
			delayMicroseconds(_baud_period_x15);
		}

		return 1;
	}
	else
	{
		return 0;
	}
}





void Arduino_Master_RTU_Soft_Serial::RTUSoftSerialReadCoilsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_coils)
{
	RTU_ADU_readCoilsRequest(slave_id, starting_address, quantity_of_coils);
	for(uint8_t i = 0; i < request_RTU_ADU_length; i++)
	{
		SoftwareSerial::write(built_request_RTU_ADU[i]);
	}
}

void Arduino_Master_RTU_Soft_Serial::RTUSoftSerialReadDiscreteInputsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_inputs)
{
	RTU_ADU_readDiscreteInputsRequest(slave_id, starting_address, quantity_of_inputs);
	for(uint8_t i = 0; i < request_RTU_ADU_length; i++)
	{
		SoftwareSerial::write(built_request_RTU_ADU[i]);
	}
}


void Arduino_Master_RTU_Soft_Serial::RTUSoftSerialReadHoldingRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers)
{
	RTU_ADU_readHoldingRegistersRequest(slave_id, starting_address, quantity_of_registers);
	for(uint8_t i = 0; i < request_RTU_ADU_length; i++)
	{
		SoftwareSerial::write(built_request_RTU_ADU[i]);
	}
}

void Arduino_Master_RTU_Soft_Serial::RTUSoftSerialReadInputRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_input_registers)
{
	RTU_ADU_readInputRegistersRequest(slave_id, starting_address, quantity_of_input_registers);
	for(uint8_t i = 0; i < request_RTU_ADU_length; i++)
	{
		SoftwareSerial::write(built_request_RTU_ADU[i]);
	}
}


void Arduino_Master_RTU_Soft_Serial::RTUSoftSerialWriteSingleCoilRequest(uint8_t slave_id, uint16_t output_address, uint16_t output_value)
{
	RTU_ADU_writeSingleCoilRequest(slave_id, output_address, output_value);
	for(uint8_t i = 0; i < request_RTU_ADU_length; i++)
	{
		SoftwareSerial::write(built_request_RTU_ADU[i]);
	}
}

void Arduino_Master_RTU_Soft_Serial::RTUSoftSerialWriteSingleRegisterRequest(uint8_t slave_id, uint16_t register_address, register_t register_value)
{
	RTU_ADU_writeSingleRegisterRequest(slave_id, register_address, register_value);
	for(uint8_t i = 0; i < request_RTU_ADU_length; i++)
	{
		SoftwareSerial::write(built_request_RTU_ADU[i]);
	}
}


void Arduino_Master_RTU_Soft_Serial::RTUSoftSerialWriteMultipleCoilsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_outputs, uint8_t byte_count, uint8_t* output_value)
{
	RTU_ADU_writeMultipleCoilsRequest(slave_id, starting_address, quantity_of_outputs, byte_count, output_value);
	for(uint8_t i = 0; i < request_RTU_ADU_length; i++)
	{
		SoftwareSerial::write(built_request_RTU_ADU[i]);
	}
}

void Arduino_Master_RTU_Soft_Serial::RTUSoftSerialWriteMultipleRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers, uint8_t byte_count/* =N* x 2Byte*/, register_t* registers_value)
{
	RTU_ADU_writeMultipleRegistersRequest(slave_id, starting_address, quantity_of_registers, byte_count, registers_value);
	for(uint8_t i = 0; i < request_RTU_ADU_length; i++)
	{
		SoftwareSerial::write(built_request_RTU_ADU[i]);
	}
}





uint16_t Arduino_Master_RTU_Soft_Serial::RTUSoftSerialGetResposeSlaveID()
{
	return RTU_ADU_getResposeSlaveID(response_ADU_buffer);
}

uint16_t Arduino_Master_RTU_Soft_Serial::RTUSoftSerialGetCRC()
{
	return RTU_ADU_getCRC(response_ADU_buffer, response_ADU_buffer_length);
}

void Arduino_Master_RTU_Soft_Serial::RTUSoftSerialGetPDU(uint8_t* PDU_buffer, uint8_t* PDU_length)
{
	RTU_ADU_getPDU(response_ADU_buffer, response_ADU_buffer_length, PDU_buffer, PDU_length);
}





Function_Code Arduino_Master_RTU_Soft_Serial::RTUSoftSerialGetFunctionCode()
{
	return RTU_ADU_getFunctionCode(response_ADU_buffer);
}

Exception_Code Arduino_Master_RTU_Soft_Serial::RTUSoftSerialGetExceptionCode()
{
	return RTU_ADU_getExceptionCode(response_ADU_buffer);
}


uint8_t Arduino_Master_RTU_Soft_Serial::RTUSoftSerialGetReadCoilByteCount()
{
	return RTU_ADU_getReadCoilByteCount(response_ADU_buffer);
}

void Arduino_Master_RTU_Soft_Serial::RTUSoftSerialGetReadCoilStatus(uint8_t* coil_status_buffer)
{
	RTU_ADU_getReadCoilStatus(response_ADU_buffer, response_ADU_buffer_length, coil_status_buffer);
}


uint8_t Arduino_Master_RTU_Soft_Serial::RTUSoftSerialGetReadDiscreteInputByteCount()
{
	return RTU_ADU_getReadDiscreteInputByteCount(response_ADU_buffer);
}

void Arduino_Master_RTU_Soft_Serial::RTUSoftSerialGetReadDiscreteInputStatus(uint8_t* discrete_input_status_buffer)
{
	RTU_ADU_getReadDiscreteInputStatus(response_ADU_buffer, response_ADU_buffer_length, discrete_input_status_buffer);
}


uint8_t Arduino_Master_RTU_Soft_Serial::RTUSoftSerialGetReadHoldingRegistersByteCount()
{
	return RTU_ADU_getReadHoldingRegistersByteCount(response_ADU_buffer);
}

void Arduino_Master_RTU_Soft_Serial::RTUSoftSerialGetReadHoldingRegistersValue(register_t* holding_register_value_buffer)
{
	RTU_ADU_getReadHoldingRegistersValue(response_ADU_buffer, response_ADU_buffer_length, holding_register_value_buffer);
}

uint8_t Arduino_Master_RTU_Soft_Serial::RTUSoftSerialGetReadHoldingRegistersNumberOfRegister()
{
	return RTU_ADU_getReadHoldingRegistersNumberOfRegister(response_ADU_buffer);
}


uint8_t Arduino_Master_RTU_Soft_Serial::RTUSoftSerialGetReadInputRegistersByteCount()
{
	return RTU_ADU_getReadInputRegistersByteCount(response_ADU_buffer);
}

void Arduino_Master_RTU_Soft_Serial::RTUSoftSerialGetReadInputRegistersValue(register_t* input_register_value_buffer)
{
	RTU_ADU_getReadInputRegistersValue(response_ADU_buffer, response_ADU_buffer_length, input_register_value_buffer);
}

uint8_t Arduino_Master_RTU_Soft_Serial::RTUSoftSerialGetReadInputRegistersNumberOfRegister()
{
	return RTU_ADU_getReadInputRegistersNumberOfRegister(response_ADU_buffer);
}



uint16_t Arduino_Master_RTU_Soft_Serial::RTUSoftSerialGetResponseWriteSingleCoilOutputAddress()
{
	return RTU_ADU_getResponseWriteSingleCoilOutputAddress(response_ADU_buffer);
}

uint16_t Arduino_Master_RTU_Soft_Serial::RTUSoftSerialGetWriteSingleCoilOutputValue()
{
	return RTU_ADU_getWriteSingleCoilOutputValue(response_ADU_buffer);
}


uint16_t Arduino_Master_RTU_Soft_Serial::RTUSoftSerialGetWriteSingleRegisterOutputAddress()
{
	return RTU_ADU_getWriteSingleRegisterOutputAddress(response_ADU_buffer);
}

uint16_t Arduino_Master_RTU_Soft_Serial::RTUSoftSerialGetWriteSingleRegisterOutputValue()
{
	return RTU_ADU_getWriteSingleRegisterOutputValue(response_ADU_buffer);
}


uint16_t Arduino_Master_RTU_Soft_Serial::RTUSoftSerialGetWriteMultipleCoilsStartingAddress()
{
	return RTU_ADU_getWriteMultipleCoilsStartingAddress(response_ADU_buffer);
}

uint16_t Arduino_Master_RTU_Soft_Serial::RTUSoftSerialGetWriteMultipleCoilsStartingQuantityOfOutputs()
{
	return RTU_ADU_getWriteMultipleCoilsStartingQuantityOfOutputs(response_ADU_buffer);
}


uint16_t Arduino_Master_RTU_Soft_Serial::RTUSoftSerialGetWriteMultipleRegistersStartingAddress()
{
	return RTU_ADU_getWriteMultipleRegistersStartingAddress(response_ADU_buffer);
}

uint16_t Arduino_Master_RTU_Soft_Serial::RTUSoftSerialGetWriteMultipleRegistersStartingQuantityOfRegisters()
{
	return RTU_ADU_getWriteMultipleRegistersStartingQuantityOfRegisters(response_ADU_buffer);
}




#endif