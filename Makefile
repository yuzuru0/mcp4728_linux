CC      = gcc
CFLAGS	= -g -O2 -Wall -I.
LDFLAGS =
LIBS    =
PROGRAM = mcp4728 
OBJS	= mcp4728.c i2c_interface.c

all:$(PROGRAM)

$(PROGRAM):	$(OBJS)
			$(CC) $(OBJS) -o $(PROGRAM)

clean:; rm -f *.o $(PROGRAM)
