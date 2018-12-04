#ifndef __ARDUINO_SLAVE_RTU_SOFT_SERIAL__ 
#define __ARDUINO_SLAVE_RTU_SOFT_SERIAL__

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "Modbus_Definition.h"
#include "Modbus_Slave.h"
#include "Modbus_Slave_Handling.h"
#include "Modbus_Slave_RTU.h"

#define MAX_INCOMING_MESSAGE_BUFFER_SIZE 100

class Arduino_Slave_RTU_Soft_Serial
{
	public:
		Arduino_Slave_RTU_Soft_Serial(SoftwareSerial* soft_serial);
		void begin(long baud);
		void fullHanlde();

	private:
		SoftwareSerial* _soft_serial;
		uint16_t _baud_period_x15;
};



Arduino_Slave_RTU_Soft_Serial::Arduino_Slave_RTU_Soft_Serial(SoftwareSerial* soft_serial)
{
	_soft_serial = soft_serial;
}

void Arduino_Slave_RTU_Soft_Serial::begin(long baud)
{
	_soft_serial->begin(baud);
	_baud_period_x15 = 1000000*15/baud;
}

void Arduino_Slave_RTU_Soft_Serial::fullHanlde()
{
	if(_soft_serial->available() > 0)
	{
		// declare buffer and buffer-length ---------------
		uint8_t incomming_message[MAX_INCOMING_MESSAGE_BUFFER_SIZE];
		uint16_t len = 0;
		// declare buffer and buffer-length ---------------

		// get data from _stream to buffer -----------------
		while(_soft_serial->available() > 0)
		{
		  incomming_message[len++] = _soft_serial->read();
		  delayMicroseconds(_baud_period_x15);
		}
		// get data from Serial to buffer -----------------

		// handling buffer ------------------------
		RTU_ADU_incomingRequest(incomming_message, len);  // in this step, response message is building automatically
		// handling buffer ------------------------

		// response message sending ------------------------------------
		for(uint8_t i = 0; i < response_RTU_ADU_length; i++)
		{
		  _soft_serial->write(built_response_RTU_ADU[i]);
		}
		// response message sending ------------------------------------

		// clear data in buffer -----------------------------
		while(_soft_serial->available() > 0)
		{
		  _soft_serial->read();
		}
		// clear data in buffer -----------------------------
	}
}

#endif