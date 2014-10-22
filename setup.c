/*
 * Author: Aananth C N
 * Date: 15 Oct 2014
 * License: GPLv2
 * Email: c.n.aananth@gmail.com
 *
 * Purpose: This file has definitions that are required to initialize the ARM
 * core required for "BYOOS" to run.
 *
 * Note -- the entry function byoos_setup() is placed in section ".setup"
 */
#include "byoos_config.h" /* soc_setup() declaration comes via this file */
#include "byoos.h"

extern int byoos_setup(void) __attribute__((section(".setup")));

/* ARM Snoop Control Unit (SCU) registers -- Thanks to NVIDIA for the structure
 * below */
struct scu_reg {
	u32 scu_ctrl;          /* SCU Control Register, offset 00 */
	u32 scu_cfg;           /* SCU Config Register, offset 04 */
	u32 scu_cpu_pwr_stat;  /* SCU CPU Power Status Register, offset 08 */
	u32 scu_inv_all;       /* SCU Invalidate All Register, offset 0C */
	u32 scu_reserved0[12]; /* reserved, offset 10-3C */
	u32 scu_filt_start;    /* SCU Filtering Start Address Reg, offset 40 */
	u32 scu_filt_end;      /* SCU Filtering End Address Reg, offset 44 */
	u32 scu_reserved1[2];  /* reserved, offset 48-4C */
	u32 scu_acc_ctl;       /* SCU Access Control Register, offset 50 */
	u32 scu_ns_acc_ctl;    /* SCU Non-secure Access Cntrl Reg, offset 54 */
};

#define SCU_CTRL_ENABLE			(1 << 0)
#define SCU_CTRL_STANDBY		(1 << 5)
#define SCU_CFG_CORE0_BIT_OFFSET	(4)

#define dmb()			__asm__ __volatile__ ("" : : : "memory")
#define __iormb()		dmb()
#define __iowmb()		dmb()
#define __arch_putl(v,a)	(*(volatile unsigned int *)(a) = (v))
#define __arch_getl(a)		(*(volatile unsigned int *)(a))

#define writel(v,c)	({ u32 __v = v; __iowmb(); __arch_putl(__v,c); __v; })
#define readl(c)        ({ u32 __v = __arch_getl(c); __iormb(); __v; })


int arm_setup(int core)
{
	struct scu_reg *scu;
	u32 reg;

	if((core < 0) || (core > 3))
		return -1;
	/* c15 register of co-processor contain scu base address. Note: This 
	 * is a memory mapped address, see the SOC reference manual also */
	asm("mrc p15, 4, %0, c15, c0, 0" : "=r" (reg));
	scu = (struct scu_reg *) reg;

	/* disable SMP or set AMP for the core passed */
	reg = readl(&scu->scu_cfg);
	reg &= ~(1 << (SCU_CFG_CORE0_BIT_OFFSET + core));
	writel(reg, &scu->scu_cfg);

	/* enable snoop control unit (scu), if not enabled */
	if((readl(&scu->scu_ctrl) & (SCU_CTRL_ENABLE|SCU_CTRL_STANDBY)) != 0) {
		reg = readl(&scu->scu_ctrl);
		reg &= ~(SCU_CTRL_ENABLE|SCU_CTRL_STANDBY);
		writel(reg, &scu->scu_ctrl);
	}

	return (u32) scu;
}

/* 
 * Entry point from u-boot. 
 */
int byoos_setup(void)
{
	int retval;

	*((unsigned long *)(0x021F0040)) = '%'; /* TODO: Remove this!! */
	*((unsigned long *)(0x021F0040)) = '\n'; /* TODO: Remove this!! */
	*((unsigned long *)(0x021F0040)) = '\r'; /* TODO: Remove this!! */
	retval = arm_setup(CONFIG_MYOS_CORE);
	soc_setup_n_go(CONFIG_MYOS_CORE);

	return retval;
}
