#ifndef __ESP8266_SLAVE_IP_UDP__ 
#define __ESP8266_SLAVE_IP_UDP__

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "Modbus_Definition.h"
#include "Modbus_Slave.h"
#include "Modbus_Slave_Handling.h"
#include "Modbus_Slave_IP.h"

#define MAX_INCOMING_MESSAGE_BUFFER_SIZE 100

class ESP8266_Slave_IP_UDP : WiFiUDP
{
	public:
		ESP8266_Slave_IP_UDP() : WiFiUDP()
		{

		}

		uint8_t begin(uint16_t udp_local_port);

		void fullHanlde();

	private:
};




uint8_t ESP8266_Slave_IP_UDP::begin(uint16_t udp_local_port)
{
	return WiFiUDP::begin(udp_local_port);
}

void ESP8266_Slave_IP_UDP::fullHanlde()
{
  int incomming_packet_size = WiFiUDP::parsePacket();
  if(incomming_packet_size)
  {
    uint8_t incomming_message[incomming_packet_size];

    WiFiUDP::read(incomming_message, incomming_packet_size);

    IP_ADU_incomingHandling(incomming_message, incomming_packet_size);

    resend:
    WiFiUDP::beginPacket(WiFiUDP::remoteIP(), WiFiUDP::remotePort());
    for(uint8_t i = 0; i < response_IP_ADU_length; i++)
    {
      WiFiUDP::write(built_response_IP_ADU[i]);
    }
    
    /*	after ::endPacket() execute,
        
        _tx_buf_head = 0;
        _tx_buf_cur = 0;
        _tx_buf_offset = 0;
		
		see ..\ESP8266WiFi\src\include\UdpContext.h for more detail
    */
    uint8_t send_state = WiFiUDP::endPacket();
    Serial.println(send_state); 
    if(!send_state)
    {
    	goto resend;
    }
  }
}



#endif