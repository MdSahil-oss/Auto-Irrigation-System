#include<reg51.h>

sbit SoilMoistureSensor=P2^4;
sbit pumpOut = P2^5;

int mois_val;
int mois_val_per;
int mois_val0;
int mois_val1;
char soil_I_MV[2];
char soil_D_MV[2];
extern int I;
int close = 3;



void recieve_soilMostureSensor(){
	cmd(0x01);
	
	mois_val=SoilMoistureSensor;
	mois_val_per=(mois_val*100)/1023;
	 I=mois_val_per;
	string("Soil Moisture : ");
	cmd(0xc0);
	string("    ");
	mois_val0=(I)/10;
	mois_val1=(I)%10;
	soil_I_MV[0]=mois_val0 + '0';
	soil_I_MV[1]=mois_val1 + '0';
	string(soil_I_MV);
	string(".");
	mois_val=mois_val_per*10;
	mois_val0=mois_val_per%10;
	mois_val=mois_val*10;
	mois_val1=mois_val%10;
	soil_I_MV[0]=mois_val0 + '0';
	soil_I_MV[1]=mois_val1 + '0';
	string(soil_I_MV);
	string("%");
	
	delay(200);
	cmd(0x01);
	
	if(mois_val_per < 10){
		string("   Pump is ON   ");
		pumpOut=1;
		close = 1;
	}
	else{
		string("  Pump is Off  ");
		pumpOut=0;
		close = 2;
	}
	if((close%2)==3 ){
		string("  Pump is Off  ");
	}
	
}