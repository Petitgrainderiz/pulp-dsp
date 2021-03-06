/* =====================================================================
 * Project:      PULP DSP Library
 * Title:        plp_mat_sub_stride_i16p_xpulpv2.c
 * Description:  parallel 16-bit integer strided matrix subtraction for XPULPV2
 *
 * $Date:        1. July 2020
 * $Revision:    V0
 *
 * Target Processor: PULP cores
 * ===================================================================== */
/*
 * Copyright (C) 2020 ETH Zurich and University of Bologna.
 *
 * Author: Tibor Schneider, ETH Zurich
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "plp_math.h"

/**
  @ingroup MatSubStride
 */

/**
  @addtogroup MatSubStrideKernels
  @{
 */

/**
  @brief Parallel strided matrix subtraction of 16-bit integer matrices kernel for XPULPV2
  extension.
  @param[in]  args      pointer to plp_mat_sub_stride_instance_i16 struct initialized by
  plp_mat_sub_stride_i16_parallel
  @return     none

  @par Exploiting SIMD instructions
  The 16 bit values are packed two each into 32 bit vectors and then the two dot products are
  performed on 32 bit vectors, with 32 bit accumulator.
*/

void plp_mat_sub_stride_i16p_xpulpv2(void *args) {

    int core_id = rt_core_id();

    plp_mat_sub_stride_instance_i16 *a = (plp_mat_sub_stride_instance_i16 *)args;

    const int16_t *__restrict__ pSrcA = a->pSrcA;
    const int16_t *__restrict__ pSrcB = a->pSrcB;
    uint32_t M = a->M;
    uint32_t N = a->N;
    uint32_t strideA = a->strideA;
    uint32_t strideB = a->strideB;
    uint32_t strideY = a->strideY;
    uint32_t nPE = a->nPE;
    int16_t *__restrict__ pDst = a->pDst;

#define BASIC_VERSION // if used don't forget to also use the undefine at end of file
#ifdef BASIC_VERSION

    uint32_t m, n; // loop counters

    for (m = core_id; m < M; m += nPE) {
        for (n = 0; n < N; n++) {
            pDst[m * strideY + n] = pSrcA[m * strideA + n] - pSrcB[m * strideB + n];
        }
    }

#else

    // TODO: Hackathon

#endif
#undef BASIC_VERSION
}

/**
   @} end of MatSubStrideKernels group
*/
