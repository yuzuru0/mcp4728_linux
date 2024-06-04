#include <stdio.h>
#include <unistd.h>
#include "mcp4728.h"
#include "i2c_interface.h"

int main(void)
{
	unsigned char dev_addr = 0x60;
	unsigned char reg_addr = ADDRESS_A;

	mcp4728_config_data mcp4728;

	mcp4728.config.VREF = VREF_INTERNAL;
	mcp4728.config.PD = PD_NORMAL;
	mcp4728.config.Gx = GAIN_X2;


	//printf("%x - %x %x %x %d\n",mcp4728.i2c_data, mcp4728.byte[0],mcp4728.byte[1],mcp4728.byte[2], sizeof(mcp4728.byte));

//	while(1)
//	{
		mcp4728.config.DAC_DATA = 0x7FF;
		i2c_write(dev_addr, reg_addr, mcp4728.byte, sizeof(mcp4728.byte));

		usleep(30000);


		mcp4728.config.DAC_DATA=0x000;
		i2c_write(dev_addr, reg_addr, mcp4728.byte, sizeof(mcp4728.byte));

//	}

	
	return 0;
}
