/*
 * Author: Aananth C N
 * Date: 16 Oct 2014
 * License: GPLv2
 * Email: c.n.aananth@gmail.com
 *
 * Purpose: This file contains all declarations that are required to support 
 * debug requirements for BYOOS
 */
#ifndef BYOOS_DEBUG_H
#define BYOOS_DEBUG_H

enum {
	INFO_MSG,
	WARN_MSG,
	ERROR_MSG
};

void debugp(int dlevel, const char *str);
void debug_sys_init(void);

#endif
