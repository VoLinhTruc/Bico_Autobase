#ifndef __ARDUINO_MASTER_RTU_SERIAL__
#define __ARDUINO_MASTER_RTU_SERIAL__

#include "Arduino.h"
#include "Modbus_Master.h"
#include "Modbus_Master_RTU.h"

#define ARDUINO_MASTER_RTU_SERIAL_MAX_RESPONSE_ADU_BUFFER_SIZE 100

class Arduino_Master_RTU_Serial
{
	public:
		Arduino_Master_RTU_Serial();


		void begin(long baud);
		void begin(long baud, uint8_t config);
		int available();


		void RTUSerialReadCoilsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_coils);
		void RTUSerialReadDiscreteInputsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_inputs);
		void RTUSerialReadHoldingRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers);
		void RTUSerialReadInputRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_input_registers);

		void RTUSerialWriteSingleCoilRequest(uint8_t slave_id, uint16_t output_address, uint16_t output_value);
		void RTUSerialWriteSingleRegisterRequest(uint8_t slave_id, uint16_t register_address, register_t register_value);

		void RTUSerialWriteMultipleCoilsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_outputs, uint8_t byte_count, uint8_t* output_value);
		void RTUSerialWriteMultipleRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers, uint8_t byte_count/* =N* x 2Byte*/, register_t* registers_value);


		uint16_t RTUSerialGetResposeSlaveID();
		uint16_t RTUSerialGetCRC();
		void RTUSerialGetPDU(uint8_t* PDU_buffer, uint8_t* PDU_length);



		Function_Code RTUSerialGetFunctionCode();
		Exception_Code RTUSerialGetExceptionCode();


		uint8_t RTUSerialGetReadCoilByteCount();
		void RTUSerialGetReadCoilStatus(uint8_t* coil_status_buffer);

		uint8_t RTUSerialGetReadDiscreteInputByteCount();
		void RTUSerialGetReadDiscreteInputStatus(uint8_t* discrete_input_status_buffer);

		uint8_t RTUSerialGetReadHoldingRegistersByteCount();
		void RTUSerialGetReadHoldingRegistersValue(register_t* holding_register_value_buffer);
		uint8_t RTUSerialGetReadHoldingRegistersNumberOfRegister();

		uint8_t RTUSerialGetReadInputRegistersByteCount();
		void RTUSerialGetReadInputRegistersValue(register_t* input_register_value_buffer);
		uint8_t RTUSerialGetReadInputRegistersNumberOfRegister();


		uint16_t RTUSerialGetResponseWriteSingleCoilOutputAddress();
		uint16_t RTUSerialGetWriteSingleCoilOutputValue();

		uint16_t RTUSerialGetWriteSingleRegisterOutputAddress();
		uint16_t RTUSerialGetWriteSingleRegisterOutputValue();

		uint16_t RTUSerialGetWriteMultipleCoilsStartingAddress();
		uint16_t RTUSerialGetWriteMultipleCoilsStartingQuantityOfOutputs();

		uint16_t RTUSerialGetWriteMultipleRegistersStartingAddress();
		uint16_t RTUSerialGetWriteMultipleRegistersStartingQuantityOfRegisters();


	private:
		uint8_t response_ADU_buffer[ARDUINO_MASTER_RTU_SERIAL_MAX_RESPONSE_ADU_BUFFER_SIZE];
		uint8_t response_ADU_buffer_length = 0;
		uint16_t _baud_period_x15;
};








Arduino_Master_RTU_Serial::Arduino_Master_RTU_Serial()
{

}



void Arduino_Master_RTU_Serial::begin(long baud)
{
	Serial.begin(baud);
	_baud_period_x15 = 1000000*15/baud;
}

void Arduino_Master_RTU_Serial::begin(long baud, uint8_t config)
{
	Serial.begin(baud, config);
	_baud_period_x15 = 1000000*15/baud;	
}

int Arduino_Master_RTU_Serial::available()
{
	if(Serial.available())
	{
		response_ADU_buffer_length = 0;
		while(Serial.available())
		{
			response_ADU_buffer[response_ADU_buffer_length++] = Serial.read();
			delayMicroseconds(_baud_period_x15);
		}

		return 1;
	}
	else
	{
		return 0;
	}
}





void Arduino_Master_RTU_Serial::RTUSerialReadCoilsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_coils)
{
	RTU_ADU_readCoilsRequest(slave_id, starting_address, quantity_of_coils);
	for(uint8_t i = 0; i < request_RTU_ADU_length; i++)
	{
		Serial.write(built_request_RTU_ADU[i]);
	}
}

void Arduino_Master_RTU_Serial::RTUSerialReadDiscreteInputsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_inputs)
{
	RTU_ADU_readDiscreteInputsRequest(slave_id, starting_address, quantity_of_inputs);
	for(uint8_t i = 0; i < request_RTU_ADU_length; i++)
	{
		Serial.write(built_request_RTU_ADU[i]);
	}
}


void Arduino_Master_RTU_Serial::RTUSerialReadHoldingRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers)
{
	RTU_ADU_readHoldingRegistersRequest(slave_id, starting_address, quantity_of_registers);
	for(uint8_t i = 0; i < request_RTU_ADU_length; i++)
	{
		Serial.write(built_request_RTU_ADU[i]);
	}
}

void Arduino_Master_RTU_Serial::RTUSerialReadInputRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_input_registers)
{
	RTU_ADU_readInputRegistersRequest(slave_id, starting_address, quantity_of_input_registers);
	for(uint8_t i = 0; i < request_RTU_ADU_length; i++)
	{
		Serial.write(built_request_RTU_ADU[i]);
	}
}


void Arduino_Master_RTU_Serial::RTUSerialWriteSingleCoilRequest(uint8_t slave_id, uint16_t output_address, uint16_t output_value)
{
	RTU_ADU_writeSingleCoilRequest(slave_id, output_address, output_value);
	for(uint8_t i = 0; i < request_RTU_ADU_length; i++)
	{
		Serial.write(built_request_RTU_ADU[i]);
	}
}

void Arduino_Master_RTU_Serial::RTUSerialWriteSingleRegisterRequest(uint8_t slave_id, uint16_t register_address, register_t register_value)
{
	RTU_ADU_writeSingleRegisterRequest(slave_id, register_address, register_value);
	for(uint8_t i = 0; i < request_RTU_ADU_length; i++)
	{
		Serial.write(built_request_RTU_ADU[i]);
	}
}


void Arduino_Master_RTU_Serial::RTUSerialWriteMultipleCoilsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_outputs, uint8_t byte_count, uint8_t* output_value)
{
	RTU_ADU_writeMultipleCoilsRequest(slave_id, starting_address, quantity_of_outputs, byte_count, output_value);
	for(uint8_t i = 0; i < request_RTU_ADU_length; i++)
	{
		Serial.write(built_request_RTU_ADU[i]);
	}
}

void Arduino_Master_RTU_Serial::RTUSerialWriteMultipleRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers, uint8_t byte_count/* =N* x 2Byte*/, register_t* registers_value)
{
	RTU_ADU_writeMultipleRegistersRequest(slave_id, starting_address, quantity_of_registers, byte_count, registers_value);
	for(uint8_t i = 0; i < request_RTU_ADU_length; i++)
	{
		Serial.write(built_request_RTU_ADU[i]);
	}
}





uint16_t Arduino_Master_RTU_Serial::RTUSerialGetResposeSlaveID()
{
	return RTU_ADU_getResposeSlaveID(response_ADU_buffer);
}

uint16_t Arduino_Master_RTU_Serial::RTUSerialGetCRC()
{
	return RTU_ADU_getCRC(response_ADU_buffer, response_ADU_buffer_length);
}

void Arduino_Master_RTU_Serial::RTUSerialGetPDU(uint8_t* PDU_buffer, uint8_t* PDU_length)
{
	RTU_ADU_getPDU(response_ADU_buffer, response_ADU_buffer_length, PDU_buffer, PDU_length);
}





Function_Code Arduino_Master_RTU_Serial::RTUSerialGetFunctionCode()
{
	return RTU_ADU_getFunctionCode(response_ADU_buffer);
}

Exception_Code Arduino_Master_RTU_Serial::RTUSerialGetExceptionCode()
{
	return RTU_ADU_getExceptionCode(response_ADU_buffer);
}


uint8_t Arduino_Master_RTU_Serial::RTUSerialGetReadCoilByteCount()
{
	return RTU_ADU_getReadCoilByteCount(response_ADU_buffer);
}

void Arduino_Master_RTU_Serial::RTUSerialGetReadCoilStatus(uint8_t* coil_status_buffer)
{
	RTU_ADU_getReadCoilStatus(response_ADU_buffer, response_ADU_buffer_length, coil_status_buffer);
}


uint8_t Arduino_Master_RTU_Serial::RTUSerialGetReadDiscreteInputByteCount()
{
	return RTU_ADU_getReadDiscreteInputByteCount(response_ADU_buffer);
}

void Arduino_Master_RTU_Serial::RTUSerialGetReadDiscreteInputStatus(uint8_t* discrete_input_status_buffer)
{
	RTU_ADU_getReadDiscreteInputStatus(response_ADU_buffer, response_ADU_buffer_length, discrete_input_status_buffer);
}


uint8_t Arduino_Master_RTU_Serial::RTUSerialGetReadHoldingRegistersByteCount()
{
	return RTU_ADU_getReadHoldingRegistersByteCount(response_ADU_buffer);
}

void Arduino_Master_RTU_Serial::RTUSerialGetReadHoldingRegistersValue(register_t* holding_register_value_buffer)
{
	RTU_ADU_getReadHoldingRegistersValue(response_ADU_buffer, response_ADU_buffer_length, holding_register_value_buffer);
}

uint8_t Arduino_Master_RTU_Serial::RTUSerialGetReadHoldingRegistersNumberOfRegister()
{
	return RTU_ADU_getReadHoldingRegistersNumberOfRegister(response_ADU_buffer);
}


uint8_t Arduino_Master_RTU_Serial::RTUSerialGetReadInputRegistersByteCount()
{
	return RTU_ADU_getReadInputRegistersByteCount(response_ADU_buffer);
}

void Arduino_Master_RTU_Serial::RTUSerialGetReadInputRegistersValue(register_t* input_register_value_buffer)
{
	RTU_ADU_getReadInputRegistersValue(response_ADU_buffer, response_ADU_buffer_length, input_register_value_buffer);
}

uint8_t Arduino_Master_RTU_Serial::RTUSerialGetReadInputRegistersNumberOfRegister()
{
	return RTU_ADU_getReadInputRegistersNumberOfRegister(response_ADU_buffer);
}



uint16_t Arduino_Master_RTU_Serial::RTUSerialGetResponseWriteSingleCoilOutputAddress()
{
	return RTU_ADU_getResponseWriteSingleCoilOutputAddress(response_ADU_buffer);
}

uint16_t Arduino_Master_RTU_Serial::RTUSerialGetWriteSingleCoilOutputValue()
{
	return RTU_ADU_getWriteSingleCoilOutputValue(response_ADU_buffer);
}


uint16_t Arduino_Master_RTU_Serial::RTUSerialGetWriteSingleRegisterOutputAddress()
{
	return RTU_ADU_getWriteSingleRegisterOutputAddress(response_ADU_buffer);
}

uint16_t Arduino_Master_RTU_Serial::RTUSerialGetWriteSingleRegisterOutputValue()
{
	return RTU_ADU_getWriteSingleRegisterOutputValue(response_ADU_buffer);
}


uint16_t Arduino_Master_RTU_Serial::RTUSerialGetWriteMultipleCoilsStartingAddress()
{
	return RTU_ADU_getWriteMultipleCoilsStartingAddress(response_ADU_buffer);
}

uint16_t Arduino_Master_RTU_Serial::RTUSerialGetWriteMultipleCoilsStartingQuantityOfOutputs()
{
	return RTU_ADU_getWriteMultipleCoilsStartingQuantityOfOutputs(response_ADU_buffer);
}


uint16_t Arduino_Master_RTU_Serial::RTUSerialGetWriteMultipleRegistersStartingAddress()
{
	return RTU_ADU_getWriteMultipleRegistersStartingAddress(response_ADU_buffer);
}

uint16_t Arduino_Master_RTU_Serial::RTUSerialGetWriteMultipleRegistersStartingQuantityOfRegisters()
{
	return RTU_ADU_getWriteMultipleRegistersStartingQuantityOfRegisters(response_ADU_buffer);
}




#endif