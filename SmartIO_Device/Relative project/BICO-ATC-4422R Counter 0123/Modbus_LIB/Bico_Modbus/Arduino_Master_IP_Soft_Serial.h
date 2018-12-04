#ifndef __ARDUINO_MASTER_IP_SOFT_SERIAL__
#define __ARDUINO_MASTER_IP_SOFT_SERIAL__

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "Modbus_Master.h"
#include "Modbus_Master_IP.h"

#define ARDUINO_MASTER_IP_SOFT_SERIAL_MAX_RESPONSE_ADU_BUFFER_SIZE 100

class Arduino_Master_IP_Soft_Serial : SoftwareSerial
{
	public:
		Arduino_Master_IP_Soft_Serial(uint8_t rx, uint8_t tx) : SoftwareSerial(rx, tx)
		{
			
		}


		void begin(long baud);
		int available();


		void IPSoftSerialReadCoilsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_coils);
		void IPSoftSerialReadDiscreteInputsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_inputs);
		void IPSoftSerialReadHoldingRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers);
		void IPSoftSerialReadInputRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_input_registers);

		void IPSoftSerialWriteSingleCoilRequest(uint8_t slave_id, uint16_t output_address, uint16_t output_value);
		void IPSoftSerialWriteSingleRegisterRequest(uint8_t slave_id, uint16_t register_address, register_t register_value);

		void IPSoftSerialWriteMultipleCoilsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_outputs, uint8_t byte_count, uint8_t* output_value);
		void IPSoftSerialWriteMultipleRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers, uint8_t byte_count/* =N* x 2Byte*/, register_t* registers_value);




		uint16_t IPSoftSerialGetTransactionID();
		uint16_t IPSoftSerialGetResposeSlaveID();
		void IPSoftSerialGetPDU(uint8_t* PDU_buffer, uint8_t* PDU_length);



		Function_Code IPSoftSerialGetFunctionCode();
		Exception_Code IPSoftSerialGetExceptionCode();


		uint8_t IPSoftSerialGetReadCoilByteCount();
		void IPSoftSerialGetReadCoilStatus(uint8_t* coil_status_buffer);

		uint8_t IPSoftSerialGetReadDiscreteInputByteCount();
		void IPSoftSerialGetReadDiscreteInputStatus(uint8_t* discrete_input_status_buffer);

		uint8_t IPSoftSerialGetReadHoldingRegistersByteCount();
		void IPSoftSerialGetReadHoldingRegistersValue(register_t* holding_register_value_buffer);
		uint8_t IPSoftSerialGetReadHoldingRegistersNumberOfRegister();

		uint8_t IPSoftSerialGetReadInputRegistersByteCount();
		void IPSoftSerialGetReadInputRegistersValue(register_t* input_register_value_buffer);
		uint8_t IPSoftSerialGetReadInputRegistersNumberOfRegister();


		uint16_t IPSoftSerialGetResponseWriteSingleCoilOutputAddress();
		uint16_t IPSoftSerialGetWriteSingleCoilOutputValue();

		uint16_t IPSoftSerialGetWriteSingleRegisterOutputAddress();
		uint16_t IPSoftSerialGetWriteSingleRegisterOutputValue();

		uint16_t IPSoftSerialGetWriteMultipleCoilsStartingAddress();
		uint16_t IPSoftSerialGetWriteMultipleCoilsStartingQuantityOfOutputs();

		uint16_t IPSoftSerialGetWriteMultipleRegistersStartingAddress();
		uint16_t IPSoftSerialGetWriteMultipleRegistersStartingQuantityOfRegisters();


	private:
		uint8_t response_ADU_buffer[ARDUINO_MASTER_IP_SOFT_SERIAL_MAX_RESPONSE_ADU_BUFFER_SIZE];
		uint8_t response_ADU_buffer_length = 0;
		uint16_t _baud_period_x15;
};








void Arduino_Master_IP_Soft_Serial::begin(long baud)
{
	SoftwareSerial::begin(baud);
	_baud_period_x15 = 1000000*15/baud;
}

int Arduino_Master_IP_Soft_Serial::available()
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





void Arduino_Master_IP_Soft_Serial::IPSoftSerialReadCoilsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_coils)
{
	IP_ADU_readCoilsRequest(slave_id, starting_address, quantity_of_coils);
	for(uint8_t i = 0; i < request_IP_ADU_length; i++)
	{
		SoftwareSerial::write(built_request_IP_ADU[i]);
	}
}

void Arduino_Master_IP_Soft_Serial::IPSoftSerialReadDiscreteInputsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_inputs)
{
	IP_ADU_readDiscreteInputsRequest(slave_id, starting_address, quantity_of_inputs);
	for(uint8_t i = 0; i < request_IP_ADU_length; i++)
	{
		SoftwareSerial::write(built_request_IP_ADU[i]);
	}
}


void Arduino_Master_IP_Soft_Serial::IPSoftSerialReadHoldingRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers)
{
	IP_ADU_readHoldingRegistersRequest(slave_id, starting_address, quantity_of_registers);
	for(uint8_t i = 0; i < request_IP_ADU_length; i++)
	{
		SoftwareSerial::write(built_request_IP_ADU[i]);
	}
}

void Arduino_Master_IP_Soft_Serial::IPSoftSerialReadInputRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_input_registers)
{
	IP_ADU_readInputRegistersRequest(slave_id, starting_address, quantity_of_input_registers);
	for(uint8_t i = 0; i < request_IP_ADU_length; i++)
	{
		SoftwareSerial::write(built_request_IP_ADU[i]);
	}
}


void Arduino_Master_IP_Soft_Serial::IPSoftSerialWriteSingleCoilRequest(uint8_t slave_id, uint16_t output_address, uint16_t output_value)
{
	IP_ADU_writeSingleCoilRequest(slave_id, output_address, output_value);
	for(uint8_t i = 0; i < request_IP_ADU_length; i++)
	{
		SoftwareSerial::write(built_request_IP_ADU[i]);
	}
}

void Arduino_Master_IP_Soft_Serial::IPSoftSerialWriteSingleRegisterRequest(uint8_t slave_id, uint16_t register_address, register_t register_value)
{
	IP_ADU_writeSingleRegisterRequest(slave_id, register_address, register_value);
	for(uint8_t i = 0; i < request_IP_ADU_length; i++)
	{
		SoftwareSerial::write(built_request_IP_ADU[i]);
	}
}


void Arduino_Master_IP_Soft_Serial::IPSoftSerialWriteMultipleCoilsRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_outputs, uint8_t byte_count, uint8_t* output_value)
{
	IP_ADU_writeMultipleCoilsRequest(slave_id, starting_address, quantity_of_outputs, byte_count, output_value);
	for(uint8_t i = 0; i < request_IP_ADU_length; i++)
	{
		SoftwareSerial::write(built_request_IP_ADU[i]);
	}
}

void Arduino_Master_IP_Soft_Serial::IPSoftSerialWriteMultipleRegistersRequest(uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers, uint8_t byte_count/* =N* x 2Byte*/, register_t* registers_value)
{
	IP_ADU_writeMultipleRegistersRequest(slave_id, starting_address, quantity_of_registers, byte_count, registers_value);
	for(uint8_t i = 0; i < request_IP_ADU_length; i++)
	{
		SoftwareSerial::write(built_request_IP_ADU[i]);
	}
}





uint16_t Arduino_Master_IP_Soft_Serial::IPSoftSerialGetTransactionID()
{
	return IP_ADU_getTransactionID(response_ADU_buffer);
}

uint16_t Arduino_Master_IP_Soft_Serial::IPSoftSerialGetResposeSlaveID()
{
	return IP_ADU_getResposeSlaveID(response_ADU_buffer);
}

void Arduino_Master_IP_Soft_Serial::IPSoftSerialGetPDU(uint8_t* PDU_buffer, uint8_t* PDU_length)
{
	IP_ADU_getPDU(response_ADU_buffer, response_ADU_buffer_length, PDU_buffer, PDU_length);
}




Function_Code Arduino_Master_IP_Soft_Serial::IPSoftSerialGetFunctionCode()
{
	return IP_ADU_getFunctionCode(response_ADU_buffer);
}

Exception_Code Arduino_Master_IP_Soft_Serial::IPSoftSerialGetExceptionCode()
{
	return IP_ADU_getExceptionCode(response_ADU_buffer);
}


uint8_t Arduino_Master_IP_Soft_Serial::IPSoftSerialGetReadCoilByteCount()
{
	return IP_ADU_getReadCoilByteCount(response_ADU_buffer);
}

void Arduino_Master_IP_Soft_Serial::IPSoftSerialGetReadCoilStatus(uint8_t* coil_status_buffer)
{
	IP_ADU_getReadCoilStatus(response_ADU_buffer, response_ADU_buffer_length, coil_status_buffer);
}


uint8_t Arduino_Master_IP_Soft_Serial::IPSoftSerialGetReadDiscreteInputByteCount()
{
	return IP_ADU_getReadDiscreteInputByteCount(response_ADU_buffer);
}

void Arduino_Master_IP_Soft_Serial::IPSoftSerialGetReadDiscreteInputStatus(uint8_t* discrete_input_status_buffer)
{
	IP_ADU_getReadDiscreteInputStatus(response_ADU_buffer, response_ADU_buffer_length, discrete_input_status_buffer);
}


uint8_t Arduino_Master_IP_Soft_Serial::IPSoftSerialGetReadHoldingRegistersByteCount()
{
	return IP_ADU_getReadHoldingRegistersByteCount(response_ADU_buffer);
}

void Arduino_Master_IP_Soft_Serial::IPSoftSerialGetReadHoldingRegistersValue(register_t* holding_register_value_buffer)
{
	IP_ADU_getReadHoldingRegistersValue(response_ADU_buffer, response_ADU_buffer_length, holding_register_value_buffer);
}

uint8_t Arduino_Master_IP_Soft_Serial::IPSoftSerialGetReadHoldingRegistersNumberOfRegister()
{
	return IP_ADU_getReadHoldingRegistersNumberOfRegister(response_ADU_buffer);
}


uint8_t Arduino_Master_IP_Soft_Serial::IPSoftSerialGetReadInputRegistersByteCount()
{
	return IP_ADU_getReadInputRegistersByteCount(response_ADU_buffer);
}

void Arduino_Master_IP_Soft_Serial::IPSoftSerialGetReadInputRegistersValue(register_t* input_register_value_buffer)
{
	IP_ADU_getReadInputRegistersValue(response_ADU_buffer, response_ADU_buffer_length, input_register_value_buffer);
}

uint8_t Arduino_Master_IP_Soft_Serial::IPSoftSerialGetReadInputRegistersNumberOfRegister()
{
	return IP_ADU_getReadInputRegistersNumberOfRegister(response_ADU_buffer);
}



uint16_t Arduino_Master_IP_Soft_Serial::IPSoftSerialGetResponseWriteSingleCoilOutputAddress()
{
	return IP_ADU_getResponseWriteSingleCoilOutputAddress(response_ADU_buffer);
}

uint16_t Arduino_Master_IP_Soft_Serial::IPSoftSerialGetWriteSingleCoilOutputValue()
{
	return IP_ADU_getWriteSingleCoilOutputValue(response_ADU_buffer);
}


uint16_t Arduino_Master_IP_Soft_Serial::IPSoftSerialGetWriteSingleRegisterOutputAddress()
{
	return IP_ADU_getWriteSingleRegisterOutputAddress(response_ADU_buffer);
}

uint16_t Arduino_Master_IP_Soft_Serial::IPSoftSerialGetWriteSingleRegisterOutputValue()
{
	return IP_ADU_getWriteSingleRegisterOutputValue(response_ADU_buffer);
}


uint16_t Arduino_Master_IP_Soft_Serial::IPSoftSerialGetWriteMultipleCoilsStartingAddress()
{
	return IP_ADU_getWriteMultipleCoilsStartingAddress(response_ADU_buffer);
}

uint16_t Arduino_Master_IP_Soft_Serial::IPSoftSerialGetWriteMultipleCoilsStartingQuantityOfOutputs()
{
	return IP_ADU_getWriteMultipleCoilsStartingQuantityOfOutputs(response_ADU_buffer);
}


uint16_t Arduino_Master_IP_Soft_Serial::IPSoftSerialGetWriteMultipleRegistersStartingAddress()
{
	return IP_ADU_getWriteMultipleRegistersStartingAddress(response_ADU_buffer);
}

uint16_t Arduino_Master_IP_Soft_Serial::IPSoftSerialGetWriteMultipleRegistersStartingQuantityOfRegisters()
{
	return IP_ADU_getWriteMultipleRegistersStartingQuantityOfRegisters(response_ADU_buffer);
}




#endif