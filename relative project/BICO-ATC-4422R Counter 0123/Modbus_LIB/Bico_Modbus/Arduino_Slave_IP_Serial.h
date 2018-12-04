#ifndef __ARDUINO_SLAVE_IP_SERIAL__ 
#define __ARDUINO_SLAVE_IP_SERIAL__

#include "Arduino.h"
#include "Modbus_Definition.h"
#include "Modbus_Slave.h"
#include "Modbus_Slave_Handling.h"
#include "Modbus_Slave_IP.h"

#define MAX_INCOMING_MESSAGE_BUFFER_SIZE 100

class Arduino_Slave_IP_Serial
{
	public:
		Arduino_Slave_IP_Serial();
		void begin(long baud);
		void begin(long baud, uint8_t config);
		void fullHanlde();

	private:
		uint16_t _baud_period_x15;
};



Arduino_Slave_IP_Serial::Arduino_Slave_IP_Serial()
{

}

void Arduino_Slave_IP_Serial::begin(long baud)
{
	Serial.begin(baud);
	_baud_period_x15 = 1000000*15/baud;
}

void Arduino_Slave_IP_Serial::begin(long baud, uint8_t config)
{
	Serial.begin(baud, config);
	_baud_period_x15 = 1000000*15/baud;	
}

void Arduino_Slave_IP_Serial::fullHanlde()
{
	if(Serial.available() > 0)
	{
		// declare buffer and buffer-length ---------------
		uint8_t incomming_message[MAX_INCOMING_MESSAGE_BUFFER_SIZE];
		uint16_t len = 0;
		// declare buffer and buffer-length ---------------

		// get data from _stream to buffer -----------------
		while(Serial.available() > 0)
		{
		  incomming_message[len++] = Serial.read();
		  delayMicroseconds(_baud_period_x15);
		}
		// get data from Serial to buffer -----------------

		// handling buffer ------------------------
		IP_ADU_incomingHandling(incomming_message, len);  // in this step, response message is building automatically
		// handling buffer ------------------------

		// response message sending ------------------------------------
		for(uint8_t i = 0; i < response_IP_ADU_length; i++)
		{
		  Serial.write(built_response_IP_ADU[i]);
		}
		// response message sending ------------------------------------

		// clear data in buffer -----------------------------
		while(Serial.available() > 0)
		{
		  Serial.read();
		}
		// clear data in buffer -----------------------------
	}
}

#endif