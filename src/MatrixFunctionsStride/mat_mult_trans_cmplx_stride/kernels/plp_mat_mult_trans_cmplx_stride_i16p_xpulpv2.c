/* =====================================================================
 * Project:      PULP DSP Library
 * Title:        plp_mat_mult_trans_cmplx_stride_i16p_xpulpv2.c
 * Description:  parallel 16-bit integer complex strided matrix transpose matrix multiplication for
 * XPULPV2
 *
 * $Date:        18. July 2020
 * $Revision:    V0
 *
 * Target Processor: PULP cores
 * ===================================================================== */
/*
 * Copyright (C) 2020 ETH Zurich and Ubiversity of Bologna. All rights reserved.
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
  @ingroup MatMultTransCmplxStride
 */

/**
  @addtogroup MatMultTransCmplxStrideKernels
  @{
 */

/**
  @brief      parallel strided matrix transpose matrix multiplication for complex 16-bit integers on
              XpulpV2
  @param[in]  args    pointer to plp_mat_mat_mult_trans_cmplx_instance_i16 struct initialized by
                    plp_mat_mult_trans_cmplx_stride_i16_parallel
  @return     none

  @par Exploiting SIMD instructions
  The 16 bit values are packed two each into 32 bit vectors and then the two dot products are
  performed on 32 bit vectors, with 32 bit accumulator.
*/

void plp_mat_mult_trans_cmplx_stride_i16p_xpulpv2(void *args) {

    int core_id = rt_core_id();

    plp_mat_mult_cmplx_stride_instance_i16 *a = (plp_mat_mult_cmplx_stride_instance_i16 *)args;

    const int16_t *__restrict__ pSrcA = a->pSrcA;
    const int16_t *__restrict__ pSrcB = a->pSrcB;
    uint32_t M = a->M;
    uint32_t N = a->N;
    uint32_t O = a->O;
    uint32_t strideA = a->strideA;
    uint32_t strideB = a->strideB;
    uint32_t strideC = a->strideC;
    uint32_t nPE = a->nPE;
    int32_t *__restrict__ pDstC = a->pDstC;

#define BASIC_VERSION // if used don't forget to also use the undefine at end of file
#ifdef BASIC_VERSION

    for (int m = core_id; m < M; m += nPE) {
        for (int o = 0; o < O; o++) {
            int32_t sum_re = 0;
            int32_t sum_im = 0;
            for (int n = 0; n < N; n++) {
                int32_t a_re = (int32_t)pSrcA[(m * strideA + n) * 2 + 0];
                int32_t a_im = (int32_t)pSrcA[(m * strideA + n) * 2 + 1];
                int32_t b_re = (int32_t)pSrcB[(o * strideB + n) * 2 + 0];
                int32_t b_im = (int32_t)pSrcB[(o * strideB + n) * 2 + 1];
                sum_re += a_re * b_re - a_im * b_im;
                sum_im += a_re * b_im + a_im * b_re;
            }
            pDstC[(m * strideC + o) * 2 + 0] = sum_re;
            pDstC[(m * strideC + o) * 2 + 1] = sum_im;
        }
    }

#else

    // TODO: Hackathon

#endif
#undef BASIC_VERSION
}

/**
   @} end of MatMultTransCmplxStrideKernels group
*/
