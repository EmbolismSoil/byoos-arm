byoos-arm
=========

BYOOS -- Boot Your Own Operating Systems. Run your proprietary OS in one of your multi core platform running Linux.



Concept
=======

Reserve some memory space in either top of bottom of RAM. Load the "byoos.bin" into the rserved space. Use the "go" command of u-boot (or any other bootloader) to execute a setup function which is placed at 0x200 bytes offset from the start of memory. The setup function then configures one of the core, as configured in "byoos_config.h" in AMP mode and makes the core executing the byoos and the OS that is linked to this.


Key Goals
=========
Make the life of embedded engineers and companies, especially Automotive, simple. They had put several decades effort in delivering multiple productlines, with compleixities and requirements that are unique to Automotive products especially "Safety". Today they are forced to follow a fast changing, less safe consumer electronics trend. This project SHALL help retaining the positives of Automotive but also augment the benefits and contributions from mobile and CE industry.


Status
------

The project is in concept stage, tested on Freescale I.MX6Q (ARM Cortex A9) based SabreAuto board. Features such as timers, entry points for proprietary OS, managing peripherals and shared memory between Linux and byoos are yet to be decided.



Suggestions, Critics are most welcome!


Thanks,
Aananth C N
