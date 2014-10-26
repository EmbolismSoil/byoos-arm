/*
 * Author: Aananth C N
 * Date: 25 Oct 2014
 * License: GPLv2
 * Email: c.n.aananth@gmail.com
 *
 * Purpose: This file contains IPCM commands invoked by client (Linux) 
 */
#include "ipcm.h"
#include "debug.h"

int ipcm_fun_NOP(void)
{
	debugp(INFO_MSG, "BYOOS: Linux client called \"NOP\" function!\n");
	return 0;
}

extern struct ipcm_block *pserver_block; // FIXME: Redesign this command processing.

int ipcm_fun_READ(void)
{
	int i;
	char rstr[] = "Hi, this is BYOOS responding to Linux Client's READ function\n";

	debugp(INFO_MSG, "BYOOS: Linux client called \"READ\" function!\n");
	for(i = 0; rstr[i]; i++) {
		pserver_block->resp_data.data[i] = rstr[i];
	}

	return 0;
}

int ipcm_fun_WRITE(void)
{
	debugp(INFO_MSG, "BYOOS: Linux client called \"WRITE\" function!\n");
	debugp(INFO_MSG, pserver_block->cmd_data.data);
	debugp(INFO_MSG, "\n");
	return 0;
}

int ipcm_fun_DEBUG_SET(void)
{
	debugp(INFO_MSG,"ipcm_fun_DEBUG_SET() called\n");
	set_debug_level((int)pserver_block->cmd_data.data[0]);
	return 0;
}
