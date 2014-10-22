/*
 * Author: Aananth C N
 * Date: 16 Oct 2014
 * License: GPLv2
 * Email: c.n.aananth@gmail.com
 *
 * Purpose: This file contains all definitions that are required to support the
 * debug requirements for BYOOS (Boot Your Own Operating System)
 */
OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm") /* I.MX supports little only */
OUTPUT_ARCH(arm)
ENTRY(_start)


/********************************************************************************************* 
  M E M O R Y L A Y O U T   -   B O O T   Y O U R   O W N   O P E R A T I N G   S Y S T E M
**********************************************************************************************

SabreaAuto Board RAM layout:                    +----------------------+
~~~~~~~~~~~~~~~~~~~~~~~~~~~~                   /|                      |
                                              / |                      |
                                             /  | MOM: 6MB frame buff. |
 0x8FFF_FFFF:  +----------------------------+   |                      |
               |    MYOS: 8MB for core 3    |   |                      |
 0x8F80_0000:  +----------------------------+   +----------------------+
               |                            |\  | RAM: 1MB .data, .bss |
               |                            | \ +----------------------+
               |                            |  \| ROM: 1MB .text       |
               |                            |   +----------------------+
               | LINUX: 1.99 GB (2GB-8MB)   |
               | for cores 0, 1 and 2       |
               |                            |
               |                            |
               |                            |
               |                            |
               |                            |
 0x1000_0000:  +----------------------------+

*********************************************************************************************/
MEMORY {
	ROM (rx)  : ORIGIN = 0x8F800000, LENGTH = 1024k /* Program Memory 		*/
	RAM (rwx) : ORIGIN = 0x8F900000, LENGTH = 1024k /* Read Write Memory 		*/
	MOM (rwx) : ORIGIN = 0x8FA00000, LENGTH = 6144k /* Multi Operations Memory 	*/
}

/* The size of the single stack used by the application */
C_STACK_SIZE = 512;
IRQ_STACK_SIZE = 0;
FIQ_STACK_SIZE = 0;
SVC_STACK_SIZE = 512;
ABT_STACK_SIZE = 0;
UND_STACK_SIZE = 0;


SECTIONS {
	.reset : {
		*startup.o (.reset) /* startup code (ARM vectors and reset handler) */
		. = ALIGN(0x200); 
	} >ROM

	.setup : {
		/* this section will place the entry function which initializes the
		   secondary core for myos */
	} >ROM

	.ramvect : { /* used for vectors remapped to RAM */
		__ram_start = .;
		. = 0x40;
	} >RAM


	.text : {/* used for code and read-only data executed from ROM in place */
		CREATE_OBJECT_SYMBOLS
		*(.text .text.* .gnu.linkonce.t.*)
		*(.gnu.warning)
		*(.glue_7t) *(.glue_7) /* Required for thumb-interwork to work */

		. = ALIGN(0x4);

		*(.rodata .rodata.* .gnu.linkonce.r.*)

	} >ROM

	/* 
	 * .ARM.exidx is the section containing information for unwinding the stack. 
	 * If your C program has functions that print out a stack backtrace, the functions 
         * will likely depend on this section being present.
	 *
	 * .ARM.exidx is sorted, so has to go in its own output section. 
	 */
	.ARM.exidx : {
		__exidx_start = .;
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
		__exidx_end = .;
	} >ROM
	_etext = .;

	.data : { /* used for initialized data */
		__data_load = LOADADDR (.data);
		__data_start = .;
		*(.shdata)
		*(.data .data.* .gnu.linkonce.d.*)
		. = ALIGN (4);
		_edata = .;
	} >RAM AT>ROM

	.bss : {
		__bss_start__ = . ;
		*(.shbss)
		*(.bss .bss.* .gnu.linkonce.b.*)
		*(COMMON)
		. = ALIGN (4); 
		 __bss_end__ = .;
	} >RAM

	.stack : {
		__stack_start__ = . ;
		. += IRQ_STACK_SIZE;
		. = ALIGN (4);
		__irq_stack_top__ = . ;
		. += FIQ_STACK_SIZE;
		. = ALIGN (4);
		__fiq_stack_top__ = . ;
		. += SVC_STACK_SIZE;
		. = ALIGN (4);
		__svc_stack_top__ = . ;
		. += ABT_STACK_SIZE;
		. = ALIGN (4);
		__abt_stack_top__ = . ;
		. += UND_STACK_SIZE;
		. = ALIGN (4);
		__und_stack_top__ = . ;
		. += C_STACK_SIZE;
		. = ALIGN (4);
		__c_stack_top__ = . ;
		__stack_end__ = .;
	} >RAM

	_end = .;
	__end = _end;
	PROVIDE(end = .);

 
	.stab 0 (NOLOAD) : {
		*(.stab)
	}

	.stabstr 0 (NOLOAD) : {
		*(.stabstr)
	}

	/* DWARF debug sections.
	* Symbols in the DWARF debugging sections are relative to the beginning
	* of the section so we begin them at 0.
	*/
	/* DWARF 1 */
	.debug 0 : { *(.debug) }
	.line 0 : { *(.line) }
	/*. . . commented by Aananth */
} 
