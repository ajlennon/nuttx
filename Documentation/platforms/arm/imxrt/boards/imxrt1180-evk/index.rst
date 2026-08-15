====================
NXP i.MX RT1180 EVK
====================

The ``imxrt1180-evk:nsh`` configuration is an initial Cortex-M33 NSH port for
the MIMXRT1189.  It links the complete image into the 128 KiB CM33 DTCM at
``0x30000000`` and is intended for debugger loading.

Supported features
==================

* Cortex-M33 ARMv8-M build
* SysTick
* LPUART1 console on GPIO_AON_08 (TX) and GPIO_AON_09 (RX)
* NSH

The port does not yet contain a ROM-bootable FlexSPI image, TRDC programming,
or ELE startup integration.
