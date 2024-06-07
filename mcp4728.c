#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

	// エンディアン変換
	for(i=0;i<3;i++)
		buf[i] = mcp4728.byte[3-1-i];

	// ビッグエンディアンの場合は変換しない
	// memcpy(buf,mcp4728.byte, sizeof(mcp4728.byte));


	i2c_write(dev_addr, buf, sizeof(buf)); 

	return ret;

}

int output_da_fast(float voltage[])
{
	int ret=0,i,j;
	unsigned char dev_addr = MCP4728_ADDR;
	fastmode_data data[4];
	unsigned char buf[8];

	for(i=0;i<MAX_CH; i++)
	{
		data[i].config.command=0;
		data[i].config.PD=0;

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

		data[i].config.DAC_DAT = (int)(voltage[i]* DAC_MAX_DATA / DAC_MAX_VOLT);
	}


	for(j=0;j<MAX_CH;j++)
	{
		// エンディアン変換しながら全送信データ結合
		for(i=0;i<2;i++)
			buf[j*2 +i] = data[j].byte[1-i];

		// ビッグエンディアンの場合は変換しない
		// memcpy(&buf[j*2],data[j].byte, sizeof(data[j].byte));
	}


	i2c_write(dev_addr,buf,sizeof(buf));

	return ret;
}

int main(int argc, char *argv[])
{
	float voltage[4];
	float single;
	int ch;
	char *endptr;

//	ch = strtol(argv[1], &endptr,10);
//	single  =strtof(argv[2],&endptr);
//	output_da(ch,voltage);

	voltage[CH_A] = 3.0;
	voltage[CH_B] = 2.0;
	voltage[CH_C] = 1.0;
	voltage[CH_D] = 0.5;

	output_da_fast(voltage);
	return 0;
}
