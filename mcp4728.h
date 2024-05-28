#ifndef __MCP4728_H__
#define __MCP4728_H__

typedef union
{
	unsigned int i2c_data;
	unsigned char byte[4];

	struct
	{
		unsigned int DAC_DATA:12;
		unsigned int Gx:1;
		unsigned int PD:2;
		unsigned int VREF:1;

		unsigned int UDAC:1;
		unsigned int DAC_CH:2;
		unsigned int COMMAND:5;

		unsigned int ADDRESS:8;
	}config;
}mcp4728_config;


#endif

