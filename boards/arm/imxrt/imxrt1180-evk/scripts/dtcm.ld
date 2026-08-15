/****************************************************************************
 * boards/arm/imxrt/imxrt1180-evk/scripts/dtcm.ld
 *
 * SPDX-License-Identifier: Apache-2.0
 ****************************************************************************/

MEMORY
{
  dtcm (rwx) : ORIGIN = 0x30000000, LENGTH = 128K
}

OUTPUT_ARCH(arm)
EXTERN(_vectors)
ENTRY(_stext)

SECTIONS
{
  .text :
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
  } > dtcm

  .init_section :
  {
    _sinit = ABSOLUTE(.);
    KEEP(*(.init_array .init_array.*))
    _einit = ABSOLUTE(.);
  } > dtcm

  .ARM.extab : { *(.ARM.extab*) } > dtcm
  .ARM.exidx :
  {
    __exidx_start = ABSOLUTE(.);
    *(.ARM.exidx*)
    __exidx_end = ABSOLUTE(.);
  } > dtcm

  _eronly = ABSOLUTE(.);

  .data :
  {
    _sdata = ABSOLUTE(.);
    *(.data .data.*)
    *(.gnu.linkonce.d.*)
    CONSTRUCTORS
    . = ALIGN(4);
    _edata = ABSOLUTE(.);
  } > dtcm

  .ramfunc ALIGN(4) :
  {
    _sramfuncs = ABSOLUTE(.);
    *(.ramfunc .ramfunc.*)
    _eramfuncs = ABSOLUTE(.);
  } > dtcm
  _framfuncs = LOADADDR(.ramfunc);

  .bss :
  {
    _sbss = ABSOLUTE(.);
    *(.bss .bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = ABSOLUTE(.);
  } > dtcm

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
