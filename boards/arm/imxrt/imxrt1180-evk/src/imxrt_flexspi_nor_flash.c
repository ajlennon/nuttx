/****************************************************************************
 * boards/arm/imxrt/imxrt1180-evk/src/imxrt_flexspi_nor_flash.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/compiler.h>

#include "imxrt_flexspi_nor_flash.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define FLASH_DUMMY_CYCLES 6

/****************************************************************************
 * Public Data
 ****************************************************************************/

locate_data(".boot_hdr.conf")
const struct flexspi_nor_config_s g_flash_config =
{
  .memory_config =
    {
      .tag = FLEXSPI_CFG_BLK_TAG,
      .version = FLEXSPI_CFG_BLK_VERSION,
      .read_sample_clock_source = FLASH_READ_SAMPLE_CLK_DQSPAD,
      .chip_select_hold_time = 3,
      .chip_select_setup_time = 3,
      .controller_misc_option = 0x10,
      .device_type = FLEXSPI_DEVICE_SERIAL_NOR,
      .serial_flash_pad_type = SERIAL_FLASH_4PADS,
      .serial_clock_frequency = FLEXSPI_SERIAL_CLK_133MHZ,
      .serial_flash_a1_size = 16 * 1024 * 1024,
      .config_mode_type =
        {
          DEVICE_CONFIG_CMD_GENERIC
        },
      .lookup_table =
        {
          [0] = FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0xeb,
                                RADDR_SDR, FLEXSPI_4PAD, 0x18),
          [1] = FLEXSPI_LUT_SEQ(DUMMY_SDR, FLEXSPI_4PAD,
                                FLASH_DUMMY_CYCLES,
                                READ_SDR, FLEXSPI_4PAD, 0x04),
          [4] = FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0x05,
                                READ_SDR, FLEXSPI_1PAD, 0x04),
          [12] = FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0x06,
                                 STOP, FLEXSPI_1PAD, 0),
          [20] = FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0x20,
                                 RADDR_SDR, FLEXSPI_1PAD, 0x18),
          [32] = FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0xd8,
                                 RADDR_SDR, FLEXSPI_1PAD, 0x18),
          [36] = FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0x02,
                                 RADDR_SDR, FLEXSPI_1PAD, 0x18),
          [37] = FLEXSPI_LUT_SEQ(WRITE_SDR, FLEXSPI_1PAD, 0x04,
                                 STOP, FLEXSPI_1PAD, 0),
          [44] = FLEXSPI_LUT_SEQ(CMD_SDR, FLEXSPI_1PAD, 0x60,
                                 STOP, FLEXSPI_1PAD, 0)
        }
    },
  .page_size = 256,
  .sector_size = 4 * 1024,
  .ip_command_serial_clock_frequency = 1,
  .uniform_block_size = 0,
  .block_size = 64 * 1024
};

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/* None */
