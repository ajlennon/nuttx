/****************************************************************************
 * boards/arm/imxrt/imxrt1180-evk/scripts/flash-ramload.ld
 *
 * SPDX-License-Identifier: Apache-2.0
 ****************************************************************************/

MEMORY
{
  flash (rx)  : ORIGIN = 0x28000000, LENGTH = 16M
  itcm  (rwx) : ORIGIN = 0x0ffe0000, LENGTH = 128K
  ocram (rwx) : ORIGIN = 0x20480000, LENGTH = 512K
}

OUTPUT_ARCH(arm)
EXTERN(_vectors)
EXTERN(g_flash_config)
EXTERN(g_boot_container)
ENTRY(_stext)

SECTIONS
{
  /* RT1180 boot layout:
   *
   *   0x0400  FlexSPI configuration block
   *   0x0800  XMCD (unused for internal RAM)
   *   0x1000  AHAB-style container
   *   0xb000  CM33 image copied to ITCM by the Boot ROM
   */

  .boot_hdr :
  {
    FILL(0xff)
    . = 0x400;
    KEEP(*(.boot_hdr.conf))
    . = 0x800;
    KEEP(*(.boot_hdr.xmcd_data))
    . = 0x1000;
    KEEP(*(.boot_hdr.container))
    . = 0xb000;
  } > flash

  __flash_image_start = LOADADDR(.text);

  .text : ALIGN(4)
  {
    _stext = ABSOLUTE(.);
    KEEP(*(.vectors))
    *(.text .text.*)
    *(.rodata .rodata.*)
    *(.fixup)
    *(.gnu.warning)
    *(.gnu.linkonce.t.*)
    *(.gnu.linkonce.r.*)
    *(.glue_7)
    *(.glue_7t)
    *(.got)
    *(.gcc_except_table)
    _etext = ABSOLUTE(.);
  } > itcm AT > flash

  .init_section : ALIGN(4)
  {
    _sinit = ABSOLUTE(.);
    KEEP(*(.init_array .init_array.*))
    _einit = ABSOLUTE(.);
  } > itcm AT > flash

  .ARM.extab : ALIGN(4)
  {
    *(.ARM.extab*)
  } > itcm AT > flash

  .ARM.exidx : ALIGN(4)
  {
    __exidx_start = ABSOLUTE(.);
    *(.ARM.exidx*)
    __exidx_end = ABSOLUTE(.);
  } > itcm AT > flash

  _eronly = ABSOLUTE(.);

  .data : ALIGN(4)
  {
    _sdata = ABSOLUTE(.);
    *(.data .data.*)
    *(.gnu.linkonce.d.*)
    CONSTRUCTORS
    . = ALIGN(4);
    _edata = ABSOLUTE(.);
  } > ocram AT > flash

  .ramfunc : ALIGN(4)
  {
    _sramfuncs = ABSOLUTE(.);
    *(.ramfunc .ramfunc.*)
    _eramfuncs = ABSOLUTE(.);
  } > ocram AT > flash

  /* The ROM copies one contiguous payload into ITCM.  Startup then moves
   * initialized data and RAM functions from their ITCM staging addresses
   * into OCRAM.
   */

  _framfuncs = _eronly + (LOADADDR(.ramfunc) - LOADADDR(.data));

  .bss : ALIGN(4)
  {
    _sbss = ABSOLUTE(.);
    *(.bss .bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = ABSOLUTE(.);
  } > ocram

  __flash_image_end = LOADADDR(.ramfunc) + SIZEOF(.ramfunc);
  __container_image_offset =
    __flash_image_start - (ORIGIN(flash) + 0x1000);
  __container_image_size = __flash_image_end - __flash_image_start;
  __container_load_address = ORIGIN(itcm);
  __container_entry = __start;

  ASSERT(__container_image_offset == 0xa000,
         "RT1180 container payload must start at offset 0xa000")
  ASSERT(__container_image_size <= LENGTH(itcm),
         "RT1180 ROM RAM-load payload exceeds ITCM")
  ASSERT((LOADADDR(.data) - __flash_image_start) ==
         (_eronly - ORIGIN(itcm)),
         "RT1180 initialized-data staging is not contiguous")

  /DISCARD/ : { *(.note .note.*) }

  .stab 0 : { *(.stab) }
  .stabstr 0 : { *(.stabstr) }
  .comment 0 : { *(.comment) }
  .debug_abbrev 0 : { *(.debug_abbrev) }
  .debug_info 0 : { *(.debug_info) }
  .debug_line 0 : { *(.debug_line) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  .debug_aranges 0 : { *(.debug_aranges) }
}
