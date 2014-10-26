/*
 * Author: Aananth C N
 * Date: 26 Oct 2014
 * License: GPLv2
 * Email: c.n.aananth@gmail.com
 *
 * Purpose: This file contains implementation of IPCM client commands
 */
#include <stdio.h>
#include <unistd.h>

#include "ipcm.h"

void ipcm_read(struct ipcm_block *pb)
{
	pb->cmd_data.len = 1;
	pb->cmd_data.data[0] = 'r';
	pb->cmd_id = IPCM_CMD_READ;
	pb->cmd_cnt++;
	usleep(100*1000);

	if(pb->cmd_cnt == pb->resp_cnt) {
		printf("%s\n", pb->resp_data.data);
	}
	else {
		printf("The other operating system has not responded\n");
	}
}

void ipcm_write(struct ipcm_block *pb)
{
	int cmd_len;

	printf("Type the message you want to send:");
	cmd_len = scanf("%s", pb->cmd_data.data);
	if(cmd_len == EOF) {
		return;
	}

	pb->cmd_data.len = cmd_len;
	pb->cmd_id = IPCM_CMD_WRITE;
	pb->cmd_cnt++;
	printf("The message is sent successfully!\n");
}

void ipcm_debug_set(struct ipcm_block *pb)
{
	int debug_level;
	int cmd_len;

	printf("Type the debug level (0 to 255):");
	cmd_len = scanf("%d", &debug_level);
	if(cmd_len == EOF) {
		return;
	}

	pb->cmd_data.data[0] = (u8) debug_level;
	pb->cmd_data.len = 1;
	pb->cmd_id = IPCM_CMD_DEBUG_SET;
	pb->cmd_cnt++;
}
