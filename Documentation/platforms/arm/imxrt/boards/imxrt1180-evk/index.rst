====================
NXP i.MX RT1180 EVK
====================

The ``imxrt1180-evk:nsh`` configuration is an initial Cortex-M33 NSH port for
the MIMXRT1189.  It links executable code into the 128 KiB secure CM33 ITCM
at ``0x0ffe0000`` and writable state into secure OCRAM at ``0x20480000``.
It is intended for debugger loading.

The ``imxrt1180-evk:nsh-flash`` configuration adds a FlexSPI NOR
configuration block and RT1180 container header.  The Boot ROM reads the
image from external flash, copies the payload into the same ITCM layout, and
jumps to the NuttX reset entry.  This is a ROM RAM-load image, not
execute-in-place.

Supported features
==================

* Cortex-M33 ARMv8-M build
* SysTick
* LPUART1 console on GPIO_AON_08 (TX) and GPIO_AON_09 (RX)
* NSH
* FlexSPI NOR ROM RAM-load image generation

The debugger-loaded ``nsh`` configuration has been tested on the EVK.  The
``nsh-flash`` image builds, but still requires external-flash programming and
power-on-reset validation.  TRDC programming and ELE startup integration are
not yet included.
