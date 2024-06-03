#include <stdio.h>
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


	printf("%x %x \n",reg_addr, mcp4728.i2c_data );
	i2c_write(dev_addr, reg_addr, mcp4728.byte, sizeof(mcp4728.byte)); 

	return ret;

}
int main(void)
{

	output_da(CH_A, 2.0);
	return 0;
}
