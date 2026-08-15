/****************************************************************************
 * arch/arm/src/imxrt/hardware/rt118x/imxrt118x_ccm.h
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

#ifndef __ARCH_ARM_SRC_IMXRT_HARDWARE_RT118X_IMXRT118X_CCM_H
#define __ARCH_ARM_SRC_IMXRT_HARDWARE_RT118X_IMXRT118X_CCM_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include "hardware/imxrt_memorymap.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* CCM clock roots */

#define IMXRT_CCM_ROOT_STRIDE            0x80u
#define IMXRT_CCM_ROOT_CONTROL(n)        (IMXRT_CCM_BASE + \
                                          (n) * IMXRT_CCM_ROOT_STRIDE)
#define IMXRT_CCM_ROOT_STATUS0(n)        (IMXRT_CCM_ROOT_CONTROL(n) + 0x20u)

#define CCM_ROOT_CONTROL_DIV_MASK        0xffu
#define CCM_ROOT_CONTROL_DIV(n)          (((n) - 1u) & \
                                          CCM_ROOT_CONTROL_DIV_MASK)
#define CCM_ROOT_CONTROL_MUX_SHIFT       8
#define CCM_ROOT_CONTROL_MUX_MASK        (3u << CCM_ROOT_CONTROL_MUX_SHIFT)
#define CCM_ROOT_CONTROL_MUX(n)          (((n) << \
                                          CCM_ROOT_CONTROL_MUX_SHIFT) & \
                                          CCM_ROOT_CONTROL_MUX_MASK)
#define CCM_ROOT_CONTROL_OFF             (1u << 24)

/* CCM low-power clock gates */

#define IMXRT_CCM_LPCG_OFFSET            0x8000u
#define IMXRT_CCM_LPCG_STRIDE            0x40u
#define IMXRT_CCM_LPCG_DIRECT(n)         (IMXRT_CCM_BASE + \
                                          IMXRT_CCM_LPCG_OFFSET + \
                                          (n) * IMXRT_CCM_LPCG_STRIDE)
#define IMXRT_CCM_LPCG_STATUS0(n)        (IMXRT_CCM_LPCG_DIRECT(n) + 0x20u)

#define CCM_LPCG_DIRECT_ON               (1u << 0)
#define CCM_LPCG_STATUS0_ON              (1u << 0)

#endif /* __ARCH_ARM_SRC_IMXRT_HARDWARE_RT118X_IMXRT118X_CCM_H */
