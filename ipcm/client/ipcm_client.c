/*
 * Author: Aananth C N
 * Date: 26 Oct 2014
 * License: GPLv2
 * Email: c.n.aananth@gmail.com
 *
 * Purpose: This file contains all definitions related to ipcm server
 */
#include "ipcm.h"
#include <stdio.h>


void ipcm_init(void)
{
}

void ipcm_exec(void)
{
}

int main(void)
{
	int cmd;


	ipcm_init();

	while(1) {
		printf("Type something, \'q\' to exit\n");
		scanf("%c", &cmd);

		if(cmd == 'q') {
			break;
		}
		else {
			ipcm_exec();
		}
	}
}
