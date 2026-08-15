# ##############################################################################
# boards/arm/imxrt/imxrt1180-evk/src/CMakeLists.txt
#
# SPDX-License-Identifier: Apache-2.0
# ##############################################################################

target_sources(board PRIVATE imxrt_boot.c imxrt_bringup.c imxrt_clockconfig.c
                             imxrt_gpio.c)

if(CONFIG_IMXRT1180_EVK_ROM_RAMLOAD)
  target_sources(board PRIVATE imxrt_flexspi_nor_boot.c
                               imxrt_flexspi_nor_flash.c)
  set_property(GLOBAL PROPERTY LD_SCRIPT
                               "${NUTTX_BOARD_DIR}/scripts/flash-ramload.ld")
else()
  set_property(GLOBAL PROPERTY LD_SCRIPT "${NUTTX_BOARD_DIR}/scripts/dtcm.ld")
endif()
