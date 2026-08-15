/****************************************************************************
 * boards/arm/imxrt/imxrt1180-evk/src/imxrt_flexspi_nor_boot.c
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

#include "imxrt_flexspi_nor_boot.h"

/****************************************************************************
 * Private Data
 ****************************************************************************/

extern const uint8_t __container_image_offset[];
extern const uint8_t __container_image_size[];
extern const uint8_t __container_load_address[];
extern const uint8_t __container_entry[];

/****************************************************************************
 * Public Data
 ****************************************************************************/

locate_data(".boot_hdr.container")
const struct imxrt_boot_container_s g_boot_container =
{
  .header =
    {
      .version = IMXRT_CONTAINER_VERSION,
      .length = sizeof(struct imxrt_boot_container_s),
      .tag = IMXRT_CONTAINER_TAG,
      .flags = IMXRT_CONTAINER_FLAGS,
      .sw_version = IMXRT_CONTAINER_SW_VERSION,
      .fuse_version = IMXRT_CONTAINER_FUSE_VERSION,
      .image_count = IMXRT_CONTAINER_IMAGE_COUNT,
      .signature_block_offset =
        sizeof(struct imxrt_container_header_s) +
        sizeof(struct imxrt_container_image_s),
      .reserved = 0
    },
  .image =
    {
      {
        .offset = (uint32_t)(uintptr_t)__container_image_offset,
        .size = (uint32_t)(uintptr_t)__container_image_size,
        .load_address = (uint32_t)(uintptr_t)__container_load_address,
        .reserved1 = 0,
        .entry = (uint32_t)(uintptr_t)__container_entry,
        .reserved2 = 0,
        .flags = IMXRT_CONTAINER_IMAGE_FLAGS,
        .metadata = 0,
        .hash =
          {
            0
          },
        .iv =
          {
            0
          }
      }
    },
  .signature_block =
    {
      .version = IMXRT_SIGNATURE_BLOCK_VERSION,
      .length = sizeof(struct imxrt_signature_block_s),
      .tag = IMXRT_SIGNATURE_BLOCK_TAG,
      .certificate_offset = 0,
      .srk_table_offset = 0,
      .signature_offset = 0,
      .blob_offset = 0,
      .reserved = 0
    }
};

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/* None */
