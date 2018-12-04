#ifndef __ESP8266_MASTER_RTU_UDP__
#define __ESP8266_MASTER_RTU_UDP__

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "Modbus_Master.h"
#include "Modbus_Master_RTU.h"

#define ESP8266_MASTER_RTU_UDP_MAX_RESPONSE_ADU_BUFFER_SIZE 100

class ESP8266_Master_RTU_UDP : WiFiUDP
{
	public:
		ESP8266_Master_RTU_UDP() : WiFiUDP()
		{

		}


		uint8_t begin(uint16_t udp_local_port);
		int parsePacket();
		void flush()
		{
			WiFiUDP::flush();
		}
		IPAddress remoteIP()
		{
			return WiFiUDP::remoteIP();
		}
		uint16_t remotePort()
		{
			return WiFiUDP::remotePort();
		}
		int available()
		{
			return WiFiUDP::available();
		}


		void RTUUDPReadCoilsRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_coils);
		void RTUUDPReadDiscreteInputsRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_inputs);
		void RTUUDPReadHoldingRegistersRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers);
		void RTUUDPReadInputRegistersRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_input_registers);

		void RTUUDPWriteSingleCoilRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t output_address, uint16_t output_value);
		void RTUUDPWriteSingleRegisterRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t register_address, register_t register_value);

		void RTUUDPWriteMultipleCoilsRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_outputs, uint8_t byte_count, uint8_t* output_value);
		void RTUUDPWriteMultipleRegistersRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers, uint8_t byte_count/* =N* x 2Byte*/, register_t* registers_value);


		uint16_t RTUUDPGetResposeSlaveID();
		void RTUUDPGetPDU(uint8_t* PDU_buffer, uint8_t* PDU_length);



		Function_Code RTUUDPGetFunctionCode();
		uint16_t RTUUDPGetCRC();
		Exception_Code RTUUDPGetExceptionCode();


		uint8_t RTUUDPGetReadCoilByteCount();
		void RTUUDPGetReadCoilStatus(uint8_t* coil_status_buffer);

		uint8_t RTUUDPGetReadDiscreteInputByteCount();
		void RTUUDPGetReadDiscreteInputStatus(uint8_t* discrete_input_status_buffer);

		uint8_t RTUUDPGetReadHoldingRegistersByteCount();
		void RTUUDPGetReadHoldingRegistersValue(register_t* holding_register_value_buffer);
		uint8_t RTUUDPGetReadHoldingRegistersNumberOfRegister();

		uint8_t RTUUDPGetReadInputRegistersByteCount();
		void RTUUDPGetReadInputRegistersValue(register_t* input_register_value_buffer);
		uint8_t RTUUDPGetReadInputRegistersNumberOfRegister();


		uint16_t RTUUDPGetResponseWriteSingleCoilOutputAddress();
		uint16_t RTUUDPGetWriteSingleCoilOutputValue();

		uint16_t RTUUDPGetWriteSingleRegisterOutputAddress();
		uint16_t RTUUDPGetWriteSingleRegisterOutputValue();

		uint16_t RTUUDPGetWriteMultipleCoilsStartingAddress();
		uint16_t RTUUDPGetWriteMultipleCoilsStartingQuantityOfOutputs();

		uint16_t RTUUDPGetWriteMultipleRegistersStartingAddress();
		uint16_t RTUUDPGetWriteMultipleRegistersStartingQuantityOfRegisters();


	//private:
		uint8_t response_ADU_buffer[ESP8266_MASTER_RTU_UDP_MAX_RESPONSE_ADU_BUFFER_SIZE];
		uint8_t response_ADU_buffer_length = 0;
};









uint8_t ESP8266_Master_RTU_UDP::begin(uint16_t udp_local_port)
{
	return WiFiUDP::begin(udp_local_port);
}

int ESP8266_Master_RTU_UDP::parsePacket()
{
	response_ADU_buffer_length = WiFiUDP::parsePacket();
	if(response_ADU_buffer_length)
	{
		WiFiUDP::read(response_ADU_buffer, response_ADU_buffer_length);
	}
	
	return response_ADU_buffer_length;
}





void ESP8266_Master_RTU_UDP::RTUUDPReadCoilsRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_coils)
{
	RTU_ADU_readCoilsRequest(slave_id, starting_address, quantity_of_coils);

	WiFiUDP::beginPacket(ip, port);
	for(uint8_t i = 0; i < request_RTU_ADU_length; i++)
	{
		WiFiUDP::write(built_request_RTU_ADU[i]);
	}
	WiFiUDP::endPacket();
}

void ESP8266_Master_RTU_UDP::RTUUDPReadDiscreteInputsRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_inputs)
{
	RTU_ADU_readDiscreteInputsRequest(slave_id, starting_address, quantity_of_inputs);

	WiFiUDP::beginPacket(ip, port);
	for(uint8_t i = 0; i < request_RTU_ADU_length; i++)
	{
		WiFiUDP::write(built_request_RTU_ADU[i]);
	}
	WiFiUDP::endPacket();
}


void ESP8266_Master_RTU_UDP::RTUUDPReadHoldingRegistersRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers)
{
	RTU_ADU_readHoldingRegistersRequest(slave_id, starting_address, quantity_of_registers);

	WiFiUDP::beginPacket(ip, port);
	for(uint8_t i = 0; i < request_RTU_ADU_length; i++)
	{
		WiFiUDP::write(built_request_RTU_ADU[i]);
	}
	WiFiUDP::endPacket();
}

void ESP8266_Master_RTU_UDP::RTUUDPReadInputRegistersRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_input_registers)
{
	RTU_ADU_readInputRegistersRequest(slave_id, starting_address, quantity_of_input_registers);

	WiFiUDP::beginPacket(ip, port);
	for(uint8_t i = 0; i < request_RTU_ADU_length; i++)
	{
		WiFiUDP::write(built_request_RTU_ADU[i]);
	}
	WiFiUDP::endPacket();
}


void ESP8266_Master_RTU_UDP::RTUUDPWriteSingleCoilRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t output_address, uint16_t output_value)
{
	RTU_ADU_writeSingleCoilRequest(slave_id, output_address, output_value);

	WiFiUDP::beginPacket(ip, port);
	for(uint8_t i = 0; i < request_RTU_ADU_length; i++)
	{
		WiFiUDP::write(built_request_RTU_ADU[i]);
	}
	WiFiUDP::endPacket();
}

void ESP8266_Master_RTU_UDP::RTUUDPWriteSingleRegisterRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t register_address, register_t register_value)
{
	RTU_ADU_writeSingleRegisterRequest(slave_id, register_address, register_value);

	WiFiUDP::beginPacket(ip, port);
	for(uint8_t i = 0; i < request_RTU_ADU_length; i++)
	{
		WiFiUDP::write(built_request_RTU_ADU[i]);
	}
	WiFiUDP::endPacket();
}


void ESP8266_Master_RTU_UDP::RTUUDPWriteMultipleCoilsRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_outputs, uint8_t byte_count, uint8_t* output_value)
{
	RTU_ADU_writeMultipleCoilsRequest(slave_id, starting_address, quantity_of_outputs, byte_count, output_value);

	WiFiUDP::beginPacket(ip, port);
	for(uint8_t i = 0; i < request_RTU_ADU_length; i++)
	{
		WiFiUDP::write(built_request_RTU_ADU[i]);
	}
	WiFiUDP::endPacket();
}

void ESP8266_Master_RTU_UDP::RTUUDPWriteMultipleRegistersRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers, uint8_t byte_count/* =N* x 2Byte*/, register_t* registers_value)
{
	RTU_ADU_writeMultipleRegistersRequest(slave_id, starting_address, quantity_of_registers, byte_count, registers_value);

	WiFiUDP::beginPacket(ip, port);
	for(uint8_t i = 0; i < request_RTU_ADU_length; i++)
	{
		WiFiUDP::write(built_request_RTU_ADU[i]);
	}
	WiFiUDP::endPacket();
}






uint16_t ESP8266_Master_RTU_UDP::RTUUDPGetResposeSlaveID()
{
	return RTU_ADU_getResposeSlaveID(response_ADU_buffer);
}

uint16_t ESP8266_Master_RTU_UDP::RTUUDPGetCRC()
{
	return RTU_ADU_getCRC(response_ADU_buffer, response_ADU_buffer_length);
}

void ESP8266_Master_RTU_UDP::RTUUDPGetPDU(uint8_t* PDU_buffer, uint8_t* PDU_length)
{
	RTU_ADU_getPDU(response_ADU_buffer, response_ADU_buffer_length, PDU_buffer, PDU_length);
}




Function_Code ESP8266_Master_RTU_UDP::RTUUDPGetFunctionCode()
{
	return RTU_ADU_getFunctionCode(response_ADU_buffer);
}

Exception_Code ESP8266_Master_RTU_UDP::RTUUDPGetExceptionCode()
{
	return RTU_ADU_getExceptionCode(response_ADU_buffer);
}


uint8_t ESP8266_Master_RTU_UDP::RTUUDPGetReadCoilByteCount()
{
	return RTU_ADU_getReadCoilByteCount(response_ADU_buffer);
}

void ESP8266_Master_RTU_UDP::RTUUDPGetReadCoilStatus(uint8_t* coil_status_buffer)
{
	RTU_ADU_getReadCoilStatus(response_ADU_buffer, response_ADU_buffer_length, coil_status_buffer);
}


uint8_t ESP8266_Master_RTU_UDP::RTUUDPGetReadDiscreteInputByteCount()
{
	return RTU_ADU_getReadDiscreteInputByteCount(response_ADU_buffer);
}

void ESP8266_Master_RTU_UDP::RTUUDPGetReadDiscreteInputStatus(uint8_t* discrete_input_status_buffer)
{
	RTU_ADU_getReadDiscreteInputStatus(response_ADU_buffer, response_ADU_buffer_length, discrete_input_status_buffer);
}


uint8_t ESP8266_Master_RTU_UDP::RTUUDPGetReadHoldingRegistersByteCount()
{
	return RTU_ADU_getReadHoldingRegistersByteCount(response_ADU_buffer);
}

void ESP8266_Master_RTU_UDP::RTUUDPGetReadHoldingRegistersValue(register_t* holding_register_value_buffer)
{
	RTU_ADU_getReadHoldingRegistersValue(response_ADU_buffer, response_ADU_buffer_length, holding_register_value_buffer);
}

uint8_t ESP8266_Master_RTU_UDP::RTUUDPGetReadHoldingRegistersNumberOfRegister()
{
	return RTU_ADU_getReadHoldingRegistersNumberOfRegister(response_ADU_buffer);
}


uint8_t ESP8266_Master_RTU_UDP::RTUUDPGetReadInputRegistersByteCount()
{
	return RTU_ADU_getReadInputRegistersByteCount(response_ADU_buffer);
}

void ESP8266_Master_RTU_UDP::RTUUDPGetReadInputRegistersValue(register_t* input_register_value_buffer)
{
	RTU_ADU_getReadInputRegistersValue(response_ADU_buffer, response_ADU_buffer_length, input_register_value_buffer);
}

uint8_t ESP8266_Master_RTU_UDP::RTUUDPGetReadInputRegistersNumberOfRegister()
{
	return RTU_ADU_getReadInputRegistersNumberOfRegister(response_ADU_buffer);
}



uint16_t ESP8266_Master_RTU_UDP::RTUUDPGetResponseWriteSingleCoilOutputAddress()
{
	return RTU_ADU_getResponseWriteSingleCoilOutputAddress(response_ADU_buffer);
}

uint16_t ESP8266_Master_RTU_UDP::RTUUDPGetWriteSingleCoilOutputValue()
{
	return RTU_ADU_getWriteSingleCoilOutputValue(response_ADU_buffer);
}


uint16_t ESP8266_Master_RTU_UDP::RTUUDPGetWriteSingleRegisterOutputAddress()
{
	return RTU_ADU_getWriteSingleRegisterOutputAddress(response_ADU_buffer);
}

uint16_t ESP8266_Master_RTU_UDP::RTUUDPGetWriteSingleRegisterOutputValue()
{
	return RTU_ADU_getWriteSingleRegisterOutputValue(response_ADU_buffer);
}


uint16_t ESP8266_Master_RTU_UDP::RTUUDPGetWriteMultipleCoilsStartingAddress()
{
	return RTU_ADU_getWriteMultipleCoilsStartingAddress(response_ADU_buffer);
}

uint16_t ESP8266_Master_RTU_UDP::RTUUDPGetWriteMultipleCoilsStartingQuantityOfOutputs()
{
	return RTU_ADU_getWriteMultipleCoilsStartingQuantityOfOutputs(response_ADU_buffer);
}


uint16_t ESP8266_Master_RTU_UDP::RTUUDPGetWriteMultipleRegistersStartingAddress()
{
	return RTU_ADU_getWriteMultipleRegistersStartingAddress(response_ADU_buffer);
}

uint16_t ESP8266_Master_RTU_UDP::RTUUDPGetWriteMultipleRegistersStartingQuantityOfRegisters()
{
	return RTU_ADU_getWriteMultipleRegistersStartingQuantityOfRegisters(response_ADU_buffer);
}




#endif //__ESP8266_MASTER_RTU_UDP__