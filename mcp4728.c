#include <stdio.h>
#include <stdlib.h>
#include "mcp4728.h"
#include "i2c_interface.h"

int output_da(int ch, float voltage)
{
	int ret=0;
	unsigned char dev_addr = MCP4728_ADDR;
	unsigned char reg_addr;
	mcp4728_config_data mcp4728;

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

	reg_addr = DAC_ADDRESS_BASE | ch<<1;

	mcp4728.config.VREF = VREF_INTERNAL;
	mcp4728.config.PD = PD_NORMAL;
	mcp4728.config.Gx = GAIN_X2;

	mcp4728.config.DAC_DATA = (int)(voltage * DAC_MAX_DATA / DAC_MAX_VOLT);


//	printf("%x %x \n",reg_addr, mcp4728.i2c_data );
	i2c_write(dev_addr, reg_addr, mcp4728.byte, sizeof(mcp4728.byte)); 

	return ret;

}
int main(int argc, char *argv[])
{
	float voltage;
	int ch;
	char *endptr;
	unsigned char dev_addr = MCP4728_ADDR;
	unsigned char reg_addr;
	unsigned char send_data[7];

//	ch = strtol(argv[1], &endptr,10);
//	voltage =strtof(argv[2],&endptr);


//	output_da(ch, voltage);
	while(1)
	{
		reg_addr = 0x03;
		send_data[0] = 0xFF;
		send_data[1] = 0x03;
		send_data[2]= 0xFF;
		send_data[3] = 0x03;
		send_data[4] = 0xFF;
		send_data[5] = 0x03;
		send_data[6] = 0xFF;
		i2c_write(dev_addr, reg_addr , send_data, sizeof(send_data));


		reg_addr = 0x00;
		send_data[0] = 0x00;
		send_data[1] = 0x00;
		send_data[2]= 0x00;
		send_data[3] = 0x00;
		send_data[4] = 0x00;
		send_data[5] = 0x00;
		send_data[6] = 0x00;
		i2c_write(dev_addr, reg_addr , send_data, sizeof(send_data));
	}

	

	return 0;
}
