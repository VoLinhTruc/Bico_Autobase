#ifndef __ARDUINO_SLAVE_RTU_SOFT_SERIAL__ 
#define __ARDUINO_SLAVE_RTU_SOFT_SERIAL__

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "Modbus_Definition.h"
#include "Modbus_Slave.h"
#include "Modbus_Slave_Handling.h"
#include "Modbus_Slave_RTU.h"

#define MAX_INCOMING_MESSAGE_BUFFER_SIZE 100

class Arduino_Slave_RTU_Soft_Serial : SoftwareSerial
{
	public:
		Arduino_Slave_RTU_Soft_Serial(uint8_t rx, uint8_t tx) : SoftwareSerial(rx, tx)
		{
			
		}
		
		void begin(long baud);
		void fullHanlde();

	private:
		uint16_t _baud_period_x15;
};


void Arduino_Slave_RTU_Soft_Serial::begin(long baud)
{
	SoftwareSerial::begin(baud);
	_baud_period_x15 = 1000000*15/baud;
}

void Arduino_Slave_RTU_Soft_Serial::fullHanlde()
{
	if(SoftwareSerial::available() > 0)
	{
		// declare buffer and buffer-length ---------------
		uint8_t incomming_message[MAX_INCOMING_MESSAGE_BUFFER_SIZE];
		uint16_t len = 0;
		// declare buffer and buffer-length ---------------

		// get data from _stream to buffer -----------------
		while(SoftwareSerial::available() > 0)
		{
		  incomming_message[len++] = SoftwareSerial::read();
		  delayMicroseconds(_baud_period_x15);
		}
		// get data from Serial to buffer -----------------

		// handling buffer ------------------------
		RTU_ADU_incomingRequest(incomming_message, len);  // in this step, response message is building automatically
		// handling buffer ------------------------

		// response message sending ------------------------------------
		for(uint8_t i = 0; i < response_RTU_ADU_length; i++)
		{
		  SoftwareSerial::write(built_response_RTU_ADU[i]);
		}
		// response message sending ------------------------------------

		// clear data in buffer -----------------------------
		while(SoftwareSerial::available() > 0)
		{
		  SoftwareSerial::read();
		}
		// clear data in buffer -----------------------------
	}
}

#endif