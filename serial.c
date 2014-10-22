/*
 * (c) 2007 Sascha Hauer <s.hauer@pengutronix.de>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

/* 
 * Modified by: Aananth C N
 * Project: BYOOS - Boot Your Own Operating Systems
 */
#include "errno.h"
#include "byoos_config.h"
#include "byoos.h"
#include "serial.h"


#ifndef CONFIG_MXC_UART_BASE
#error "define CONFIG_MXC_UART_BASE to use the MXC UART driver"
#endif

#define UART_PHYS	CONFIG_MXC_UART_BASE

static void serial_setbrg(void)
{
	u32 clk = get_uart_clk();

	__REG(UART_PHYS + UFCR) = 4 << 7; /* divide input clock by 2 */
	__REG(UART_PHYS + UBIR) = 0xf;
	__REG(UART_PHYS + UBMR) = clk / (2 * CONFIG_BAUDRATE);

}

int serial_getc(void)
{
	while (__REG(UART_PHYS + UTS) & UTS_RXEMPTY)
		WATCHDOG_RESET();
	return (__REG(UART_PHYS + URXD) & URXD_RX_DATA); /* mask out status from upper word */
}

void serial_putc(const char c)
{
	__REG(UART_PHYS + UTXD) = c;

	/* wait for transmitter to be ready */
	while (!(__REG(UART_PHYS + UTS) & UTS_TXEMPTY))
		WATCHDOG_RESET();

	/* If \n, also do \r */
	if (c == '\n')
		serial_putc ('\r');
}

/*
 * Test whether a character is in the RX buffer
 */
int serial_tstc(void)
{
	/* If receive fifo is empty, return false */
	if (__REG(UART_PHYS + UTS) & UTS_RXEMPTY)
		return 0;
	return 1;
}

/*
 * Initialise the serial port with the given baudrate. The settings
 * are always 8 data bits, no parity, 1 stop bit, no start bits.
 *
 */
int serial_init(void)
{
	__REG(UART_PHYS + UCR1) = 0x0;
	__REG(UART_PHYS + UCR2) = 0x0;

	while (!(__REG(UART_PHYS + UCR2) & UCR2_SRST));

	__REG(UART_PHYS + UCR3) = 0x0704;
	__REG(UART_PHYS + UCR4) = 0x8000;
	__REG(UART_PHYS + UESC) = 0x002b;
	__REG(UART_PHYS + UTIM) = 0x0;

	__REG(UART_PHYS + UTS) = 0x0;

	serial_setbrg();

	__REG(UART_PHYS + UCR2) = UCR2_WS | UCR2_IRTS | UCR2_RXEN | UCR2_TXEN
		| UCR2_SRST;

	__REG(UART_PHYS + UCR1) = UCR1_UARTEN;

	return 0;
}

#if 0
static struct serial_device serial_drv = {
	.name	= "mxc_serial",
	.start	= serial_init,
	.stop	= NULL,
	.setbrg	= serial_setbrg,
	.putc	= serial_putc,
	.puts	= default_serial_puts,
	.getc	= serial_getc,
	.tstc	= serial_tstc,
};

void serial_initialize(void)
{
	serial_register(&serial_drv);
}

__weak struct serial_device *default_serial_console(void)
{
	return &serial_drv;
}
#endif
