#include <stdio.h>
#include <stdlib.h>
#include "mcp4728.h"
#include "i2c_interface.h"

int main(int argc, char *argv[])
{
	float voltage;
	int ch;
	char *endptr;

	ch = strtol(argv[1], &endptr,10);
	voltage =strtof(argv[2],&endptr);


	output_da(ch, voltage);
	return 0;
}
