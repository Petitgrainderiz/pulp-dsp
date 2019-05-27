/* =====================================================================
 * Project:      PULP DSP Library
 * Title:        plp_dot_prod_int32_scalar.c
 * Description:  32-bit integer scalar dot product
 *
 * $Date:        16. May 2019
 * $Revision:    V0
 *
 * Target Processor: PULP cores
 * ===================================================================== */
/*
 * Copyright (C) 2019 Xiaying Wang, IIS, ETH Zurich. All rights reserved.
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
  @ingroup groupMath
 */

/**
  @defgroup BasicDotProd Vector Dot Product
  This module contains the glue code for Vector Dot Product. The kernel codes (kernels) are in the Moducle Vector Dot Product Kernels.

  The Vector Dot Product computes the dot product of two vectors.
  The vectors are multiplied element-by-element and then summed.
  <pre>
      sum = pSrcA[0]*pSrcB[0] + pSrcA[1]*pSrcB[1] + ... + pSrcA[blockSize-1]*pSrcB[blockSize-1]
  </pre>
  There are separate functions for floating-point, int8, int16, and int32 data types. For lower precision integers (int8, int16), functions exploiting SIMD instructions are provided.

  The naming of the functions follows the following pattern (for example plp_dot_prod_i32s):
  <pre>
      pulp _ function name _ data type precision method, with

      data type = {f, i, q} respectively for floats, integers, fixed points

      precision = {32, 16, 8} bits

      method = {s, v, p} meaning single (or scalar, i.e. not using packed SIMD), vectorized (i.e. using SIMD instructions), and parallel (for multicore parallel computing), respectively.

  </pre>


 */

/**
  @addtogroup BasicDotProd
  @{
 */

/**
  @brief Glue code for scalar dot product of 32-bit integer vectors.
  @param[in]  pSrcA      points to the first input vector
  @param[in]  pSrcB      points to the second input vector
  @param[in]  blockSize  number of samples in each vector
  @param[out] result     output result returned here
  @return        none
 */

void plp_dot_prod_i32s(
                         const int32_t * pSrcA,
                         const int32_t * pSrcB,
                         uint32_t blockSize,
                         int32_t * pRes) {
  
  if (rt_cluster_id() == ARCHI_FC_CID){
    plp_dot_prod_i32s_rv32im(pSrcA, pSrcB, blockSize, pRes);
  }
  else{
    plp_dot_prod_i32s_xpulpv2(pSrcA, pSrcB, blockSize, pRes);
  }
}

/**
  @} end of BasicDotProd group
 */

