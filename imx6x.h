/*
 * Author: Aananth C N
 * Date: 14 Oct 2014
 * License: GPLv2
 * Email: c.n.aananth@gmail.com
 *
 * Purpose: Contains definitions and declarations related to Freescale I.MX6Q
 * micro controller.
 */
#ifndef BYOOS_IMX6QDQ_H
#define BYOOS_IMX6QDQ_H

#include "types.h"

/* System Reset Controller */
#define SRC_BASE	0x020D8000
#define SRC_SCR		(SRC_BASE+0x0)
#define SRC_GPR1	(SRC_BASE+0x20)

#define ENTRY_VECTOR_CORE(x)	(SRC_GPR1 + (4 * 2 * x))
#define ENTRY_ARGREG_CORE(x)	(ENTRY_VECTOR_CORE(x) + 4)

#define SRC_CORE1_BIT_OFFSET	(22)

#define AIPS1_ARB_BASE_ADDR	0x02000000
#define AIPS2_ARB_BASE_ADDR	0x02100000

#define CCM_BASE_ADDR	(AIPS1_ARB_BASE_ADDR + 0x44000)

/* UART Registers */
#define UART1_BASE	(AIPS1_ARB_BASE_ADDR + 0x20000)
#define UART2_BASE	(AIPS2_ARB_BASE_ADDR + 0xE8000)
#define UART3_BASE	(AIPS2_ARB_BASE_ADDR + 0xEC000)
#define UART4_BASE	(AIPS2_ARB_BASE_ADDR + 0xF0000)
#define UART5_BASE	(AIPS2_ARB_BASE_ADDR + 0xF4000)


/* General Macros */
#define __raw_readl(a)	(*(volatile u32 *)(a))
#define __REG(x)	(*((volatile u32 *)(x)))


/* Stubs */
#define WATCHDOG_RESET()	{ }

u32 get_uart_clk(void);

int soc_setup_n_go(int core);



#endif
