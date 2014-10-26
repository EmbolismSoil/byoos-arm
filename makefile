# Author: Aananth C N
# Date: 09 October 2014
# License: GPLv2
# Email: c.n.aananth@gmail.com
#
# This is a makefile for a tiny OS built using GNU toolchains

include ipcm/ipcm.mk

.PHONY: all

TOOLCHAIN = arm-none-eabi

CC = ${TOOLCHAIN}-gcc
AS = ${TOOLCHAIN}-as
AR = ${TOOLCHAIN}-ar
PP = ${TOOLCHAIN}-cpp
LD = ${TOOLCHAIN}-ld
OC = ${TOOLCHAIN}-objcopy

TARGET 	= byoos

# Though ARM Cortex A9 supports both little and big endian but I.MX supports
# little endian only!!
IFLAGS = -I. -I./ipcm/

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



all: $(AOBJS) $(COBJS) $(IPCM_LIB)
	@echo ""
	@echo "----------------------------------------------------------------------"
	@echo "linking..." 
	@echo "----------------------------------------------------------------------"
	$(LD) -o ${TARGET} $^ ${LFLAGS} -T ${TARGET}.lds
	$(OC) $(TARGET) -O binary $(TARGET).bin
	@echo ""
	@echo "----------------------------------------------------------------------"
	@echo "Building IPCM Client"
	@echo "----------------------------------------------------------------------"
	$(MAKE) -C ipcm/client
	@echo ""


%.o: %.c
	@echo ""
	@echo "compiling $<"
	$(CC) -o $@ $< $(CFLAGS) $(IFLAGS)
	@echo ""

%.o: %.s
	@echo ""
	@echo "preprocessing $<"
	$(PP) -o $(subst .o,.p,$@) $<
	@echo ""
	@echo "assembling $<"
	$(AS) -o $@ $(subst .s,.p,$<) $(AFLAGS)
	@echo ""

clean: ipcm_clean
	@echo ""
	@echo "----------------------------------------------------------------------"
	@echo "cleaning..."
	@echo "----------------------------------------------------------------------"
	$(RM) ${COBJS} ${AOBJS} ${TARGET} *.p ${TARGET}.bin ${TARGET}.map
	@echo ""
	$(MAKE) -C ipcm/client clean
