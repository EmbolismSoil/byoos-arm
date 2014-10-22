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
volatile u32 Count;


/*-----------------------------------------------------------------------------
 * Functions */

void low_level_init(void (*reset_addr)(), void (*return_addr)())
{
	/* nothing so far */
}

/* All BYOOS init are done here */
void byoos_init(void)
{
	//serial_init();
}

/* BYOOS main */
int byoos_main(void)
{
	static u8 ascii;

	*((volatile unsigned long *)(0x021F0040)) = '#';
	*((volatile unsigned long *)(0x021F0040)) = '\n';
	byoos_init();
	*((volatile unsigned long *)(0x021F0040)) = '$';
	*((volatile unsigned long *)(0x021F0040)) = '\n';
	//debugp(INFO_MSG, "MYOS init complete, entering main loop \n");

	*((volatile unsigned long *)(0x021F0040)) = '@';
	*((volatile unsigned long *)(0x021F0040)) = '\n';

	Count = RELOAD_VAL;
	ascii = '0';
	while(1) {
		Count--;
		if(Count == 0) {
			Count = RELOAD_VAL;
			//debugp(INFO_MSG, "DI Kernel is alive");
			*((volatile unsigned long *)(0x021F0040)) = ascii;
			*((volatile unsigned long *)(0x021F0040)) = '\n';
			*((volatile unsigned long *)(0x021F0040)) = '\r';
			if(ascii == 'z') {
				ascii = '0';
			}
			else {
				ascii++;
			}
		}
	}

	return 0;
}
