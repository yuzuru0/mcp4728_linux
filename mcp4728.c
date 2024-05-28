#include <stdio.h>
#include "mcp4728.h"
#include "i2c_interface.h"

int main(void)
{
	unsigned char dev_addr = 0x60;
	unsigned char reg_addr = 0x58;

	mcp4728_config_data mcp4728;

	mcp4728.config.VREF = VREF_INTERNAL;
	mcp4728.config.PD = PD_NORMAL;
	mcp4728.config.Gx = GAIN_X2;

	mcp4728.config.DAC_DATA = 0x07FF;

	printf("%x - %x %x %x %d\n",mcp4728.i2c_data, mcp4728.byte[0],mcp4728.byte[1],mcp4728.byte[2], sizeof(mcp4728.byte));

	i2c_write(dev_addr, reg_addr, mcp4728.byte, sizeof(mcp4728.byte)); 

	
	return 0;
}
