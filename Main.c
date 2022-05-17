#include<reg51.h>

#include "proLCD.h"
#include "soilMoistureSensor.h"
#include "DHT11.h"

void main()
{
		
	
	
	init();
	custom();
	string("STARTING");
	delay(100);
	string(".");
	delay(100);
	string(".");
	delay(100);
	string(".");
	delay(100);
	Request();	/* send start pulse */
	Response();	/* receive response */
	while(1)
	{
		I_RH=Receive_data();	/* store first eight bit in I_RH */
		D_RH=Receive_data();	/* store next eight bit in D_RH */
		I_Temp=Receive_data();	/* store next eight bit in I_Temp */
		D_Temp=Receive_data();	/* store next eight bit in D_Temp */
		CheckSum=Receive_data();/* store next eight bit in CheckSum */
		cmd(0x01);
		cmd(0x80);
		if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
		{
			string("     Error");
		}
		
		else
		{
			show_DHT11();
			
		}	
		delay(500);
		cmd(0x01);
		cmd(0x80);
		SoilMoistureSensor = 1;
		delay(150);
		recieve_soilMostureSensor();
		delay(500);

		}
}