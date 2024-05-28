#include <stdio.h>
#include "mcp4728.h"
#include "i2c_interface.h"

int main(void)
{
	unsigned char dev_addr = 0x60;
	unsigned char reg_addr = 0xC0;

	mcp4728_config_data mcp4728_config;

	mcp4728_config.COMMAND = SINGLE_WRITE;
	mcp4728_config.DAC_CH = CH_A;
	mcp4728_config.UDAC = EN_LATCH;
	mcp4728_config.VREF = VREF_INTERNAL;
	mcp4728_config.PD = PD_NORMAL;
	mcp4728_config.Gx = GAIN_X2;

	mcp4728_config.DAC_DATA = 0x0FFF;



	
	return 0;
}
