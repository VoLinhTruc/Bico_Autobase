#ifndef __ESP8266_MASTER_IP_UDP__
#define __ESP8266_MASTER_IP_UDP__

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "Modbus_Master.h"
#include "Modbus_Master_IP.h"

#define ESP8266_MASTER_IP_UDP_MAX_RESPONSE_ADU_BUFFER_SIZE 100

class ESP8266_Master_IP_UDP : WiFiUDP
{
	public:
		ESP8266_Master_IP_UDP() : WiFiUDP()
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


		void IPUDPReadCoilsRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_coils);
		void IPUDPReadDiscreteInputsRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_inputs);
		void IPUDPReadHoldingRegistersRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers);
		void IPUDPReadInputRegistersRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_input_registers);

		void IPUDPWriteSingleCoilRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t output_address, uint16_t output_value);
		void IPUDPWriteSingleRegisterRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t register_address, register_t register_value);

		void IPUDPWriteMultipleCoilsRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_outputs, uint8_t byte_count, uint8_t* output_value);
		void IPUDPWriteMultipleRegistersRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers, uint8_t byte_count/* =N* x 2Byte*/, register_t* registers_value);


		uint16_t IPUDPGetTransactionID();
		uint16_t IPUDPGetResposeSlaveID();
		void IPUDPGetPDU(uint8_t* PDU_buffer, uint8_t* PDU_length);



		Function_Code IPUDPGetFunctionCode();
		Exception_Code IPUDPGetExceptionCode();


		uint8_t IPUDPGetReadCoilByteCount();
		void IPUDPGetReadCoilStatus(uint8_t* coil_status_buffer);

		uint8_t IPUDPGetReadDiscreteInputByteCount();
		void IPUDPGetReadDiscreteInputStatus(uint8_t* discrete_input_status_buffer);

		uint8_t IPUDPGetReadHoldingRegistersByteCount();
		void IPUDPGetReadHoldingRegistersValue(register_t* holding_register_value_buffer);
		uint8_t IPUDPGetReadHoldingRegistersNumberOfRegister();

		uint8_t IPUDPGetReadInputRegistersByteCount();
		void IPUDPGetReadInputRegistersValue(register_t* input_register_value_buffer);
		uint8_t IPUDPGetReadInputRegistersNumberOfRegister();


		uint16_t IPUDPGetResponseWriteSingleCoilOutputAddress();
		uint16_t IPUDPGetWriteSingleCoilOutputValue();

		uint16_t IPUDPGetWriteSingleRegisterOutputAddress();
		uint16_t IPUDPGetWriteSingleRegisterOutputValue();

		uint16_t IPUDPGetWriteMultipleCoilsStartingAddress();
		uint16_t IPUDPGetWriteMultipleCoilsStartingQuantityOfOutputs();

		uint16_t IPUDPGetWriteMultipleRegistersStartingAddress();
		uint16_t IPUDPGetWriteMultipleRegistersStartingQuantityOfRegisters();


	//private:
		uint8_t response_ADU_buffer[ESP8266_MASTER_IP_UDP_MAX_RESPONSE_ADU_BUFFER_SIZE];
		uint8_t response_ADU_buffer_length = 0;
};









uint8_t ESP8266_Master_IP_UDP::begin(uint16_t udp_local_port)
{
	return WiFiUDP::begin(udp_local_port);
}

int ESP8266_Master_IP_UDP::parsePacket()
{
	response_ADU_buffer_length = WiFiUDP::parsePacket();
	if(response_ADU_buffer_length)
	{
		WiFiUDP::read(response_ADU_buffer, response_ADU_buffer_length);
	}
	
	return response_ADU_buffer_length;
}





void ESP8266_Master_IP_UDP::IPUDPReadCoilsRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_coils)
{
	IP_ADU_readCoilsRequest(slave_id, starting_address, quantity_of_coils);

	WiFiUDP::beginPacket(ip, port);
	for(uint8_t i = 0; i < request_IP_ADU_length; i++)
	{
		WiFiUDP::write(built_request_IP_ADU[i]);
	}
	WiFiUDP::endPacket();
}

void ESP8266_Master_IP_UDP::IPUDPReadDiscreteInputsRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_inputs)
{
	IP_ADU_readDiscreteInputsRequest(slave_id, starting_address, quantity_of_inputs);

	WiFiUDP::beginPacket(ip, port);
	for(uint8_t i = 0; i < request_IP_ADU_length; i++)
	{
		WiFiUDP::write(built_request_IP_ADU[i]);
	}
	WiFiUDP::endPacket();
}


void ESP8266_Master_IP_UDP::IPUDPReadHoldingRegistersRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers)
{
	IP_ADU_readHoldingRegistersRequest(slave_id, starting_address, quantity_of_registers);

	WiFiUDP::beginPacket(ip, port);
	for(uint8_t i = 0; i < request_IP_ADU_length; i++)
	{
		WiFiUDP::write(built_request_IP_ADU[i]);
	}
	WiFiUDP::endPacket();
}

void ESP8266_Master_IP_UDP::IPUDPReadInputRegistersRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_input_registers)
{
	IP_ADU_readInputRegistersRequest(slave_id, starting_address, quantity_of_input_registers);

	WiFiUDP::beginPacket(ip, port);
	for(uint8_t i = 0; i < request_IP_ADU_length; i++)
	{
		WiFiUDP::write(built_request_IP_ADU[i]);
	}
	WiFiUDP::endPacket();
}


void ESP8266_Master_IP_UDP::IPUDPWriteSingleCoilRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t output_address, uint16_t output_value)
{
	IP_ADU_writeSingleCoilRequest(slave_id, output_address, output_value);

	WiFiUDP::beginPacket(ip, port);
	for(uint8_t i = 0; i < request_IP_ADU_length; i++)
	{
		WiFiUDP::write(built_request_IP_ADU[i]);
	}
	WiFiUDP::endPacket();
}

void ESP8266_Master_IP_UDP::IPUDPWriteSingleRegisterRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t register_address, register_t register_value)
{
	IP_ADU_writeSingleRegisterRequest(slave_id, register_address, register_value);

	WiFiUDP::beginPacket(ip, port);
	for(uint8_t i = 0; i < request_IP_ADU_length; i++)
	{
		WiFiUDP::write(built_request_IP_ADU[i]);
	}
	WiFiUDP::endPacket();
}


void ESP8266_Master_IP_UDP::IPUDPWriteMultipleCoilsRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_outputs, uint8_t byte_count, uint8_t* output_value)
{
	IP_ADU_writeMultipleCoilsRequest(slave_id, starting_address, quantity_of_outputs, byte_count, output_value);

	WiFiUDP::beginPacket(ip, port);
	for(uint8_t i = 0; i < request_IP_ADU_length; i++)
	{
		WiFiUDP::write(built_request_IP_ADU[i]);
	}
	WiFiUDP::endPacket();
}

void ESP8266_Master_IP_UDP::IPUDPWriteMultipleRegistersRequest(IPAddress ip, uint16_t port, uint8_t slave_id, uint16_t starting_address, uint16_t quantity_of_registers, uint8_t byte_count/* =N* x 2Byte*/, register_t* registers_value)
{
	IP_ADU_writeMultipleRegistersRequest(slave_id, starting_address, quantity_of_registers, byte_count, registers_value);

	WiFiUDP::beginPacket(ip, port);
	for(uint8_t i = 0; i < request_IP_ADU_length; i++)
	{
		WiFiUDP::write(built_request_IP_ADU[i]);
	}
	WiFiUDP::endPacket();
}





uint16_t ESP8266_Master_IP_UDP::IPUDPGetTransactionID()
{
	return IP_ADU_getTransactionID(response_ADU_buffer);
}

uint16_t ESP8266_Master_IP_UDP::IPUDPGetResposeSlaveID()
{
	return IP_ADU_getResposeSlaveID(response_ADU_buffer);
}

void ESP8266_Master_IP_UDP::IPUDPGetPDU(uint8_t* PDU_buffer, uint8_t* PDU_length)
{
	IP_ADU_getPDU(response_ADU_buffer, response_ADU_buffer_length, PDU_buffer, PDU_length);
}




Function_Code ESP8266_Master_IP_UDP::IPUDPGetFunctionCode()
{
	return IP_ADU_getFunctionCode(response_ADU_buffer);
}

Exception_Code ESP8266_Master_IP_UDP::IPUDPGetExceptionCode()
{
	return IP_ADU_getExceptionCode(response_ADU_buffer);
}


uint8_t ESP8266_Master_IP_UDP::IPUDPGetReadCoilByteCount()
{
	return IP_ADU_getReadCoilByteCount(response_ADU_buffer);
}

void ESP8266_Master_IP_UDP::IPUDPGetReadCoilStatus(uint8_t* coil_status_buffer)
{
	IP_ADU_getReadCoilStatus(response_ADU_buffer, response_ADU_buffer_length, coil_status_buffer);
}


uint8_t ESP8266_Master_IP_UDP::IPUDPGetReadDiscreteInputByteCount()
{
	return IP_ADU_getReadDiscreteInputByteCount(response_ADU_buffer);
}

void ESP8266_Master_IP_UDP::IPUDPGetReadDiscreteInputStatus(uint8_t* discrete_input_status_buffer)
{
	IP_ADU_getReadDiscreteInputStatus(response_ADU_buffer, response_ADU_buffer_length, discrete_input_status_buffer);
}


uint8_t ESP8266_Master_IP_UDP::IPUDPGetReadHoldingRegistersByteCount()
{
	return IP_ADU_getReadHoldingRegistersByteCount(response_ADU_buffer);
}

void ESP8266_Master_IP_UDP::IPUDPGetReadHoldingRegistersValue(register_t* holding_register_value_buffer)
{
	IP_ADU_getReadHoldingRegistersValue(response_ADU_buffer, response_ADU_buffer_length, holding_register_value_buffer);
}

uint8_t ESP8266_Master_IP_UDP::IPUDPGetReadHoldingRegistersNumberOfRegister()
{
	return IP_ADU_getReadHoldingRegistersNumberOfRegister(response_ADU_buffer);
}


uint8_t ESP8266_Master_IP_UDP::IPUDPGetReadInputRegistersByteCount()
{
	return IP_ADU_getReadInputRegistersByteCount(response_ADU_buffer);
}

void ESP8266_Master_IP_UDP::IPUDPGetReadInputRegistersValue(register_t* input_register_value_buffer)
{
	IP_ADU_getReadInputRegistersValue(response_ADU_buffer, response_ADU_buffer_length, input_register_value_buffer);
}

uint8_t ESP8266_Master_IP_UDP::IPUDPGetReadInputRegistersNumberOfRegister()
{
	return IP_ADU_getReadInputRegistersNumberOfRegister(response_ADU_buffer);
}



uint16_t ESP8266_Master_IP_UDP::IPUDPGetResponseWriteSingleCoilOutputAddress()
{
	return IP_ADU_getResponseWriteSingleCoilOutputAddress(response_ADU_buffer);
}

uint16_t ESP8266_Master_IP_UDP::IPUDPGetWriteSingleCoilOutputValue()
{
	return IP_ADU_getWriteSingleCoilOutputValue(response_ADU_buffer);
}


uint16_t ESP8266_Master_IP_UDP::IPUDPGetWriteSingleRegisterOutputAddress()
{
	return IP_ADU_getWriteSingleRegisterOutputAddress(response_ADU_buffer);
}

uint16_t ESP8266_Master_IP_UDP::IPUDPGetWriteSingleRegisterOutputValue()
{
	return IP_ADU_getWriteSingleRegisterOutputValue(response_ADU_buffer);
}


uint16_t ESP8266_Master_IP_UDP::IPUDPGetWriteMultipleCoilsStartingAddress()
{
	return IP_ADU_getWriteMultipleCoilsStartingAddress(response_ADU_buffer);
}

uint16_t ESP8266_Master_IP_UDP::IPUDPGetWriteMultipleCoilsStartingQuantityOfOutputs()
{
	return IP_ADU_getWriteMultipleCoilsStartingQuantityOfOutputs(response_ADU_buffer);
}


uint16_t ESP8266_Master_IP_UDP::IPUDPGetWriteMultipleRegistersStartingAddress()
{
	return IP_ADU_getWriteMultipleRegistersStartingAddress(response_ADU_buffer);
}

uint16_t ESP8266_Master_IP_UDP::IPUDPGetWriteMultipleRegistersStartingQuantityOfRegisters()
{
	return IP_ADU_getWriteMultipleRegistersStartingQuantityOfRegisters(response_ADU_buffer);
}




#endif //__ESP8266_MASTER_IP_UDP__