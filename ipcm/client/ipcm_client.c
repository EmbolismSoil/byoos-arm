/*
 * Author: Aananth C N
 * Date: 26 Oct 2014
 * License: GPLv2
 * Email: c.n.aananth@gmail.com
 *
 * Purpose: This file contains all definitions related to ipcm server
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include "ipcm.h"
#include "ipcm_client_cmds.h"

int fdmem;
int ipcm_block_size;
void *map;

struct ipcm_block *pserver_block;
struct ipcm_block *pclient_block;


int ipcm_init(void)
{
	ipcm_block_size = sizeof(struct ipcm_block);

	fdmem = open("/dev/mem", O_RDWR);
	map = mmap(NULL, ipcm_block_size, PROT_READ | PROT_WRITE, MAP_SHARED,
			fdmem, CONFIG_IPCM_SRV_BLK_ADDR);

	pserver_block = (struct ipcm_block *)map;
	pclient_block = (struct ipcm_block *)((u8*)pserver_block +
				sizeof(struct ipcm_block));

	return 0;
}

int ipcm_exit(void)
{
	munmap(map, ipcm_block_size);
	close(fdmem);

	/* create_thread_for_rx_from_server() TODO: this will be done later */

	return 0;
}

int ipcm_exec(void)
{
	char cmd[128];

	printf("Type any of the following commands:\n");
	printf(" read  - to read data from BYOOS\n");
	printf(" write - to write data to BYOOS\n");
	printf(" debug - to change debug level of BYOOS\n");
	printf(" quit  - to exit this application\n");
	if(EOF == scanf("%s", cmd)) {
		return 0;
	}

	if(strcmp(cmd, "quit") == 0) {
		return 1;
	}
	else if(strcmp(cmd, "read") == 0) {
		ipcm_read(pserver_block);
	}
	else if(strcmp(cmd, "write") == 0) {
		ipcm_write(pserver_block);
	}
	else if(strcmp(cmd, "debug") == 0) {
		ipcm_debug_set(pserver_block);
	}
	else {
		return 0;
	}

	return 0;
}

int main(void)
{
	int die = 0;

	ipcm_init();

	while(!die) {
		die = ipcm_exec();
	}

	ipcm_exit();

	return 0;
}
