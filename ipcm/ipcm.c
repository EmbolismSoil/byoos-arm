/*
 * Author: Aananth C N
 * Date: 25 Oct 2014
 * License: GPLv2
 * Email: c.n.aananth@gmail.com
 *
 * Purpose: This file contains all definitions for memory based inter-processor
 * communications.
 */
#include "ipcm.h"
#include "debug.h"

#undef IPCM_CMD
#define IPCM_CMD(x)	{ IPCM_CMD_##x, ipcm_fun_##x },
struct ipcm_cmd ipcm_cmd_table[] = {
#include "ipcm_cmds.h"
	{ MAX_IPCM_CMDS, (int (*)(void))0 }
};
