/*
 * Author: Aananth C N
 * Date: 10 Oct 2014
 * License: GPLv2
 * Email: c.n.aananth@gmail.com
 *
 * Purpose: This file contains all definitions that are required to support the
 * debug requirements for BYOOS (Boot Your Own Operating System)
 */
#include <stdint.h>
#include "byoos_config.h"
#include "debug.h"
#include "serial.h"

/*-----------------------------------------------------------------------------
 * Globals */

#define RELOAD_VAL	(65536 * 50)
volatile u32 Count = 0x1234;


/*-----------------------------------------------------------------------------
 * Functions */

void low_level_init(void (*reset_addr)(), void (*return_addr)())
{
	/* nothing so far */
}

/* All BYOOS init are done here */
void byoos_init(void)
{
	//serial_init(); FIXME: Do not init serial until we have a design to
	//manage terminal outputs printed or scanned by Linux OS in BYOOS.
	//For now, let byoos abuse the serial terminal :-). 
}

/* BYOOS main */
int byoos_main(void)
{
	byoos_init();
	debugp(INFO_MSG, "BYOOS init complete, entering main loop \n");

	while(1) {
		Count--;
		if(Count == 0) {
			Count = RELOAD_VAL;
			debugp(INFO_MSG, "DI Kernel is alive\n");
		}
	}

	return 0;
}
