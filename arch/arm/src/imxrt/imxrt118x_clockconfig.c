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
#include "hardware/imxrt_ccm.h"
#include "hardware/imxrt_lpuart.h"
#include "hardware/imxrt_memorymap.h"
#include "imxrt_clockconfig.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define IMXRT118X_ROOT_LPUART0102       27u
#define IMXRT118X_LPCG_LPUART1          79u

#define IMXRT118X_ROOT_MUX_OSCRC24M      0u
#define IMXRT118X_ROOT_MUX_OSCRC400M     1u
#define IMXRT118X_ROOT_MUX_SYSPLL3_DIV2  2u

#define IMXRT118X_OSCRC24M_FREQUENCY     24000000u
#define IMXRT118X_OSCRC400M_FREQUENCY    400000000u
#define IMXRT118X_SYSPLL3_DIV2_FREQUENCY 240000000u

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static void imxrt118x_set_root(unsigned int root, unsigned int mux,
                               unsigned int divider)
{
  uint32_t regval = CCM_ROOT_CONTROL_MUX(mux) |
                    CCM_ROOT_CONTROL_DIV(divider);

  putreg32(regval, IMXRT_CCM_ROOT_CONTROL(root));
  UP_MB();

  /* Complete the write before a consumer clock is enabled. */

  (void)getreg32(IMXRT_CCM_ROOT_CONTROL(root));
}

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
  /* Keep the proven RC source until the port owns the complete NXP
   * sequence: PMU PLL LDO, SYS_PLL3, and ELE/TRDC access.  Root and LPCG
   * programming are now separate so a later PLL switch cannot silently
   * desynchronise the UART baud calculation.
   */

  imxrt118x_set_root(IMXRT118X_ROOT_LPUART0102,
                     IMXRT118X_ROOT_MUX_OSCRC24M, 1);
  imxrt_clockall_lpuart1();
}

/****************************************************************************
 * Name: imxrt_clockall_lpuart1
 *
 * Description:
 *   Enable the LPUART1 low-power clock gate.
 *
 ****************************************************************************/

void imxrt_clockall_lpuart1(void)
{
  putreg32(CCM_LPCG_DIRECT_ON,
           IMXRT_CCM_LPCG_DIRECT(IMXRT118X_LPCG_LPUART1));
  UP_MB();

  /* Complete the write before accessing LPUART1. */

  (void)getreg32(IMXRT_CCM_LPCG_DIRECT(IMXRT118X_LPCG_LPUART1));
}

/****************************************************************************
 * Name: imxrt_get_lpuart_clock
 *
 * Description:
 *   Return the configured LPUART1 source frequency.
 *
 ****************************************************************************/

uint32_t imxrt_get_lpuart_clock(uint32_t base)
{
  uint32_t regval;
  uint32_t source;
  uint32_t divider;

  if (base != IMXRT_LPUART1_BASE)
    {
      return 0;
    }

  regval = getreg32(IMXRT_CCM_ROOT_CONTROL(IMXRT118X_ROOT_LPUART0102));
  divider = (regval & CCM_ROOT_CONTROL_DIV_MASK) + 1;

  switch ((regval & CCM_ROOT_CONTROL_MUX_MASK) >>
          CCM_ROOT_CONTROL_MUX_SHIFT)
    {
      case IMXRT118X_ROOT_MUX_OSCRC24M:
        source = IMXRT118X_OSCRC24M_FREQUENCY;
        break;

      case IMXRT118X_ROOT_MUX_OSCRC400M:
        source = IMXRT118X_OSCRC400M_FREQUENCY;
        break;

      case IMXRT118X_ROOT_MUX_SYSPLL3_DIV2:
        source = IMXRT118X_SYSPLL3_DIV2_FREQUENCY;
        break;

      default:
        return 0;
    }

  return source / divider;
}
