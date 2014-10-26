# Author: Aananth C N
# Date: 25 October 2014
# License: GPLv2
# Email: c.n.aananth@gmail.com
#
# This is a makefile for a tiny OS built using GNU toolchains

IPCM_LIB = ipcm_lib.o

IPCM_OBJS = 	ipcm/ipcm.o \
		ipcm/server/ipcm_client_cmds.o \
		ipcm/server/ipcm_server.o

$(IPCM_LIB): $(IPCM_OBJS)
	$(AR) rvs $@ $^

ipcm_clean:
	$(RM) $(IPCM_OBJS) $(IPCM_LIB)

