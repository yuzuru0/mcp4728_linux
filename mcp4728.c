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

	reg_addr = DAC_ADDRESS_BASE || ch<<1;

	mcp4728.config.VREF = VREF_INTERNAL;
	mcp4728.config.PD = PD_NORMAL;
	mcp4728.config.Gx = GAIN_X2;

	mcp4728.config.DAC_DATA = (int)(voltage * DAC_MAX_DATA / DAC_MAX_VOLT);


	printf("%x - %x %x %x %d\n",mcp4728.i2c_data, mcp4728.byte[0],mcp4728.byte[1],mcp4728.byte[2], sizeof(mcp4728.byte));


	i2c_write(dev_addr, reg_addr, mcp4728.byte, sizeof(mcp4728.byte)); 

	return ret;

}
int main(void)
{
	unsigned char dev_addr = 0x60;
	unsigned char reg_addr = DAC_ADDRESS_A;

	mcp4728_config_data mcp4728;

	mcp4728.config.VREF = VREF_INTERNAL;
	mcp4728.config.PD = PD_NORMAL;
	mcp4728.config.Gx = GAIN_X2;

	mcp4728.config.DAC_DATA = 0x07FF;

	printf("%x - %x %x %x %d\n",mcp4728.i2c_data, mcp4728.byte[0],mcp4728.byte[1],mcp4728.byte[2], sizeof(mcp4728.byte));

	i2c_write(dev_addr, reg_addr, mcp4728.byte, sizeof(mcp4728.byte)); 

	
	return 0;
}
