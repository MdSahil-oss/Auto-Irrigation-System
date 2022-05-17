#include<reg51.h>
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
sbit DHT11=P2^3;

int I_RH,D_RH,I_Temp,D_Temp,CheckSum; 
char hum[2],temp[2];
char *c;
int i;




void timer_delay20ms()		/* Timer0 delay function */
{
	TMOD = 0x01;
	TH0 = 0xB8;		/* Load higher 8-bit in TH0 */
	TL0 = 0x0C;		/* Load lower 8-bit in TL0 */
	TR0 = 1;		/* Start timer0 */
	while(TF0 == 0);	/* Wait until timer0 flag set */
	TR0 = 0;		/* Stop timer0 */
	TF0 = 0;		/* Clear timer0 flag */
}

void timer_delay30us()		/* Timer0 delay function */
{
	TMOD = 0x01;		/* Timer0 mode1 (16-bit timer mode) */
	TH0 = 0xFF;		/* Load higher 8-bit in TH0 */
	TL0 = 0xF1;		/* Load lower 8-bit in TL0 */
	TR0 = 1;		/* Start timer0 */
	while(TF0 == 0);	/* Wait until timer0 flag set */
	TR0 = 0;		/* Stop timer0 */
	TF0 = 0;		/* Clear timer0 flag */
}

void Request()			/* Microcontroller send request */
{
	DHT11 = 0;		/* set to low pin */
	timer_delay20ms();	/* wait for 20ms */
	DHT11 = 1;		/* set to high pin */
}

void Response()			/* Receive response from DHT11 */
{
	while(DHT11==1);
	while(DHT11==0);
	while(DHT11==1);
}

int Receive_data()		/* Receive data */
{
	int q,c=0;	
	for (q=0; q<8; q++)
	{
		while(DHT11==0);/* check received bit 0 or 1 */
		timer_delay30us();
		if(DHT11 == 1)	/* If high pulse is greater than 30ms */
		c = (c<<1)|(0x01);/* Then its logic HIGH */
		else		/* otherwise its logic LOW */
		c = (c<<1);
		while(DHT11==1);
	}
	return c;
}
void show_DHT11(){
	
			int hum0,hum1;
			int temp0,temp1;
			string("Hum = ");
			hum0 = I_RH/10;
			hum1 = I_RH%10;
			hum[0]=hum0 + '0';
			hum[1]=hum1 + '0';
			string(hum);
			string(".");
			hum0 = D_RH/10;
			hum1 = D_RH%10;
			hum[0]=hum0 + '0';
			hum[1]=hum1 + '0';
			string(hum);
			string("%");
			cmd(0xc0);
			string("Temp = ");
			temp0 = I_Temp/10;
			temp1 = I_Temp%10;
			temp[0]=temp0+'0';
			temp[1]=temp1+'0';
			string(temp);
			string(".");
			temp0 = D_Temp/10;
			temp1 = D_Temp%10;
			temp[0]=temp0+'0';
			temp[1]=temp1+'0';
			string(temp);
			string(" ");
			display(0xDF);
			string("C");
			
	
		}
