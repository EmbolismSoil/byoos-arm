/*
 * Author: Aananth C N
 * Date: 25 Oct 2014
 * License: GPLv2
 * Email: c.n.aananth@gmail.com
 *
 * Purpose: This file contains the commands supported IPCM
 */

/*
 * To add any new commands, just call macro IPCM_CMD(COMMAND_NAME) as given
 * below.
 *
 * The ipcm.c file will take care of defining the enum and adding an entry in 
 * IPCM function table, at the time of pre-processing.
 */
IPCM_CMD(NOP)	/* No operation */
IPCM_CMD(READ)	/* Read - the initiator, client/server wants to read */
IPCM_CMD(WRITE) /* Write - the initator wants to write */
