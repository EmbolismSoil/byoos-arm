byoos-arm
=========

BYOOS -- Boot Your Own Operating Systems. Run your proprietary OS in one of your multi core platform running Linux.


How to build
------------
1. git clone "this project" 
2. cd byoos-arm
3. make (Note: you may need to install arm-none-eabi- toolchain. For Ubuntu: sudo apt-get install gcc-arm-none-eabi)
4. You will find "byoos.bin"


How to test (Freescale SabreAuto Board)
-----------
1. Modify the PHYS_SDRAM_SIZE value such that you reserve some memory space as described in "Concept" section below.
2. Modify the kernel dts file to allot only 3 cpus or disable SMP.
2. Rebuild u-boot, kernel and update sdcard image.
3. Copy the byoos.bin into the fat partition of sdcard
4. Turn on Sabreauto, stop the execution of u-boot by typing any key with in the "bootdelay" time.
5. Type command "go 0x8f800200". When this command returns, byoos.bin will be active on Core 3
6. Then type "run bootcmd". Linux will be up on other core(s).


Concept
=======

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
               |   BYOOS: 8MB for core 3    |   |                      |  
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
