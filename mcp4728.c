#include <stdio.h>
#include <stdlib.h>
#include "mcp4728.h"
#include "i2c_interface.h"

int output_da(int ch, float voltage)
{
	int ret=0,i;
	unsigned char dev_addr = MCP4728_ADDR;
	mcp4728_config_data mcp4728;
	unsigned char buf[3];

	if(ch < CH_A || ch > CH_D)
	{
		printf("CHの範囲を超えています\n");
		return -1;
	}

	if(voltage < DAC_MIN_VOLT)
	{
		ret = -2;
		voltage = DAC_MIN_VOLT;
		//printf("DACの出力範囲を超えています\n");
	}

	if(voltage > DAC_MAX_VOLT)
	{
		ret = -3;
		voltage = DAC_MAX_VOLT;
		//printf("DACの出力範囲を超えています\n");
	}

	mcp4728.config.command = 0x0b;			//single mode
	mcp4728.config.DAC=ch;
	mcp4728.config.UDAC=EN_LATCH;
	mcp4728.config.VREF = VREF_INTERNAL;
	mcp4728.config.PD = PD_NORMAL;
	mcp4728.config.Gx = GAIN_X2;

	mcp4728.config.DAC_DATA = (int)(voltage * DAC_MAX_DATA / DAC_MAX_VOLT);

	for(i=0;i<3;i++)
		buf[i] = mcp4728.byte[3-1-i];


//	printf("%x %x \n",reg_addr, mcp4728.i2c_data );
	i2c_write(dev_addr, buf, sizeof(buf)); 

	return ret;

}

int output_da_fast(float voltage[])
{
	int ret=0,i;
	unsigned char dev_addr = MCP4728_ADDR;
	unsigned char reg_addr;
	fastmode_data data;
/*
	for(i=0;i<MAX_CH; i++)
	{
		data.ch[i].config.command=0;
		data.ch[i].config.PD=0;

		if(voltage[i] < DAC_MIN_VOLT)
		{
			ret = -2;
			voltage[i] = DAC_MIN_VOLT;
			//printf("DACの出力範囲を超えています\n");
		}

		if(voltage[i] > DAC_MAX_VOLT)
		{
			ret = -3;
			voltage[i] = DAC_MAX_VOLT;
			//printf("DACの出力範囲を超えています\n");
		}

		data.ch[i].config.DAC_DAT = (int)(voltage[i]* DAC_MAX_DATA / DAC_MAX_VOLT);
	}
*/

	data.ch[CH_A].config.command=0;
	data.ch[CH_A].config.PD=0;
	data.ch[CH_A].config.DAC_DAT = 0xfff;


	data.ch[CH_B].config.command=0;
	data.ch[CH_B].config.PD=0;
	data.ch[CH_B].config.DAC_DAT = 0x7ff;

	printf("%lx\t",data);
	for(i=0;i<8;i++)
		printf("%x ",data.byte[i]);

	printf("\n");


	return ret;
}

int main(int argc, char *argv[])
{
	float voltage[4];
	int ch;
	char *endptr;

//	ch = strtol(argv[1], &endptr,10);
//	voltage =strtof(argv[2],&endptr);

	voltage[CH_A] = 5.0;
	voltage[CH_B] = 4.0;
	voltage[CH_C] = 3.0;
	voltage[CH_D] = 2.0;

//	output_da_fast(voltage);
	output_da(1,0);
	return 0;
}
