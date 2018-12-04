#ifndef __ARDUINO_MASTER_IP_SERIAL__
#define __ARDUINO_MASTER_IP_SERIAL__

#include "Arduino.h"
#include "Modbus_Master.h"
#include "Modbus_Master_IP.h"

#define ARDUINO_MASTER_IP_SERIAL_MAX_RESPONSE_ADU_BUFFER_SIZE 100

class Arduino_Master_IP_Serial
{
	public:
		Arduino_Master_IP_Serial();


		void begin(long baud);
		void begin(long baud, uint8_t config);
		int available();


		void IPSerialReadCoilsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_coils);
		void IPSerialReadDiscreteInputsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_inputs);
		void IPSerialReadHoldingRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers);
		void IPSerialReadInputRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_input_registers);

		void IPSerialWriteSingleCoilRequest(uint8_t slave_id, uint16_t output_address, uint16_t output_value);
		void IPSerialWriteSingleRegisterRequest(uint8_t slave_id, uint16_t register_address, register_t register_value);

		void IPSerialWriteMultipleCoilsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_outputs, uint8_t byte_count, uint8_t* output_value);
		void IPSerialWriteMultipleRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers, uint8_t byte_count/* =N* x 2Byte*/, register_t* registers_value);


		uint16_t IPSerialGetTransactionID();
		uint16_t IPSerialGetResposeSlaveID();
		void IPSerialGetPDU(uint8_t* PDU_buffer, uint8_t* PDU_length);



		Function_Code IPSerialGetFunctionCode();
		Exception_Code IPSerialGetExceptionCode();


		uint8_t IPSerialGetReadCoilByteCount();
		void IPSerialGetReadCoilStatus(uint8_t* coil_status_buffer);

		uint8_t IPSerialGetReadDiscreteInputByteCount();
		void IPSerialGetReadDiscreteInputStatus(uint8_t* discrete_input_status_buffer);

		uint8_t IPSerialGetReadHoldingRegistersByteCount();
		void IPSerialGetReadHoldingRegistersValue(register_t* holding_register_value_buffer);
		uint8_t IPSerialGetReadHoldingRegistersNumberOfRegister();

		uint8_t IPSerialGetReadInputRegistersByteCount();
		void IPSerialGetReadInputRegistersValue(register_t* input_register_value_buffer);
		uint8_t IPSerialGetReadInputRegistersNumberOfRegister();


		uint16_t IPSerialGetResponseWriteSingleCoilOutputAddress();
		uint16_t IPSerialGetWriteSingleCoilOutputValue();

		uint16_t IPSerialGetWriteSingleRegisterOutputAddress();
		uint16_t IPSerialGetWriteSingleRegisterOutputValue();

		uint16_t IPSerialGetWriteMultipleCoilsStartingAddress();
		uint16_t IPSerialGetWriteMultipleCoilsStartingQuantityOfOutputs();

		uint16_t IPSerialGetWriteMultipleRegistersStartingAddress();
		uint16_t IPSerialGetWriteMultipleRegistersStartingQuantityOfRegisters();


	private:
		uint8_t response_ADU_buffer[ARDUINO_MASTER_IP_SERIAL_MAX_RESPONSE_ADU_BUFFER_SIZE];
		uint8_t response_ADU_buffer_length = 0;
		uint16_t _baud_period_x15;
};








Arduino_Master_IP_Serial::Arduino_Master_IP_Serial()
{

}



void Arduino_Master_IP_Serial::begin(long baud)
{
	Serial.begin(baud);
	_baud_period_x15 = 1000000*15/baud;
}

void Arduino_Master_IP_Serial::begin(long baud, uint8_t config)
{
	Serial.begin(baud, config);
	_baud_period_x15 = 1000000*15/baud;	
}

int Arduino_Master_IP_Serial::available()
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





void Arduino_Master_IP_Serial::IPSerialReadCoilsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_coils)
{
	IP_ADU_readCoilsRequest(slave_id, starting_address, quantity_of_coils);
	for(uint8_t i = 0; i < request_IP_ADU_length; i++)
	{
		Serial.write(built_request_IP_ADU[i]);
	}
}

void Arduino_Master_IP_Serial::IPSerialReadDiscreteInputsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_inputs)
{
	IP_ADU_readDiscreteInputsRequest(slave_id, starting_address, quantity_of_inputs);
	for(uint8_t i = 0; i < request_IP_ADU_length; i++)
	{
		Serial.write(built_request_IP_ADU[i]);
	}
}


void Arduino_Master_IP_Serial::IPSerialReadHoldingRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers)
{
	IP_ADU_readHoldingRegistersRequest(slave_id, starting_address, quantity_of_registers);
	for(uint8_t i = 0; i < request_IP_ADU_length; i++)
	{
		Serial.write(built_request_IP_ADU[i]);
	}
}

void Arduino_Master_IP_Serial::IPSerialReadInputRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_input_registers)
{
	IP_ADU_readInputRegistersRequest(slave_id, starting_address, quantity_of_input_registers);
	for(uint8_t i = 0; i < request_IP_ADU_length; i++)
	{
		Serial.write(built_request_IP_ADU[i]);
	}
}


void Arduino_Master_IP_Serial::IPSerialWriteSingleCoilRequest(uint8_t slave_id, uint16_t output_address, uint16_t output_value)
{
	IP_ADU_writeSingleCoilRequest(slave_id, output_address, output_value);
	for(uint8_t i = 0; i < request_IP_ADU_length; i++)
	{
		Serial.write(built_request_IP_ADU[i]);
	}
}

void Arduino_Master_IP_Serial::IPSerialWriteSingleRegisterRequest(uint8_t slave_id, uint16_t register_address, register_t register_value)
{
	IP_ADU_writeSingleRegisterRequest(slave_id, register_address, register_value);
	for(uint8_t i = 0; i < request_IP_ADU_length; i++)
	{
		Serial.write(built_request_IP_ADU[i]);
	}
}


void Arduino_Master_IP_Serial::IPSerialWriteMultipleCoilsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_outputs, uint8_t byte_count, uint8_t* output_value)
{
	IP_ADU_writeMultipleCoilsRequest(slave_id, starting_address, quantity_of_outputs, byte_count, output_value);
	for(uint8_t i = 0; i < request_IP_ADU_length; i++)
	{
		Serial.write(built_request_IP_ADU[i]);
	}
}

void Arduino_Master_IP_Serial::IPSerialWriteMultipleRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers, uint8_t byte_count/* =N* x 2Byte*/, register_t* registers_value)
{
	IP_ADU_writeMultipleRegistersRequest(slave_id, starting_address, quantity_of_registers, byte_count, registers_value);
	for(uint8_t i = 0; i < request_IP_ADU_length; i++)
	{
		Serial.write(built_request_IP_ADU[i]);
	}
}





uint16_t Arduino_Master_IP_Serial::IPSerialGetTransactionID()
{
	return IP_ADU_getTransactionID(response_ADU_buffer);
}

uint16_t Arduino_Master_IP_Serial::IPSerialGetResposeSlaveID()
{
	return IP_ADU_getResposeSlaveID(response_ADU_buffer);
}

void Arduino_Master_IP_Serial::IPSerialGetPDU(uint8_t* PDU_buffer, uint8_t* PDU_length)
{
	IP_ADU_getPDU(response_ADU_buffer, response_ADU_buffer_length, PDU_buffer, PDU_length);
}




Function_Code Arduino_Master_IP_Serial::IPSerialGetFunctionCode()
{
	return IP_ADU_getFunctionCode(response_ADU_buffer);
}

Exception_Code Arduino_Master_IP_Serial::IPSerialGetExceptionCode()
{
	return IP_ADU_getExceptionCode(response_ADU_buffer);
}


uint8_t Arduino_Master_IP_Serial::IPSerialGetReadCoilByteCount()
{
	return IP_ADU_getReadCoilByteCount(response_ADU_buffer);
}

void Arduino_Master_IP_Serial::IPSerialGetReadCoilStatus(uint8_t* coil_status_buffer)
{
	IP_ADU_getReadCoilStatus(response_ADU_buffer, response_ADU_buffer_length, coil_status_buffer);
}


uint8_t Arduino_Master_IP_Serial::IPSerialGetReadDiscreteInputByteCount()
{
	return IP_ADU_getReadDiscreteInputByteCount(response_ADU_buffer);
}

void Arduino_Master_IP_Serial::IPSerialGetReadDiscreteInputStatus(uint8_t* discrete_input_status_buffer)
{
	IP_ADU_getReadDiscreteInputStatus(response_ADU_buffer, response_ADU_buffer_length, discrete_input_status_buffer);
}


uint8_t Arduino_Master_IP_Serial::IPSerialGetReadHoldingRegistersByteCount()
{
	return IP_ADU_getReadHoldingRegistersByteCount(response_ADU_buffer);
}

void Arduino_Master_IP_Serial::IPSerialGetReadHoldingRegistersValue(register_t* holding_register_value_buffer)
{
	IP_ADU_getReadHoldingRegistersValue(response_ADU_buffer, response_ADU_buffer_length, holding_register_value_buffer);
}

uint8_t Arduino_Master_IP_Serial::IPSerialGetReadHoldingRegistersNumberOfRegister()
{
	return IP_ADU_getReadHoldingRegistersNumberOfRegister(response_ADU_buffer);
}


uint8_t Arduino_Master_IP_Serial::IPSerialGetReadInputRegistersByteCount()
{
	return IP_ADU_getReadInputRegistersByteCount(response_ADU_buffer);
}

void Arduino_Master_IP_Serial::IPSerialGetReadInputRegistersValue(register_t* input_register_value_buffer)
{
	IP_ADU_getReadInputRegistersValue(response_ADU_buffer, response_ADU_buffer_length, input_register_value_buffer);
}

uint8_t Arduino_Master_IP_Serial::IPSerialGetReadInputRegistersNumberOfRegister()
{
	return IP_ADU_getReadInputRegistersNumberOfRegister(response_ADU_buffer);
}



uint16_t Arduino_Master_IP_Serial::IPSerialGetResponseWriteSingleCoilOutputAddress()
{
	return IP_ADU_getResponseWriteSingleCoilOutputAddress(response_ADU_buffer);
}

uint16_t Arduino_Master_IP_Serial::IPSerialGetWriteSingleCoilOutputValue()
{
	return IP_ADU_getWriteSingleCoilOutputValue(response_ADU_buffer);
}


uint16_t Arduino_Master_IP_Serial::IPSerialGetWriteSingleRegisterOutputAddress()
{
	return IP_ADU_getWriteSingleRegisterOutputAddress(response_ADU_buffer);
}

uint16_t Arduino_Master_IP_Serial::IPSerialGetWriteSingleRegisterOutputValue()
{
	return IP_ADU_getWriteSingleRegisterOutputValue(response_ADU_buffer);
}


uint16_t Arduino_Master_IP_Serial::IPSerialGetWriteMultipleCoilsStartingAddress()
{
	return IP_ADU_getWriteMultipleCoilsStartingAddress(response_ADU_buffer);
}

uint16_t Arduino_Master_IP_Serial::IPSerialGetWriteMultipleCoilsStartingQuantityOfOutputs()
{
	return IP_ADU_getWriteMultipleCoilsStartingQuantityOfOutputs(response_ADU_buffer);
}


uint16_t Arduino_Master_IP_Serial::IPSerialGetWriteMultipleRegistersStartingAddress()
{
	return IP_ADU_getWriteMultipleRegistersStartingAddress(response_ADU_buffer);
}

uint16_t Arduino_Master_IP_Serial::IPSerialGetWriteMultipleRegistersStartingQuantityOfRegisters()
{
	return IP_ADU_getWriteMultipleRegistersStartingQuantityOfRegisters(response_ADU_buffer);
}




#endif