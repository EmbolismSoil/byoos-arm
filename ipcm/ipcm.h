/*
 * Author: Aananth C N
 * Date: 25 Oct 2014
 * License: GPLv2
 * Email: c.n.aananth@gmail.com
 *
 * Purpose: This file contains all declarations for memory based inter-processor
 * communications.
 */

#ifndef BYOOS_IPCM_H
#define BYOOS_IPCM_H

#include "types.h"
#include "byoos_config.h"

/* 
 * IPCM 
 * ====
 *
 * Concept: Client-Server architecture
 *
 * Two separate blocks of memory will be allocated, with Server on bottom and
 * Client on top (see picture below)
 *
 *                  +--------+---------+----------+------------+-------------+
 *                 /| cmd_id | cmd_cnt | resp_cnt |  cmd_data  |  resp_data  |
 *   client_block:--+--------+---------+----------+------------+-------------+
 *                 /| cmd_id | cmd_cnt | resp_cnt |  cmd_data  |  resp_data  |
 *   server_block --+--------+---------+----------+------------+-------------+
 *
 *
 * Communication Rules
 * -------------------
 *  1. BYOOS is always a "server". (No arguments!)
 *
 *  2. client_block_offset = server_block_offset + server_block_size
 *
 *  3. Condition for a client or server to talk is, the other side's "cmd_cnt"
 *     and "resp_cnt" are equal, but for CONFIG_IPCM_TIMEOUT period.
 *
 *  4. The initiator of the communication, will first write the "cmd_id" and
 *     write the "cmd_data" and finally increment the "cmd_cnt", once the
 *     condition for communication is met.
 *
 *  5. The respondent has to then process the command, write the "resp_data" and
 *     finally increment the "resp_cnt"
 *
 *  6. If timeout happens, the last command shall be retried once, else cmd_cnt 
 *     shall be decremented
 *
 *  7. The client can write cmd_id, cmd_cnt and cmd_data fields of the server
 *     block. But the server can only read them.
 *
 *  8. Similarly, client can only read resp_cnt, resp_data. Only the server can
 *     clear or update these 2 fields.
 */

struct ipcm_data {
	u32 len;
	u8 data[CONFIG_IPCM_DATA_LEN - sizeof(u32)];
};

struct ipcm_block {
	u32 cmd_id;
	u32 cmd_cnt;
	u32 resp_cnt;
	struct ipcm_data cmd_data;
	struct ipcm_data resp_data;
};

/* IPCM command ID enum is created at pre-processing time here */
#undef IPCM_CMD
#define IPCM_CMD(x)	IPCM_CMD_##x,
typedef enum {
#include "ipcm_cmds.h"
	MAX_IPCM_CMDS
}ipcm_cmd_t;

struct ipcm_cmd {
	ipcm_cmd_t cmd_id;
	int (*cmd_fn)(void);
};

/* IPCM command functions declarations done at pre-processing time here */
#undef IPCM_CMD
#define IPCM_CMD(x)	int ipcm_fun_##x(void);
#include "ipcm_cmds.h"
#endif

extern struct ipcm_cmd ipcm_cmd_table[];

void ipcm_init(void);
void ipcm_exec(void);
