# Author: Aananth C N
# Date: 09 October 2014
# License: GPLv2
# Email: c.n.aananth@gmail.com
#
# This is a makefile for a tiny OS built using GNU toolchains

CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
PP = arm-none-eabi-cpp
LD = arm-none-eabi-ld
OC = arm-none-eabi-objcopy

TARGET 	= byoos

# Though ARM Cortex A9 supports both little and big endian but I.MX supports
# little endian only!!
CFLAGS 	= -c -g \
	-mlittle-endian \
	-Wall \
	-mthumb-interwork \
	-O1

# \
	-mlong-calls \

AFLAGS 	= -c -g -mlittle-endian \
	-mthumb-interwork \


LFLAGS = -g -Map=${TARGET}.map --cref -lgcc -L/usr/lib/gcc/arm-none-eabi/4.8.2/


COBJS = byoos.o \
	setup.o \
	debug.o \
	imx6x.o \
	serial.o

AOBJS = startup.o

all: byoos_objs 

byoos_objs: $(AOBJS) $(COBJS)
	@echo ""
	@echo "----------------------------------------------------------------------"
	@echo "linking..." 
	@echo "----------------------------------------------------------------------"
	$(LD) -o ${TARGET} $^ ${LFLAGS} -T ${TARGET}.lds
	$(OC) $(TARGET) -O binary $(TARGET).bin
	@echo ""


%.o: %.c
	@echo ""
	@echo "compiling $<"
	$(CC) -o $@ $< $(CFLAGS)
	@echo ""

%.o: %.s
	@echo ""
	@echo "preprocessing $<"
	$(PP) -o $(subst .o,.p,$@) $<
	@echo ""
	@echo "assembling $<"
	$(AS) -o $@ $(subst .s,.p,$<) $(AFLAGS)
	@echo ""


clean:
	@echo ""
	@echo "----------------------------------------------------------------------"
	@echo "cleaning..."
	@echo "----------------------------------------------------------------------"
	$(RM) ${COBJS} ${AOBJS} ${TARGET} *.p ${TARGET}.bin ${TARGET}.map
	@echo ""
