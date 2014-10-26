# Author: Aananth C N
# Date: 26 October 2014
# License: GPLv2
# Email: c.n.aananth@gmail.com
#
# This is a makefile for ipcm Linux client.


.PHONY: all
.DEFAULT: all

PROJ_ROOT = ../..
TOOLCHAIN = arm-linux-gnueabi

CC = ${TOOLCHAIN}-gcc
AS = ${TOOLCHAIN}-as
AR = ${TOOLCHAIN}-ar
PP = ${TOOLCHAIN}-cpp
LD = ${TOOLCHAIN}-ld
OC = ${TOOLCHAIN}-objcopy

TARGET 	= ${PROJ_ROOT}/ipcm_client

# Though ARM Cortex A9 supports both little and big endian but I.MX supports
# little endian only!!
IFLAGS = -I. -I${PROJ_ROOT} -I${PROJ_ROOT}/ipcm

CFLAGS 	= -c -g \
	-mlittle-endian \
	-Wall \
	-O1

LFLAGS = -g 


COBJS = ipcm_client.o 


all: $(COBJS)
	@echo ""
	@echo "---------------------------------------------------------------"
	@echo "linking ${TARGET}..." 
	@echo "---------------------------------------------------------------"
	$(CC) -o ${TARGET} $^ ${LFLAGS} 
	@echo ""

%.o: %.c
	@echo ""
	@echo "compiling $<"
	$(CC) -o $@ $< $(CFLAGS) $(IFLAGS)
	@echo ""

clean: 
	@echo ""
	@echo "---------------------------------------------------------------"
	@echo "cleaning ipcm client..."
	@echo "---------------------------------------------------------------"
	$(RM) ${COBJS} ${TARGET}
	@echo ""
