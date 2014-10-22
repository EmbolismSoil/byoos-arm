/*# 
 *# Author: Aananth C N
 *# Date: 09 Oct 2014 
 *# License: GPLv2
 *# Email: c.n.aananth@gmail.com
 *#
 *# Project: myos - An OS that will run on one of the multi-core processor
 *# Reference: Article written by Miro Samek and Balau in different web pages
 */

/*****************************************************************************
*# Defintions
*/

#define USR_MODE	0x10
#define FIQ_MODE	0x11
#define IRQ_MODE	0x12
#define SVC_MODE	0x13
#define ABT_MODE	0x17
#define UND_MODE	0x1b
#define SYS_MODE	0x1f
#define MODE_MASK	0x1f
#define T_BIT		0x20
#define F_BIT		0x40
#define I_BIT		0x80

#define IRQ_MODE_VAL 	(IRQ_MODE | I_BIT | F_BIT)
#define FIQ_MODE_VAL	(FIQ_MODE | I_BIT | F_BIT)	
#define SVC_MODE_VAL	(SVC_MODE | I_BIT | F_BIT)
#define ABT_MODE_VAL	(ABT_MODE | I_BIT | F_BIT)
#define UND_MODE_VAL	(UND_MODE | I_BIT | F_BIT)
#define SYS_MODE_VAL	(SYS_MODE | I_BIT | F_BIT)

#define STACK_FILL 0xBABABABA

/*****************************************************************************
* The startup code must be linked at the start of ROM, which is NOT
* necessarily address zero.
*/
.text
.section .reset
.code 32

.global _start
.func _start


_start:
	/* Vector table
	* NOTE: used only very briefly until RAM is remapped to address zero
	*/
	B _reset /* Reset: relative branch allows remap */
	B . /* Undefined Instruction */
	B . /* Software Interrupt */
	B . /* Prefetch Abort */
	B . /* Data Abort */
	B . /* Reserved */
	B . /* IRQ */
	B . /* FIQ */

	/* The copyright notice embedded prominently at the beginning of ROM */
	.string "Copyright (c) Aananth C N. All Rights Reserved."
	.align 4 /* re-align to the word boundary */


/***************************************************************************** 
* _reset 
*/
 _reset:

	/* Call the platform-specific low-level initialization routine
	 *
	 * NOTE: The ROM is typically NOT at its linked address before the remap,
	 * so the branch to low_level_init() must be relative (position
	 * independent code). The low_level_init() function must continue to
	 * execute in ARM state. Also, the function low_level_init() cannot rely
	 * on uninitialized data being cleared and cannot use any initialized
	 * data, because the .bss and .data sections have not been initialized yet.
	 */
	LDR r0,=_reset /* pass the reset address as the 1st argument */
	LDR r1,=_cstartup /* pass the return address as the 2nd argument */
	MOV lr,r1 /* set the return address after the remap */
	LDR sp,=__stack_end__ /* set the temporary stack pointer */
	B low_level_init /* relative branch enables remap */
	
	/* NOTE: after the return from low_level_init() the ROM is remapped
	 * to its linked address so the rest of the code executes at its linked
	 * address.
	 */


_cstartup:
	/* Relocate the .data section (copy from ROM to RAM) */
	LDR r0,=__data_load
	LDR r1,=__data_start
	LDR r2,=_edata
1:
	CMP r1,r2
	LDMLTIA r0!,{r3}
	STMLTIA r1!,{r3}
	BLT 1b

	/* Clear the .bss section (zero init) */
	LDR r1,=__bss_start__
	LDR r2,=__bss_end__
	MOV r3,#0
1:
	CMP r1,r2
	STMLTIA r1!,{r3}
	BLT 1b

	/* Fill the .stack section */
	LDR r1,=__stack_start__
	LDR r2,=__stack_end__
	LDR r3,=STACK_FILL
1: 
	CMP r2,r2
	STMLTIA r1!,{r3}
	BLT 1b

_stack_init:
	/* Initialize stack pointers for all ARM modes */
	MSR CPSR_c,#IRQ_MODE_VAL 
	LDR sp,=__irq_stack_top__ /* set the IRQ stack pointer */

	MSR CPSR_c,#FIQ_MODE_VAL
	LDR sp,=__fiq_stack_top__ /* set the FIQ stack pointer */

	MSR CPSR_c,#SVC_MODE_VAL
	LDR sp,=__svc_stack_top__ /* set the SVC stack pointer */

	MSR CPSR_c,#ABT_MODE_VAL
	LDR sp,=__abt_stack_top__ /* set the ABT stack pointer */

	MSR CPSR_c,#UND_MODE_VAL
	LDR sp,=__und_stack_top__ /* set the UND stack pointer */

	MSR CPSR_c,#SYS_MODE_VAL
	LDR sp,=__c_stack_top__ /* set the C stack pointer */

_enter_byoos:
	/* Enter the C/C++ code */
	LDR r12,=byoos_main
	MOV lr,pc /* set the return address */
	BX r12 /* the target code can be ARM or THUMB */

	SWI 0xFFFFFF /* cause exception if main() ever returns */

.size _start, . - _start
.endfunc
.end 
