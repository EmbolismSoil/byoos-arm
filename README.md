byoos-arm
=========

BYOOS -- Boot Your Own Operating Systems. Run your proprietary OS in one of your multi core platform running Linux.



Concept
-------

Reserve some memory space in either top of bottom of RAM. Load the "byoos.bin" into the rserved space. Use the "go" command of u-boot (or any other bootloader) to execute a setup function which is placed at 0x200 bytes offset from the start of memory. The setup function then configures one of the core, as configured in "byoos_config.h" in AMP mode and makes the core executing the byoos and the OS that is linked to this.

Example:
<pre>
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
</pre>


Key Goals
---------
Make the life of embedded engineers and companies (especially Automotive), simple and safe. Such companies and people had put several decades effort in delivering multiple safety critical products, with compleixities and requirements that are unique to Automotive products. Today, they are forced to follow a fast changing, less safe consumer electronics trend. This project SHALL help retaining the positives (past) of Automotive designs but also augment the benefits and contributions (present & future) from mobile and CE industry.


Status
------

The project is in concept stage, tested on Freescale I.MX6Q (ARM Cortex A9) based SabreAuto board. Features such as timers, entry points for proprietary OS, managing peripherals and shared memory between Linux and byoos are yet to be decided.



Suggestions, Critics are most welcome!


Thanks,
Aananth C N
