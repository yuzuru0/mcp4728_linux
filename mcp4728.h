#ifndef __MCP4728_H__
#define __MCP4728_H__

#define MCP4728_ADDR 0x60

#define SINGLE_WRITE 0x0B

#define DAC_ADDRESS_A 0x58
#define DAC_ADDRESS_B 0x5A
#define DAC_ADDRESS_C 0x5C
#define DAC_ADDRESS_D 0x5E
#define DAC_ADDRESS_BASE 0x58

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

#define DAC_MAX_DATA 0x0FFF
#define DAC_MAX_VOLT 4.096	//	内部Vref, 出力2倍ゲイン
#define DAC_MIN_VOLT 0.0

#define MAX_CH 4

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
		unsigned int DAC:2;
		unsigned int command:5;
	}config;
}mcp4728_config_data;


typedef union
{
	unsigned short fast_command;
	unsigned char byte[2];
	struct
	{
		unsigned int DAC_DAT:12;
		unsigned int PD:2;
		unsigned int command:2;
	}config;
}fastmode_data;

int output_da(int ch, float voltage);
int output_da_fast(float voltage[]);

#endif

