/*
 * Author: Aananth C N
 * Date: 26 Oct 2014
 * License: GPLv2
 * Email: c.n.aananth@gmail.com
 *
 * Purpose: This file contains all definitions related to ipcm server
 */
#include "ipcm.h"
#include "debug.h"

struct ipcm_block *pserver_block;
struct ipcm_block *pclient_block;

int ipcm_init(void)
{
	int ipcm_block_size;
	int *p;
	int i;

	pserver_block = (struct ipcm_block *)CONFIG_IPCM_SRV_BLK_ADDR;
	pclient_block = (struct ipcm_block *)((u8*)pserver_block +
				sizeof(struct ipcm_block));

	ipcm_block_size = sizeof(struct ipcm_block);
	p = (int *) pserver_block;
	for(i=0; i < ipcm_block_size; i+=4) {
		*p++ = 0;
	}
	p = (int *) pclient_block;
	for(i=0; i < ipcm_block_size; i+=4) {
		*p++ = 0;
	}

	return 0;
}

int ipcm_exec(void)
{
	if(pserver_block->cmd_cnt != pserver_block->resp_cnt) {
		if(pserver_block->cmd_id < MAX_IPCM_CMDS) {
			if(ipcm_cmd_table[pserver_block->cmd_id].cmd_fn()) {
				debugp(ERROR_MSG, "IPCM command failed!\n");
			}
		}
		else {
			debugp(ERROR_MSG, "Unknown IPCM command!\n");
		}
		pserver_block->resp_cnt = pserver_block->cmd_cnt;
	}

	return 0;
}
