#ifndef __MCP4728_H__
#define __MCP4728_H__

#define SINGLE_WRITE 0x0B

#define CH_A 0x00
#define CH_B 0x01
#define CH_C 0x02
#define CH_D 0x03

#define EN_LATCH 0x00

#define VREF_INTERNAL 0x01
#define VREF_EXTERNAL 0x00

#define PD_NORMAL 0x00
#define PD_1K	0x01
#define PD_100K 0x02
#define PD_500K 0x03

#define GAIN_X2 0x01
#define GAIN_X1 0x00



typedef union
{
	unsigned int i2c_data;
	unsigned char byte[3];

	struct
	{
		unsigned int DAC_DATA:12;
		unsigned int Gx:1;
		unsigned int PD:2;
		unsigned int VREF:1;

		unsigned int UDAC:1;
		unsigned int DAC_CH:2;
		unsigned int COMMAND:5;

		unsgined int UNUSED:8;
	}config;
}mcp4728_config_data;


#endif

