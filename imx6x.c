/*
 * Author: Aananth C N
 * Date: 14 Oct 2014
 * License: GPLv2
 * Email: c.n.aananth@gmail.com
 *
 * Purpose: Contains definitions related to Freescale I.MX6Q
 * micro controller.
 */
#include "imx6x.h"
#include "crm_regs.h"

struct mxc_ccm_reg *imx_ccm = (struct mxc_ccm_reg *)CCM_BASE_ADDR;
u32 get_uart_clk(void)
{
        u32 reg, uart_podf;
        u32 freq = PLL3_80M;

        reg = __raw_readl(&imx_ccm->cscdr1);
#ifdef CONFIG_MX6SL            
        if (reg & MXC_CCM_CSCDR1_UART_CLK_SEL)
                freq = MXC_HCLK;
#endif
        reg &= MXC_CCM_CSCDR1_UART_CLK_PODF_MASK;
        uart_podf = reg >> MXC_CCM_CSCDR1_UART_CLK_PODF_OFFSET;

        return freq / (uart_podf + 1);
}


int soc_setup_n_go(int core)
{
	u32 *core_entry = (u32 *)ENTRY_VECTOR_CORE(core);
	u32 *core_argv = (u32 *)ENTRY_ARGREG_CORE(core);
	u32 src_scr;

	/* set up the entry points for 2nd core */
	extern int _start;
	*core_entry = (u32) &_start;
	*core_argv = 0x0;

	/* start the 2nd core */
	src_scr = __REG(SRC_SCR);
	src_scr |= (1 << (SRC_CORE1_BIT_OFFSET+core-1));
	__REG(SRC_SCR) = src_scr;

	return 0;
}
