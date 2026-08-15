/****************************************************************************
 * arch/arm/src/imxrt/imxrt118x_clockconfig.c
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

#include <nuttx/config.h>

#include <arch/barriers.h>

#include "arm_internal.h"
#include "hardware/imxrt_memorymap.h"
#include "imxrt_clockconfig.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define IMXRT118X_CCM_ROOT_STRIDE       0x80u
#define IMXRT118X_CCM_LPCG_OFFSET       0x8000u
#define IMXRT118X_CCM_LPCG_STRIDE       0x40u
#define IMXRT118X_ROOT_LPUART0102       27u
#define IMXRT118X_LPCG_LPUART1          79u

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: imxrt_clockconfig
 *
 * Description:
 *   Configure the initial RT1180 clock roots used by NuttX.
 *
 ****************************************************************************/

void imxrt_clockconfig(void)
{
  uintptr_t root = IMXRT_CCM_BASE +
                   IMXRT118X_ROOT_LPUART0102 * IMXRT118X_CCM_ROOT_STRIDE;
  uintptr_t gate = IMXRT_CCM_BASE + IMXRT118X_CCM_LPCG_OFFSET +
                   IMXRT118X_LPCG_LPUART1 * IMXRT118X_CCM_LPCG_STRIDE;

  /* Use the always-available 24 MHz RC source (mux 0), divide by one, and
   * explicitly enable the LPUART1 LPCG.  A later bootable port can switch to
   * a PLL-derived root after ELE/TRDC initialization.
   */

  putreg32(0, root);
  putreg32(1, gate);
  UP_MB();
}
