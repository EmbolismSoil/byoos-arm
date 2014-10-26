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

int ipcm_fun_NOP(void)
{
	debugp(INFO_MSG, "BYOOS: Linux client called \"NOP\" function!\n");
	return 0;
}

int ipcm_fun_READ(void)
{
	debugp(INFO_MSG, "BYOOS: Linux client called \"READ\" function!\n");
	return 0;
}

int ipcm_fun_WRITE(void)
{
	debugp(INFO_MSG, "BYOOS: Linux client called \"WRITE\" function!\n");
	return 0;
}
