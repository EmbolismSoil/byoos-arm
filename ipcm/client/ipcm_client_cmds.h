/*
 * Author: Aananth C N
 * Date: 26 Oct 2014
 * License: GPLv2
 * Email: c.n.aananth@gmail.com
 *
 * Purpose: This file contains all declarations for memory based inter-processor
 * communications.
 */

#ifndef BYOOS_IPCM_CLIENT_H
#define BYOOS_IPCM_CLIENT_H

#include "types.h"
#include "byoos_config.h"

void ipcm_read(struct ipcm_block *pb);
void ipcm_write(struct ipcm_block *pb);
void ipcm_debug_set(struct ipcm_block *pb);


#endif
