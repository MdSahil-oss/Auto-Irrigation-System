#include<reg51.h>
#define lcd P3

sbit rs=P2^0;
sbit e=P2^1;
sbit rw=P2^2;

void delay (int);
void cmd (char);
void display (char);
void custom (void);
void string (char *);
void init (void);

unsigned char custom_char[]= {0x00,0x04,0x0E,0x04,0x15,0x0E,0x04,0x00, 
	                      0x00,0x04,0x0E,0x0E,0x0E,0x1F,0x04,0x00, 
	                      0x00,0x0A,0x15,0x11,0x11,0x0A,0x04,0x00,
			      0x0E,0x11,0x11,0x1F,0x1B,0x1B,0x1B,0x1F,
	                      0x0E,0x11,0x10,0x1F,0x1B,0x1B,0x1B,0x1F,
			      0x00,0x0E,0x15,0x1B,0x0E,0x0E,0x00,0x00,
	                      };
	                          
 
void delay (int d)
{
	unsigned char i;
	for(;d>0;d--)
	{
		for(i=250;i>0;i--);
		for(i=248;i>0;i--);
	}
}
void cmd (char c)
{
	lcd=c;
	
	rs=0;
	rw=0;
	e=1;
	delay(5);
	e=0;
}
void display (char c)
{
	lcd=c;
	rs=1;
	rw=0;
	e=1;
	delay(5);
	e=0;
}
void custom (void)
{
	int k;
	cmd(0x40);
	for(k=0;k<48;k++)
	display(custom_char[k]);
	cmd(0x80);
}

void string (char *p)
{
	while(*p)
	{
		display(*p++);
	}
}
void init (void)
{
	cmd(0x38);
	cmd(0x0c);
	cmd(0x01);
	cmd(0x80);
}

