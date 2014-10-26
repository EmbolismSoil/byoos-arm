/*
 * Author: Aananth C N
 * Date: 16 Oct 2014
 * License: GPLv2
 * Email: c.n.aananth@gmail.com
 *
 * Purpose: This file contains all definitions that are required to support the
 * debug requirements for BYOOS
 */
#include "debug.h"
#include "byoos_config.h"
#include "serial.h"

#include <stdio.h>

static volatile int system_dlevel;
static char prompt[] = "BYOOS$ ";

void debugp(int dlevel, const char *str)
{
	int i;

	if(dlevel >= system_dlevel) {
		for(i = 0; prompt[i]; i++) {
			serial_putc(prompt[i]);
		}

		for(i = 0; (i < CONFIG_DEBUG_CHAR_MAX) && str[i]; i++) {
			serial_putc(str[i]);
		}
	}
}
