/*===---- arm_mve.h - ARM MVE intrinsics (hybrid implementation) -----------===
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *===-----------------------------------------------------------------------===
 *
 * This header file uses the implementations of MVE intrinsics in open-source
 * LLVM, where they exist. For intrinsics not yet defined in LLVM, the Arm
 * Compiler preliminary implementation is used instead.
 *
 *===-----------------------------------------------------------------------===
 */

#ifndef __ARM_MVE_H
#define __ARM_MVE_H

#if !__ARM_FEATURE_MVE
#error "MVE support not enabled"
#endif

#undef __ARM_MVE_H
#include <arm_mve_upstream.h>

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

static __attribute__((__always_inline__))
float16x8_t __arm_vabsq_f16(float16x8_t __p0)
{
    return __builtin_mve_vabsq_f16(__p0);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vabsq_f32(float32x4_t __p0)
{
    return __builtin_mve_vabsq_f32(__p0);
}

static __attribute__((__always_inline__))
float16x8_t __arm_vabsq_m_f16(float16x8_t __p0, float16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vabsq_m_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vabsq_m_f32(float32x4_t __p0, float32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vabsq_m_f32(__p0, __p1, __p2);
}

#endif /* MVE floating point */

static __attribute__((__always_inline__))
int16x8_t __arm_vabsq_m_s16(int16x8_t __p0, int16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vabsq_m_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vabsq_m_s32(int32x4_t __p0, int32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vabsq_m_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vabsq_m_s8(int8x16_t __p0, int8x16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vabsq_m_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vabsq_s16(int16x8_t __p0)
{
    return __builtin_mve_vabsq_s16(__p0);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vabsq_s32(int32x4_t __p0)
{
    return __builtin_mve_vabsq_s32(__p0);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vabsq_s8(int8x16_t __p0)
{
    return __builtin_mve_vabsq_s8(__p0);
}

static __attribute__((__always_inline__))
int64_t __arm_vaddlvaq_p_s32(int64_t __p0, int32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vaddlvaq_p_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint64_t __arm_vaddlvaq_p_u32(uint64_t __p0, uint32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vaddlvaq_p_u32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int64_t __arm_vaddlvaq_s32(int64_t __p0, int32x4_t __p1)
{
    return __builtin_mve_vaddlvaq_s32(__p0, __p1);
}

static __attribute__((__always_inline__))
uint64_t __arm_vaddlvaq_u32(uint64_t __p0, uint32x4_t __p1)
{
    return __builtin_mve_vaddlvaq_u32(__p0, __p1);
}

static __attribute__((__always_inline__))
int64_t __arm_vaddlvq_p_s32(int32x4_t __p0, mve_pred16_t __p1)
{
    return __builtin_mve_vaddlvq_p_s32(__p0, __p1);
}

static __attribute__((__always_inline__))
uint64_t __arm_vaddlvq_p_u32(uint32x4_t __p0, mve_pred16_t __p1)
{
    return __builtin_mve_vaddlvq_p_u32(__p0, __p1);
}

static __attribute__((__always_inline__))
int64_t __arm_vaddlvq_s32(int32x4_t __p0)
{
    return __builtin_mve_vaddlvq_s32(__p0);
}

static __attribute__((__always_inline__))
uint64_t __arm_vaddlvq_u32(uint32x4_t __p0)
{
    return __builtin_mve_vaddlvq_u32(__p0);
}

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

static __attribute__((__always_inline__))
float16x8_t __arm_vaddq_m_n_f16(float16x8_t __p0, float16x8_t __p1, float16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vaddq_m_n_f16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vaddq_m_n_f32(float32x4_t __p0, float32x4_t __p1, float32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vaddq_m_n_f32(__p0, __p1, __p2, __p3);
}

#endif /* MVE floating point */

static __attribute__((__always_inline__))
int16x8_t __arm_vaddq_m_n_s16(int16x8_t __p0, int16x8_t __p1, int16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vaddq_m_n_s16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vaddq_m_n_s32(int32x4_t __p0, int32x4_t __p1, int32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vaddq_m_n_s32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vaddq_m_n_s8(int8x16_t __p0, int8x16_t __p1, int8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vaddq_m_n_s8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vaddq_m_n_u16(uint16x8_t __p0, uint16x8_t __p1, uint16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vaddq_m_n_u16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vaddq_m_n_u32(uint32x4_t __p0, uint32x4_t __p1, uint32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vaddq_m_n_u32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vaddq_m_n_u8(uint8x16_t __p0, uint8x16_t __p1, uint8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vaddq_m_n_u8(__p0, __p1, __p2, __p3);
}

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

static __attribute__((__always_inline__))
float16x8_t __arm_vaddq_n_f16(float16x8_t __p0, float16_t __p1)
{
    return __builtin_mve_vaddq_n_f16(__p0, __p1);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vaddq_n_f32(float32x4_t __p0, float32_t __p1)
{
    return __builtin_mve_vaddq_n_f32(__p0, __p1);
}

#endif /* MVE floating point */

static __attribute__((__always_inline__))
int16x8_t __arm_vaddq_n_s16(int16x8_t __p0, int16_t __p1)
{
    return __builtin_mve_vaddq_n_s16(__p0, __p1);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vaddq_n_s32(int32x4_t __p0, int32_t __p1)
{
    return __builtin_mve_vaddq_n_s32(__p0, __p1);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vaddq_n_s8(int8x16_t __p0, int8_t __p1)
{
    return __builtin_mve_vaddq_n_s8(__p0, __p1);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vaddq_n_u16(uint16x8_t __p0, uint16_t __p1)
{
    return __builtin_mve_vaddq_n_u16(__p0, __p1);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vaddq_n_u32(uint32x4_t __p0, uint32_t __p1)
{
    return __builtin_mve_vaddq_n_u32(__p0, __p1);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vaddq_n_u8(uint8x16_t __p0, uint8_t __p1)
{
    return __builtin_mve_vaddq_n_u8(__p0, __p1);
}

static __attribute__((__always_inline__))
int32_t __arm_vaddvaq_p_s16(int32_t __p0, int16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vaddvaq_p_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32_t __arm_vaddvaq_p_s32(int32_t __p0, int32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vaddvaq_p_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32_t __arm_vaddvaq_p_s8(int32_t __p0, int8x16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vaddvaq_p_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint32_t __arm_vaddvaq_p_u16(uint32_t __p0, uint16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vaddvaq_p_u16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint32_t __arm_vaddvaq_p_u32(uint32_t __p0, uint32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vaddvaq_p_u32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint32_t __arm_vaddvaq_p_u8(uint32_t __p0, uint8x16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vaddvaq_p_u8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32_t __arm_vaddvaq_s16(int32_t __p0, int16x8_t __p1)
{
    return __builtin_mve_vaddvaq_s16(__p0, __p1);
}

static __attribute__((__always_inline__))
int32_t __arm_vaddvaq_s32(int32_t __p0, int32x4_t __p1)
{
    return __builtin_mve_vaddvaq_s32(__p0, __p1);
}

static __attribute__((__always_inline__))
int32_t __arm_vaddvaq_s8(int32_t __p0, int8x16_t __p1)
{
    return __builtin_mve_vaddvaq_s8(__p0, __p1);
}

static __attribute__((__always_inline__))
uint32_t __arm_vaddvaq_u16(uint32_t __p0, uint16x8_t __p1)
{
    return __builtin_mve_vaddvaq_u16(__p0, __p1);
}

static __attribute__((__always_inline__))
uint32_t __arm_vaddvaq_u32(uint32_t __p0, uint32x4_t __p1)
{
    return __builtin_mve_vaddvaq_u32(__p0, __p1);
}

static __attribute__((__always_inline__))
uint32_t __arm_vaddvaq_u8(uint32_t __p0, uint8x16_t __p1)
{
    return __builtin_mve_vaddvaq_u8(__p0, __p1);
}

static __attribute__((__always_inline__))
int32_t __arm_vaddvq_p_s16(int16x8_t __p0, mve_pred16_t __p1)
{
    return __builtin_mve_vaddvq_p_s16(__p0, __p1);
}

static __attribute__((__always_inline__))
int32_t __arm_vaddvq_p_s32(int32x4_t __p0, mve_pred16_t __p1)
{
    return __builtin_mve_vaddvq_p_s32(__p0, __p1);
}

static __attribute__((__always_inline__))
int32_t __arm_vaddvq_p_s8(int8x16_t __p0, mve_pred16_t __p1)
{
    return __builtin_mve_vaddvq_p_s8(__p0, __p1);
}

static __attribute__((__always_inline__))
uint32_t __arm_vaddvq_p_u16(uint16x8_t __p0, mve_pred16_t __p1)
{
    return __builtin_mve_vaddvq_p_u16(__p0, __p1);
}

static __attribute__((__always_inline__))
uint32_t __arm_vaddvq_p_u32(uint32x4_t __p0, mve_pred16_t __p1)
{
    return __builtin_mve_vaddvq_p_u32(__p0, __p1);
}

static __attribute__((__always_inline__))
uint32_t __arm_vaddvq_p_u8(uint8x16_t __p0, mve_pred16_t __p1)
{
    return __builtin_mve_vaddvq_p_u8(__p0, __p1);
}

static __attribute__((__always_inline__))
int32_t __arm_vaddvq_s16(int16x8_t __p0)
{
    return __builtin_mve_vaddvq_s16(__p0);
}

static __attribute__((__always_inline__))
int32_t __arm_vaddvq_s32(int32x4_t __p0)
{
    return __builtin_mve_vaddvq_s32(__p0);
}

static __attribute__((__always_inline__))
int32_t __arm_vaddvq_s8(int8x16_t __p0)
{
    return __builtin_mve_vaddvq_s8(__p0);
}

static __attribute__((__always_inline__))
uint32_t __arm_vaddvq_u16(uint16x8_t __p0)
{
    return __builtin_mve_vaddvq_u16(__p0);
}

static __attribute__((__always_inline__))
uint32_t __arm_vaddvq_u32(uint32x4_t __p0)
{
    return __builtin_mve_vaddvq_u32(__p0);
}

static __attribute__((__always_inline__))
uint32_t __arm_vaddvq_u8(uint8x16_t __p0)
{
    return __builtin_mve_vaddvq_u8(__p0);
}

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

static __attribute__((__always_inline__))
float16x8_t __arm_vbrsrq_m_n_f16(float16x8_t __p0, float16x8_t __p1, int32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vbrsrq_m_n_f16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vbrsrq_m_n_f32(float32x4_t __p0, float32x4_t __p1, int32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vbrsrq_m_n_f32(__p0, __p1, __p2, __p3);
}

#endif /* MVE floating point */

static __attribute__((__always_inline__))
int16x8_t __arm_vbrsrq_m_n_s16(int16x8_t __p0, int16x8_t __p1, int32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vbrsrq_m_n_s16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vbrsrq_m_n_s32(int32x4_t __p0, int32x4_t __p1, int32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vbrsrq_m_n_s32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vbrsrq_m_n_s8(int8x16_t __p0, int8x16_t __p1, int32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vbrsrq_m_n_s8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vbrsrq_m_n_u16(uint16x8_t __p0, uint16x8_t __p1, int32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vbrsrq_m_n_u16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vbrsrq_m_n_u32(uint32x4_t __p0, uint32x4_t __p1, int32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vbrsrq_m_n_u32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vbrsrq_m_n_u8(uint8x16_t __p0, uint8x16_t __p1, int32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vbrsrq_m_n_u8(__p0, __p1, __p2, __p3);
}

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

static __attribute__((__always_inline__))
float16x8_t __arm_vbrsrq_n_f16(float16x8_t __p0, int32_t __p1)
{
    return __builtin_mve_vbrsrq_n_f16(__p0, __p1);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vbrsrq_n_f32(float32x4_t __p0, int32_t __p1)
{
    return __builtin_mve_vbrsrq_n_f32(__p0, __p1);
}

#endif /* MVE floating point */

static __attribute__((__always_inline__))
int16x8_t __arm_vbrsrq_n_s16(int16x8_t __p0, int32_t __p1)
{
    return __builtin_mve_vbrsrq_n_s16(__p0, __p1);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vbrsrq_n_s32(int32x4_t __p0, int32_t __p1)
{
    return __builtin_mve_vbrsrq_n_s32(__p0, __p1);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vbrsrq_n_s8(int8x16_t __p0, int32_t __p1)
{
    return __builtin_mve_vbrsrq_n_s8(__p0, __p1);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vbrsrq_n_u16(uint16x8_t __p0, int32_t __p1)
{
    return __builtin_mve_vbrsrq_n_u16(__p0, __p1);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vbrsrq_n_u32(uint32x4_t __p0, int32_t __p1)
{
    return __builtin_mve_vbrsrq_n_u32(__p0, __p1);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vbrsrq_n_u8(uint8x16_t __p0, int32_t __p1)
{
    return __builtin_mve_vbrsrq_n_u8(__p0, __p1);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vclsq_m_s16(int16x8_t __p0, int16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vclsq_m_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vclsq_m_s32(int32x4_t __p0, int32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vclsq_m_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vclsq_m_s8(int8x16_t __p0, int8x16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vclsq_m_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vclsq_s16(int16x8_t __p0)
{
    return __builtin_mve_vclsq_s16(__p0);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vclsq_s32(int32x4_t __p0)
{
    return __builtin_mve_vclsq_s32(__p0);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vclsq_s8(int8x16_t __p0)
{
    return __builtin_mve_vclsq_s8(__p0);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vclzq_m_s16(int16x8_t __p0, int16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vclzq_m_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vclzq_m_s32(int32x4_t __p0, int32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vclzq_m_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vclzq_m_s8(int8x16_t __p0, int8x16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vclzq_m_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vclzq_m_u16(uint16x8_t __p0, uint16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vclzq_m_u16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vclzq_m_u32(uint32x4_t __p0, uint32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vclzq_m_u32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vclzq_m_u8(uint8x16_t __p0, uint8x16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vclzq_m_u8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vclzq_s16(int16x8_t __p0)
{
    return __builtin_mve_vclzq_s16(__p0);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vclzq_s32(int32x4_t __p0)
{
    return __builtin_mve_vclzq_s32(__p0);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vclzq_s8(int8x16_t __p0)
{
    return __builtin_mve_vclzq_s8(__p0);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vclzq_u16(uint16x8_t __p0)
{
    return __builtin_mve_vclzq_u16(__p0);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vclzq_u32(uint32x4_t __p0)
{
    return __builtin_mve_vclzq_u32(__p0);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vclzq_u8(uint8x16_t __p0)
{
    return __builtin_mve_vclzq_u8(__p0);
}

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

static __attribute__((__always_inline__))
int16x8_t __arm_vcvtaq_m_s16_f16(int16x8_t __p0, float16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vcvtaq_m_s16_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vcvtaq_m_s32_f32(int32x4_t __p0, float32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vcvtaq_m_s32_f32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vcvtaq_m_u16_f16(uint16x8_t __p0, float16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vcvtaq_m_u16_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vcvtaq_m_u32_f32(uint32x4_t __p0, float32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vcvtaq_m_u32_f32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vcvtaq_s16_f16(float16x8_t __p0)
{
    return __builtin_mve_vcvtaq_s16_f16(__p0);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vcvtaq_s32_f32(float32x4_t __p0)
{
    return __builtin_mve_vcvtaq_s32_f32(__p0);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vcvtaq_u16_f16(float16x8_t __p0)
{
    return __builtin_mve_vcvtaq_u16_f16(__p0);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vcvtaq_u32_f32(float32x4_t __p0)
{
    return __builtin_mve_vcvtaq_u32_f32(__p0);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vcvtbq_f32_f16(float16x8_t __p0)
{
    return __builtin_mve_vcvtbq_f32_f16(__p0);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vcvtbq_m_f32_f16(float32x4_t __p0, float16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vcvtbq_m_f32_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vcvtmq_m_s16_f16(int16x8_t __p0, float16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vcvtmq_m_s16_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vcvtmq_m_s32_f32(int32x4_t __p0, float32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vcvtmq_m_s32_f32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vcvtmq_m_u16_f16(uint16x8_t __p0, float16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vcvtmq_m_u16_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vcvtmq_m_u32_f32(uint32x4_t __p0, float32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vcvtmq_m_u32_f32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vcvtmq_s16_f16(float16x8_t __p0)
{
    return __builtin_mve_vcvtmq_s16_f16(__p0);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vcvtmq_s32_f32(float32x4_t __p0)
{
    return __builtin_mve_vcvtmq_s32_f32(__p0);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vcvtmq_u16_f16(float16x8_t __p0)
{
    return __builtin_mve_vcvtmq_u16_f16(__p0);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vcvtmq_u32_f32(float32x4_t __p0)
{
    return __builtin_mve_vcvtmq_u32_f32(__p0);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vcvtnq_m_s16_f16(int16x8_t __p0, float16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vcvtnq_m_s16_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vcvtnq_m_s32_f32(int32x4_t __p0, float32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vcvtnq_m_s32_f32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vcvtnq_m_u16_f16(uint16x8_t __p0, float16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vcvtnq_m_u16_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vcvtnq_m_u32_f32(uint32x4_t __p0, float32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vcvtnq_m_u32_f32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vcvtnq_s16_f16(float16x8_t __p0)
{
    return __builtin_mve_vcvtnq_s16_f16(__p0);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vcvtnq_s32_f32(float32x4_t __p0)
{
    return __builtin_mve_vcvtnq_s32_f32(__p0);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vcvtnq_u16_f16(float16x8_t __p0)
{
    return __builtin_mve_vcvtnq_u16_f16(__p0);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vcvtnq_u32_f32(float32x4_t __p0)
{
    return __builtin_mve_vcvtnq_u32_f32(__p0);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vcvtpq_m_s16_f16(int16x8_t __p0, float16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vcvtpq_m_s16_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vcvtpq_m_s32_f32(int32x4_t __p0, float32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vcvtpq_m_s32_f32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vcvtpq_m_u16_f16(uint16x8_t __p0, float16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vcvtpq_m_u16_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vcvtpq_m_u32_f32(uint32x4_t __p0, float32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vcvtpq_m_u32_f32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vcvtpq_s16_f16(float16x8_t __p0)
{
    return __builtin_mve_vcvtpq_s16_f16(__p0);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vcvtpq_s32_f32(float32x4_t __p0)
{
    return __builtin_mve_vcvtpq_s32_f32(__p0);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vcvtpq_u16_f16(float16x8_t __p0)
{
    return __builtin_mve_vcvtpq_u16_f16(__p0);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vcvtpq_u32_f32(float32x4_t __p0)
{
    return __builtin_mve_vcvtpq_u32_f32(__p0);
}

static __attribute__((__always_inline__))
float16x8_t __arm_vcvtq_f16_s16(int16x8_t __p0)
{
    return __builtin_mve_vcvtq_f16_s16(__p0);
}

static __attribute__((__always_inline__))
float16x8_t __arm_vcvtq_f16_u16(uint16x8_t __p0)
{
    return __builtin_mve_vcvtq_f16_u16(__p0);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vcvtq_f32_s32(int32x4_t __p0)
{
    return __builtin_mve_vcvtq_f32_s32(__p0);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vcvtq_f32_u32(uint32x4_t __p0)
{
    return __builtin_mve_vcvtq_f32_u32(__p0);
}

static __attribute__((__always_inline__))
float16x8_t __arm_vcvtq_m_f16_s16(float16x8_t __p0, int16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vcvtq_m_f16_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float16x8_t __arm_vcvtq_m_f16_u16(float16x8_t __p0, uint16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vcvtq_m_f16_u16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vcvtq_m_f32_s32(float32x4_t __p0, int32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vcvtq_m_f32_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vcvtq_m_f32_u32(float32x4_t __p0, uint32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vcvtq_m_f32_u32(__p0, __p1, __p2);
}

#define __arm_vcvtq_m_n_f16_s16(__p0, __p1, __p2, __p3) ({ \
    __builtin_mve_vcvtq_m_n_f16_s16(__p0, __p1, __p2, __p3); \
})

#define __arm_vcvtq_m_n_f16_u16(__p0, __p1, __p2, __p3) ({ \
    __builtin_mve_vcvtq_m_n_f16_u16(__p0, __p1, __p2, __p3); \
})

#define __arm_vcvtq_m_n_f32_s32(__p0, __p1, __p2, __p3) ({ \
    __builtin_mve_vcvtq_m_n_f32_s32(__p0, __p1, __p2, __p3); \
})

#define __arm_vcvtq_m_n_f32_u32(__p0, __p1, __p2, __p3) ({ \
    __builtin_mve_vcvtq_m_n_f32_u32(__p0, __p1, __p2, __p3); \
})

#define __arm_vcvtq_m_n_s16_f16(__p0, __p1, __p2, __p3) ({ \
    __builtin_mve_vcvtq_m_n_s16_f16(__p0, __p1, __p2, __p3); \
})

#define __arm_vcvtq_m_n_s32_f32(__p0, __p1, __p2, __p3) ({ \
    __builtin_mve_vcvtq_m_n_s32_f32(__p0, __p1, __p2, __p3); \
})

#define __arm_vcvtq_m_n_u16_f16(__p0, __p1, __p2, __p3) ({ \
    __builtin_mve_vcvtq_m_n_u16_f16(__p0, __p1, __p2, __p3); \
})

#define __arm_vcvtq_m_n_u32_f32(__p0, __p1, __p2, __p3) ({ \
    __builtin_mve_vcvtq_m_n_u32_f32(__p0, __p1, __p2, __p3); \
})

static __attribute__((__always_inline__))
int16x8_t __arm_vcvtq_m_s16_f16(int16x8_t __p0, float16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vcvtq_m_s16_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vcvtq_m_s32_f32(int32x4_t __p0, float32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vcvtq_m_s32_f32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vcvtq_m_u16_f16(uint16x8_t __p0, float16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vcvtq_m_u16_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vcvtq_m_u32_f32(uint32x4_t __p0, float32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vcvtq_m_u32_f32(__p0, __p1, __p2);
}

#define __arm_vcvtq_n_f16_s16(__p0, __p1) ({ \
    __builtin_mve_vcvtq_n_f16_s16(__p0, __p1); \
})

#define __arm_vcvtq_n_f16_u16(__p0, __p1) ({ \
    __builtin_mve_vcvtq_n_f16_u16(__p0, __p1); \
})

#define __arm_vcvtq_n_f32_s32(__p0, __p1) ({ \
    __builtin_mve_vcvtq_n_f32_s32(__p0, __p1); \
})

#define __arm_vcvtq_n_f32_u32(__p0, __p1) ({ \
    __builtin_mve_vcvtq_n_f32_u32(__p0, __p1); \
})

#define __arm_vcvtq_n_s16_f16(__p0, __p1) ({ \
    __builtin_mve_vcvtq_n_s16_f16(__p0, __p1); \
})

#define __arm_vcvtq_n_s32_f32(__p0, __p1) ({ \
    __builtin_mve_vcvtq_n_s32_f32(__p0, __p1); \
})

#define __arm_vcvtq_n_u16_f16(__p0, __p1) ({ \
    __builtin_mve_vcvtq_n_u16_f16(__p0, __p1); \
})

#define __arm_vcvtq_n_u32_f32(__p0, __p1) ({ \
    __builtin_mve_vcvtq_n_u32_f32(__p0, __p1); \
})

static __attribute__((__always_inline__))
int16x8_t __arm_vcvtq_s16_f16(float16x8_t __p0)
{
    return __builtin_mve_vcvtq_s16_f16(__p0);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vcvtq_s32_f32(float32x4_t __p0)
{
    return __builtin_mve_vcvtq_s32_f32(__p0);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vcvtq_u16_f16(float16x8_t __p0)
{
    return __builtin_mve_vcvtq_u16_f16(__p0);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vcvtq_u32_f32(float32x4_t __p0)
{
    return __builtin_mve_vcvtq_u32_f32(__p0);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vcvttq_f32_f16(float16x8_t __p0)
{
    return __builtin_mve_vcvttq_f32_f16(__p0);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vcvttq_m_f32_f16(float32x4_t __p0, float16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vcvttq_m_f32_f16(__p0, __p1, __p2);
}

#endif /* MVE floating point */

#define __arm_vddupq_m_n_u16(__p0, __p1, __p2, __p3) ({ \
    __builtin_mve_vddupq_m_n_u16(__p0, __p1, __p2, __p3); \
})

#define __arm_vddupq_m_n_u32(__p0, __p1, __p2, __p3) ({ \
    __builtin_mve_vddupq_m_n_u32(__p0, __p1, __p2, __p3); \
})

#define __arm_vddupq_m_n_u8(__p0, __p1, __p2, __p3) ({ \
    __builtin_mve_vddupq_m_n_u8(__p0, __p1, __p2, __p3); \
})

#define __arm_vddupq_m_wb_u16(__p0, __p1, __p2, __p3) ({ \
    __builtin_mve_vddupq_m_wb_u16(__p0, __p1, __p2, __p3); \
})

#define __arm_vddupq_m_wb_u32(__p0, __p1, __p2, __p3) ({ \
    __builtin_mve_vddupq_m_wb_u32(__p0, __p1, __p2, __p3); \
})

#define __arm_vddupq_m_wb_u8(__p0, __p1, __p2, __p3) ({ \
    __builtin_mve_vddupq_m_wb_u8(__p0, __p1, __p2, __p3); \
})

#define __arm_vddupq_n_u16(__p0, __p1) ({ \
    __builtin_mve_vddupq_n_u16(__p0, __p1); \
})

#define __arm_vddupq_n_u32(__p0, __p1) ({ \
    __builtin_mve_vddupq_n_u32(__p0, __p1); \
})

#define __arm_vddupq_n_u8(__p0, __p1) ({ \
    __builtin_mve_vddupq_n_u8(__p0, __p1); \
})

#define __arm_vddupq_wb_u16(__p0, __p1) ({ \
    __builtin_mve_vddupq_wb_u16(__p0, __p1); \
})

#define __arm_vddupq_wb_u32(__p0, __p1) ({ \
    __builtin_mve_vddupq_wb_u32(__p0, __p1); \
})

#define __arm_vddupq_wb_u8(__p0, __p1) ({ \
    __builtin_mve_vddupq_wb_u8(__p0, __p1); \
})

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

static __attribute__((__always_inline__))
float16x8_t __arm_vdupq_m_n_f16(float16x8_t __p0, float16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vdupq_m_n_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vdupq_m_n_f32(float32x4_t __p0, float32_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vdupq_m_n_f32(__p0, __p1, __p2);
}

#endif /* MVE floating point */

static __attribute__((__always_inline__))
int16x8_t __arm_vdupq_m_n_s16(int16x8_t __p0, int16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vdupq_m_n_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vdupq_m_n_s32(int32x4_t __p0, int32_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vdupq_m_n_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vdupq_m_n_s8(int8x16_t __p0, int8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vdupq_m_n_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vdupq_m_n_u16(uint16x8_t __p0, uint16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vdupq_m_n_u16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vdupq_m_n_u32(uint32x4_t __p0, uint32_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vdupq_m_n_u32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vdupq_m_n_u8(uint8x16_t __p0, uint8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vdupq_m_n_u8(__p0, __p1, __p2);
}

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

static __attribute__((__always_inline__))
float16x8_t __arm_vdupq_n_f16(float16_t __p0)
{
    return __builtin_mve_vdupq_n_f16(__p0);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vdupq_n_f32(float32_t __p0)
{
    return __builtin_mve_vdupq_n_f32(__p0);
}

#endif /* MVE floating point */

static __attribute__((__always_inline__))
int16x8_t __arm_vdupq_n_s16(int16_t __p0)
{
    return __builtin_mve_vdupq_n_s16(__p0);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vdupq_n_s32(int32_t __p0)
{
    return __builtin_mve_vdupq_n_s32(__p0);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vdupq_n_s8(int8_t __p0)
{
    return __builtin_mve_vdupq_n_s8(__p0);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vdupq_n_u16(uint16_t __p0)
{
    return __builtin_mve_vdupq_n_u16(__p0);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vdupq_n_u32(uint32_t __p0)
{
    return __builtin_mve_vdupq_n_u32(__p0);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vdupq_n_u8(uint8_t __p0)
{
    return __builtin_mve_vdupq_n_u8(__p0);
}

#define __arm_vdwdupq_m_n_u16(__p0, __p1, __p2, __p3, __p4) ({ \
    __builtin_mve_vdwdupq_m_n_u16(__p0, __p1, __p2, __p3, __p4); \
})

#define __arm_vdwdupq_m_n_u32(__p0, __p1, __p2, __p3, __p4) ({ \
    __builtin_mve_vdwdupq_m_n_u32(__p0, __p1, __p2, __p3, __p4); \
})

#define __arm_vdwdupq_m_n_u8(__p0, __p1, __p2, __p3, __p4) ({ \
    __builtin_mve_vdwdupq_m_n_u8(__p0, __p1, __p2, __p3, __p4); \
})

#define __arm_vdwdupq_m_wb_u16(__p0, __p1, __p2, __p3, __p4) ({ \
    __builtin_mve_vdwdupq_m_wb_u16(__p0, __p1, __p2, __p3, __p4); \
})

#define __arm_vdwdupq_m_wb_u32(__p0, __p1, __p2, __p3, __p4) ({ \
    __builtin_mve_vdwdupq_m_wb_u32(__p0, __p1, __p2, __p3, __p4); \
})

#define __arm_vdwdupq_m_wb_u8(__p0, __p1, __p2, __p3, __p4) ({ \
    __builtin_mve_vdwdupq_m_wb_u8(__p0, __p1, __p2, __p3, __p4); \
})

#define __arm_vdwdupq_n_u16(__p0, __p1, __p2) ({ \
    __builtin_mve_vdwdupq_n_u16(__p0, __p1, __p2); \
})

#define __arm_vdwdupq_n_u32(__p0, __p1, __p2) ({ \
    __builtin_mve_vdwdupq_n_u32(__p0, __p1, __p2); \
})

#define __arm_vdwdupq_n_u8(__p0, __p1, __p2) ({ \
    __builtin_mve_vdwdupq_n_u8(__p0, __p1, __p2); \
})

#define __arm_vdwdupq_wb_u16(__p0, __p1, __p2) ({ \
    __builtin_mve_vdwdupq_wb_u16(__p0, __p1, __p2); \
})

#define __arm_vdwdupq_wb_u32(__p0, __p1, __p2) ({ \
    __builtin_mve_vdwdupq_wb_u32(__p0, __p1, __p2); \
})

#define __arm_vdwdupq_wb_u8(__p0, __p1, __p2) ({ \
    __builtin_mve_vdwdupq_wb_u8(__p0, __p1, __p2); \
})

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

static __attribute__((__always_inline__))
float16x8_t __arm_vfmaq_f16(float16x8_t __p0, float16x8_t __p1, float16x8_t __p2)
{
    return __builtin_mve_vfmaq_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vfmaq_f32(float32x4_t __p0, float32x4_t __p1, float32x4_t __p2)
{
    return __builtin_mve_vfmaq_f32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float16x8_t __arm_vfmaq_m_f16(float16x8_t __p0, float16x8_t __p1, float16x8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vfmaq_m_f16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vfmaq_m_f32(float32x4_t __p0, float32x4_t __p1, float32x4_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vfmaq_m_f32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
float16x8_t __arm_vfmaq_m_n_f16(float16x8_t __p0, float16x8_t __p1, float16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vfmaq_m_n_f16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vfmaq_m_n_f32(float32x4_t __p0, float32x4_t __p1, float32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vfmaq_m_n_f32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
float16x8_t __arm_vfmaq_n_f16(float16x8_t __p0, float16x8_t __p1, float16_t __p2)
{
    return __builtin_mve_vfmaq_n_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vfmaq_n_f32(float32x4_t __p0, float32x4_t __p1, float32_t __p2)
{
    return __builtin_mve_vfmaq_n_f32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float16x8_t __arm_vfmasq_m_n_f16(float16x8_t __p0, float16x8_t __p1, float16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vfmasq_m_n_f16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vfmasq_m_n_f32(float32x4_t __p0, float32x4_t __p1, float32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vfmasq_m_n_f32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
float16x8_t __arm_vfmasq_n_f16(float16x8_t __p0, float16x8_t __p1, float16_t __p2)
{
    return __builtin_mve_vfmasq_n_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vfmasq_n_f32(float32x4_t __p0, float32x4_t __p1, float32_t __p2)
{
    return __builtin_mve_vfmasq_n_f32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float16x8_t __arm_vfmsq_f16(float16x8_t __p0, float16x8_t __p1, float16x8_t __p2)
{
    return __builtin_mve_vfmsq_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vfmsq_f32(float32x4_t __p0, float32x4_t __p1, float32x4_t __p2)
{
    return __builtin_mve_vfmsq_f32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float16x8_t __arm_vfmsq_m_f16(float16x8_t __p0, float16x8_t __p1, float16x8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vfmsq_m_f16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vfmsq_m_f32(float32x4_t __p0, float32x4_t __p1, float32x4_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vfmsq_m_f32(__p0, __p1, __p2, __p3);
}

#endif /* MVE floating point */

static __attribute__((__always_inline__))
int16x8_t __arm_vhaddq_m_n_s16(int16x8_t __p0, int16x8_t __p1, int16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vhaddq_m_n_s16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vhaddq_m_n_s32(int32x4_t __p0, int32x4_t __p1, int32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vhaddq_m_n_s32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vhaddq_m_n_s8(int8x16_t __p0, int8x16_t __p1, int8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vhaddq_m_n_s8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vhaddq_m_n_u16(uint16x8_t __p0, uint16x8_t __p1, uint16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vhaddq_m_n_u16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vhaddq_m_n_u32(uint32x4_t __p0, uint32x4_t __p1, uint32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vhaddq_m_n_u32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vhaddq_m_n_u8(uint8x16_t __p0, uint8x16_t __p1, uint8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vhaddq_m_n_u8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vhaddq_n_s16(int16x8_t __p0, int16_t __p1)
{
    return __builtin_mve_vhaddq_n_s16(__p0, __p1);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vhaddq_n_s32(int32x4_t __p0, int32_t __p1)
{
    return __builtin_mve_vhaddq_n_s32(__p0, __p1);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vhaddq_n_s8(int8x16_t __p0, int8_t __p1)
{
    return __builtin_mve_vhaddq_n_s8(__p0, __p1);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vhaddq_n_u16(uint16x8_t __p0, uint16_t __p1)
{
    return __builtin_mve_vhaddq_n_u16(__p0, __p1);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vhaddq_n_u32(uint32x4_t __p0, uint32_t __p1)
{
    return __builtin_mve_vhaddq_n_u32(__p0, __p1);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vhaddq_n_u8(uint8x16_t __p0, uint8_t __p1)
{
    return __builtin_mve_vhaddq_n_u8(__p0, __p1);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vhsubq_m_n_s16(int16x8_t __p0, int16x8_t __p1, int16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vhsubq_m_n_s16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vhsubq_m_n_s32(int32x4_t __p0, int32x4_t __p1, int32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vhsubq_m_n_s32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vhsubq_m_n_s8(int8x16_t __p0, int8x16_t __p1, int8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vhsubq_m_n_s8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vhsubq_m_n_u16(uint16x8_t __p0, uint16x8_t __p1, uint16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vhsubq_m_n_u16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vhsubq_m_n_u32(uint32x4_t __p0, uint32x4_t __p1, uint32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vhsubq_m_n_u32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vhsubq_m_n_u8(uint8x16_t __p0, uint8x16_t __p1, uint8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vhsubq_m_n_u8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vhsubq_n_s16(int16x8_t __p0, int16_t __p1)
{
    return __builtin_mve_vhsubq_n_s16(__p0, __p1);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vhsubq_n_s32(int32x4_t __p0, int32_t __p1)
{
    return __builtin_mve_vhsubq_n_s32(__p0, __p1);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vhsubq_n_s8(int8x16_t __p0, int8_t __p1)
{
    return __builtin_mve_vhsubq_n_s8(__p0, __p1);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vhsubq_n_u16(uint16x8_t __p0, uint16_t __p1)
{
    return __builtin_mve_vhsubq_n_u16(__p0, __p1);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vhsubq_n_u32(uint32x4_t __p0, uint32_t __p1)
{
    return __builtin_mve_vhsubq_n_u32(__p0, __p1);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vhsubq_n_u8(uint8x16_t __p0, uint8_t __p1)
{
    return __builtin_mve_vhsubq_n_u8(__p0, __p1);
}

#define __arm_vidupq_m_n_u16(__p0, __p1, __p2, __p3) ({ \
    __builtin_mve_vidupq_m_n_u16(__p0, __p1, __p2, __p3); \
})

#define __arm_vidupq_m_n_u32(__p0, __p1, __p2, __p3) ({ \
    __builtin_mve_vidupq_m_n_u32(__p0, __p1, __p2, __p3); \
})

#define __arm_vidupq_m_n_u8(__p0, __p1, __p2, __p3) ({ \
    __builtin_mve_vidupq_m_n_u8(__p0, __p1, __p2, __p3); \
})

#define __arm_vidupq_m_wb_u16(__p0, __p1, __p2, __p3) ({ \
    __builtin_mve_vidupq_m_wb_u16(__p0, __p1, __p2, __p3); \
})

#define __arm_vidupq_m_wb_u32(__p0, __p1, __p2, __p3) ({ \
    __builtin_mve_vidupq_m_wb_u32(__p0, __p1, __p2, __p3); \
})

#define __arm_vidupq_m_wb_u8(__p0, __p1, __p2, __p3) ({ \
    __builtin_mve_vidupq_m_wb_u8(__p0, __p1, __p2, __p3); \
})

#define __arm_vidupq_n_u16(__p0, __p1) ({ \
    __builtin_mve_vidupq_n_u16(__p0, __p1); \
})

#define __arm_vidupq_n_u32(__p0, __p1) ({ \
    __builtin_mve_vidupq_n_u32(__p0, __p1); \
})

#define __arm_vidupq_n_u8(__p0, __p1) ({ \
    __builtin_mve_vidupq_n_u8(__p0, __p1); \
})

#define __arm_vidupq_wb_u16(__p0, __p1) ({ \
    __builtin_mve_vidupq_wb_u16(__p0, __p1); \
})

#define __arm_vidupq_wb_u32(__p0, __p1) ({ \
    __builtin_mve_vidupq_wb_u32(__p0, __p1); \
})

#define __arm_vidupq_wb_u8(__p0, __p1) ({ \
    __builtin_mve_vidupq_wb_u8(__p0, __p1); \
})

#define __arm_viwdupq_m_n_u16(__p0, __p1, __p2, __p3, __p4) ({ \
    __builtin_mve_viwdupq_m_n_u16(__p0, __p1, __p2, __p3, __p4); \
})

#define __arm_viwdupq_m_n_u32(__p0, __p1, __p2, __p3, __p4) ({ \
    __builtin_mve_viwdupq_m_n_u32(__p0, __p1, __p2, __p3, __p4); \
})

#define __arm_viwdupq_m_n_u8(__p0, __p1, __p2, __p3, __p4) ({ \
    __builtin_mve_viwdupq_m_n_u8(__p0, __p1, __p2, __p3, __p4); \
})

#define __arm_viwdupq_m_wb_u16(__p0, __p1, __p2, __p3, __p4) ({ \
    __builtin_mve_viwdupq_m_wb_u16(__p0, __p1, __p2, __p3, __p4); \
})

#define __arm_viwdupq_m_wb_u32(__p0, __p1, __p2, __p3, __p4) ({ \
    __builtin_mve_viwdupq_m_wb_u32(__p0, __p1, __p2, __p3, __p4); \
})

#define __arm_viwdupq_m_wb_u8(__p0, __p1, __p2, __p3, __p4) ({ \
    __builtin_mve_viwdupq_m_wb_u8(__p0, __p1, __p2, __p3, __p4); \
})

#define __arm_viwdupq_n_u16(__p0, __p1, __p2) ({ \
    __builtin_mve_viwdupq_n_u16(__p0, __p1, __p2); \
})

#define __arm_viwdupq_n_u32(__p0, __p1, __p2) ({ \
    __builtin_mve_viwdupq_n_u32(__p0, __p1, __p2); \
})

#define __arm_viwdupq_n_u8(__p0, __p1, __p2) ({ \
    __builtin_mve_viwdupq_n_u8(__p0, __p1, __p2); \
})

#define __arm_viwdupq_wb_u16(__p0, __p1, __p2) ({ \
    __builtin_mve_viwdupq_wb_u16(__p0, __p1, __p2); \
})

#define __arm_viwdupq_wb_u32(__p0, __p1, __p2) ({ \
    __builtin_mve_viwdupq_wb_u32(__p0, __p1, __p2); \
})

#define __arm_viwdupq_wb_u8(__p0, __p1, __p2) ({ \
    __builtin_mve_viwdupq_wb_u8(__p0, __p1, __p2); \
})

static __attribute__((__always_inline__))
uint16_t __arm_vmaxavq_p_s16(uint16_t __p0, int16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmaxavq_p_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint32_t __arm_vmaxavq_p_s32(uint32_t __p0, int32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmaxavq_p_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint8_t __arm_vmaxavq_p_s8(uint8_t __p0, int8x16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmaxavq_p_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint16_t __arm_vmaxavq_s16(uint16_t __p0, int16x8_t __p1)
{
    return __builtin_mve_vmaxavq_s16(__p0, __p1);
}

static __attribute__((__always_inline__))
uint32_t __arm_vmaxavq_s32(uint32_t __p0, int32x4_t __p1)
{
    return __builtin_mve_vmaxavq_s32(__p0, __p1);
}

static __attribute__((__always_inline__))
uint8_t __arm_vmaxavq_s8(uint8_t __p0, int8x16_t __p1)
{
    return __builtin_mve_vmaxavq_s8(__p0, __p1);
}

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

static __attribute__((__always_inline__))
float16_t __arm_vmaxnmavq_f16(float16_t __p0, float16x8_t __p1)
{
    return __builtin_mve_vmaxnmavq_f16(__p0, __p1);
}

static __attribute__((__always_inline__))
float32_t __arm_vmaxnmavq_f32(float32_t __p0, float32x4_t __p1)
{
    return __builtin_mve_vmaxnmavq_f32(__p0, __p1);
}

static __attribute__((__always_inline__))
float16_t __arm_vmaxnmavq_p_f16(float16_t __p0, float16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmaxnmavq_p_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float32_t __arm_vmaxnmavq_p_f32(float32_t __p0, float32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmaxnmavq_p_f32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float16_t __arm_vmaxnmvq_f16(float16_t __p0, float16x8_t __p1)
{
    return __builtin_mve_vmaxnmvq_f16(__p0, __p1);
}

static __attribute__((__always_inline__))
float32_t __arm_vmaxnmvq_f32(float32_t __p0, float32x4_t __p1)
{
    return __builtin_mve_vmaxnmvq_f32(__p0, __p1);
}

static __attribute__((__always_inline__))
float16_t __arm_vmaxnmvq_p_f16(float16_t __p0, float16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmaxnmvq_p_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float32_t __arm_vmaxnmvq_p_f32(float32_t __p0, float32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmaxnmvq_p_f32(__p0, __p1, __p2);
}

#endif /* MVE floating point */

static __attribute__((__always_inline__))
int16_t __arm_vmaxvq_p_s16(int16_t __p0, int16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmaxvq_p_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32_t __arm_vmaxvq_p_s32(int32_t __p0, int32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmaxvq_p_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8_t __arm_vmaxvq_p_s8(int8_t __p0, int8x16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmaxvq_p_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint16_t __arm_vmaxvq_p_u16(uint16_t __p0, uint16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmaxvq_p_u16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint32_t __arm_vmaxvq_p_u32(uint32_t __p0, uint32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmaxvq_p_u32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint8_t __arm_vmaxvq_p_u8(uint8_t __p0, uint8x16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmaxvq_p_u8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint16_t __arm_vminavq_p_s16(uint16_t __p0, int16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vminavq_p_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint32_t __arm_vminavq_p_s32(uint32_t __p0, int32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vminavq_p_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint8_t __arm_vminavq_p_s8(uint8_t __p0, int8x16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vminavq_p_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint16_t __arm_vminavq_s16(uint16_t __p0, int16x8_t __p1)
{
    return __builtin_mve_vminavq_s16(__p0, __p1);
}

static __attribute__((__always_inline__))
uint32_t __arm_vminavq_s32(uint32_t __p0, int32x4_t __p1)
{
    return __builtin_mve_vminavq_s32(__p0, __p1);
}

static __attribute__((__always_inline__))
uint8_t __arm_vminavq_s8(uint8_t __p0, int8x16_t __p1)
{
    return __builtin_mve_vminavq_s8(__p0, __p1);
}

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

static __attribute__((__always_inline__))
float16_t __arm_vminnmavq_f16(float16_t __p0, float16x8_t __p1)
{
    return __builtin_mve_vminnmavq_f16(__p0, __p1);
}

static __attribute__((__always_inline__))
float32_t __arm_vminnmavq_f32(float32_t __p0, float32x4_t __p1)
{
    return __builtin_mve_vminnmavq_f32(__p0, __p1);
}

static __attribute__((__always_inline__))
float16_t __arm_vminnmavq_p_f16(float16_t __p0, float16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vminnmavq_p_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float32_t __arm_vminnmavq_p_f32(float32_t __p0, float32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vminnmavq_p_f32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float16_t __arm_vminnmvq_f16(float16_t __p0, float16x8_t __p1)
{
    return __builtin_mve_vminnmvq_f16(__p0, __p1);
}

static __attribute__((__always_inline__))
float32_t __arm_vminnmvq_f32(float32_t __p0, float32x4_t __p1)
{
    return __builtin_mve_vminnmvq_f32(__p0, __p1);
}

static __attribute__((__always_inline__))
float16_t __arm_vminnmvq_p_f16(float16_t __p0, float16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vminnmvq_p_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float32_t __arm_vminnmvq_p_f32(float32_t __p0, float32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vminnmvq_p_f32(__p0, __p1, __p2);
}

#endif /* MVE floating point */

static __attribute__((__always_inline__))
int16_t __arm_vminvq_p_s16(int16_t __p0, int16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vminvq_p_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32_t __arm_vminvq_p_s32(int32_t __p0, int32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vminvq_p_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8_t __arm_vminvq_p_s8(int8_t __p0, int8x16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vminvq_p_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint16_t __arm_vminvq_p_u16(uint16_t __p0, uint16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vminvq_p_u16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint32_t __arm_vminvq_p_u32(uint32_t __p0, uint32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vminvq_p_u32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint8_t __arm_vminvq_p_u8(uint8_t __p0, uint8x16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vminvq_p_u8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vmlaq_m_n_s16(int16x8_t __p0, int16x8_t __p1, int16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vmlaq_m_n_s16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vmlaq_m_n_s32(int32x4_t __p0, int32x4_t __p1, int32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vmlaq_m_n_s32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vmlaq_m_n_s8(int8x16_t __p0, int8x16_t __p1, int8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vmlaq_m_n_s8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vmlaq_m_n_u16(uint16x8_t __p0, uint16x8_t __p1, uint16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vmlaq_m_n_u16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vmlaq_m_n_u32(uint32x4_t __p0, uint32x4_t __p1, uint32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vmlaq_m_n_u32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vmlaq_m_n_u8(uint8x16_t __p0, uint8x16_t __p1, uint8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vmlaq_m_n_u8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vmlaq_n_s16(int16x8_t __p0, int16x8_t __p1, int16_t __p2)
{
    return __builtin_mve_vmlaq_n_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vmlaq_n_s32(int32x4_t __p0, int32x4_t __p1, int32_t __p2)
{
    return __builtin_mve_vmlaq_n_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vmlaq_n_s8(int8x16_t __p0, int8x16_t __p1, int8_t __p2)
{
    return __builtin_mve_vmlaq_n_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vmlaq_n_u16(uint16x8_t __p0, uint16x8_t __p1, uint16_t __p2)
{
    return __builtin_mve_vmlaq_n_u16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vmlaq_n_u32(uint32x4_t __p0, uint32x4_t __p1, uint32_t __p2)
{
    return __builtin_mve_vmlaq_n_u32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vmlaq_n_u8(uint8x16_t __p0, uint8x16_t __p1, uint8_t __p2)
{
    return __builtin_mve_vmlaq_n_u8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vmlasq_m_n_s16(int16x8_t __p0, int16x8_t __p1, int16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vmlasq_m_n_s16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vmlasq_m_n_s32(int32x4_t __p0, int32x4_t __p1, int32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vmlasq_m_n_s32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vmlasq_m_n_s8(int8x16_t __p0, int8x16_t __p1, int8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vmlasq_m_n_s8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vmlasq_m_n_u16(uint16x8_t __p0, uint16x8_t __p1, uint16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vmlasq_m_n_u16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vmlasq_m_n_u32(uint32x4_t __p0, uint32x4_t __p1, uint32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vmlasq_m_n_u32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vmlasq_m_n_u8(uint8x16_t __p0, uint8x16_t __p1, uint8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vmlasq_m_n_u8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vmlasq_n_s16(int16x8_t __p0, int16x8_t __p1, int16_t __p2)
{
    return __builtin_mve_vmlasq_n_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vmlasq_n_s32(int32x4_t __p0, int32x4_t __p1, int32_t __p2)
{
    return __builtin_mve_vmlasq_n_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vmlasq_n_s8(int8x16_t __p0, int8x16_t __p1, int8_t __p2)
{
    return __builtin_mve_vmlasq_n_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vmlasq_n_u16(uint16x8_t __p0, uint16x8_t __p1, uint16_t __p2)
{
    return __builtin_mve_vmlasq_n_u16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vmlasq_n_u32(uint32x4_t __p0, uint32x4_t __p1, uint32_t __p2)
{
    return __builtin_mve_vmlasq_n_u32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vmlasq_n_u8(uint8x16_t __p0, uint8x16_t __p1, uint8_t __p2)
{
    return __builtin_mve_vmlasq_n_u8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vmovlbq_m_s16(int32x4_t __p0, int16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmovlbq_m_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vmovlbq_m_s8(int16x8_t __p0, int8x16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmovlbq_m_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vmovlbq_m_u16(uint32x4_t __p0, uint16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmovlbq_m_u16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vmovlbq_m_u8(uint16x8_t __p0, uint8x16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmovlbq_m_u8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vmovlbq_s16(int16x8_t __p0)
{
    return __builtin_mve_vmovlbq_s16(__p0);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vmovlbq_s8(int8x16_t __p0)
{
    return __builtin_mve_vmovlbq_s8(__p0);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vmovlbq_u16(uint16x8_t __p0)
{
    return __builtin_mve_vmovlbq_u16(__p0);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vmovlbq_u8(uint8x16_t __p0)
{
    return __builtin_mve_vmovlbq_u8(__p0);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vmovltq_m_s16(int32x4_t __p0, int16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmovltq_m_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vmovltq_m_s8(int16x8_t __p0, int8x16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmovltq_m_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vmovltq_m_u16(uint32x4_t __p0, uint16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmovltq_m_u16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vmovltq_m_u8(uint16x8_t __p0, uint8x16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmovltq_m_u8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vmovltq_s16(int16x8_t __p0)
{
    return __builtin_mve_vmovltq_s16(__p0);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vmovltq_s8(int8x16_t __p0)
{
    return __builtin_mve_vmovltq_s8(__p0);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vmovltq_u16(uint16x8_t __p0)
{
    return __builtin_mve_vmovltq_u16(__p0);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vmovltq_u8(uint8x16_t __p0)
{
    return __builtin_mve_vmovltq_u8(__p0);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vmovnbq_m_s16(int8x16_t __p0, int16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmovnbq_m_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vmovnbq_m_s32(int16x8_t __p0, int32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmovnbq_m_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vmovnbq_m_u16(uint8x16_t __p0, uint16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmovnbq_m_u16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vmovnbq_m_u32(uint16x8_t __p0, uint32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmovnbq_m_u32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vmovnbq_s16(int8x16_t __p0, int16x8_t __p1)
{
    return __builtin_mve_vmovnbq_s16(__p0, __p1);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vmovnbq_s32(int16x8_t __p0, int32x4_t __p1)
{
    return __builtin_mve_vmovnbq_s32(__p0, __p1);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vmovnbq_u16(uint8x16_t __p0, uint16x8_t __p1)
{
    return __builtin_mve_vmovnbq_u16(__p0, __p1);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vmovnbq_u32(uint16x8_t __p0, uint32x4_t __p1)
{
    return __builtin_mve_vmovnbq_u32(__p0, __p1);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vmovntq_m_s16(int8x16_t __p0, int16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmovntq_m_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vmovntq_m_s32(int16x8_t __p0, int32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmovntq_m_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vmovntq_m_u16(uint8x16_t __p0, uint16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmovntq_m_u16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vmovntq_m_u32(uint16x8_t __p0, uint32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmovntq_m_u32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vmovntq_s16(int8x16_t __p0, int16x8_t __p1)
{
    return __builtin_mve_vmovntq_s16(__p0, __p1);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vmovntq_s32(int16x8_t __p0, int32x4_t __p1)
{
    return __builtin_mve_vmovntq_s32(__p0, __p1);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vmovntq_u16(uint8x16_t __p0, uint16x8_t __p1)
{
    return __builtin_mve_vmovntq_u16(__p0, __p1);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vmovntq_u32(uint16x8_t __p0, uint32x4_t __p1)
{
    return __builtin_mve_vmovntq_u32(__p0, __p1);
}

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

static __attribute__((__always_inline__))
float16x8_t __arm_vmulq_m_n_f16(float16x8_t __p0, float16x8_t __p1, float16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vmulq_m_n_f16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vmulq_m_n_f32(float32x4_t __p0, float32x4_t __p1, float32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vmulq_m_n_f32(__p0, __p1, __p2, __p3);
}

#endif /* MVE floating point */

static __attribute__((__always_inline__))
int16x8_t __arm_vmulq_m_n_s16(int16x8_t __p0, int16x8_t __p1, int16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vmulq_m_n_s16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vmulq_m_n_s32(int32x4_t __p0, int32x4_t __p1, int32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vmulq_m_n_s32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vmulq_m_n_s8(int8x16_t __p0, int8x16_t __p1, int8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vmulq_m_n_s8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vmulq_m_n_u16(uint16x8_t __p0, uint16x8_t __p1, uint16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vmulq_m_n_u16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vmulq_m_n_u32(uint32x4_t __p0, uint32x4_t __p1, uint32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vmulq_m_n_u32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vmulq_m_n_u8(uint8x16_t __p0, uint8x16_t __p1, uint8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vmulq_m_n_u8(__p0, __p1, __p2, __p3);
}

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

static __attribute__((__always_inline__))
float16x8_t __arm_vmulq_n_f16(float16x8_t __p0, float16_t __p1)
{
    return __builtin_mve_vmulq_n_f16(__p0, __p1);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vmulq_n_f32(float32x4_t __p0, float32_t __p1)
{
    return __builtin_mve_vmulq_n_f32(__p0, __p1);
}

#endif /* MVE floating point */

static __attribute__((__always_inline__))
int16x8_t __arm_vmulq_n_s16(int16x8_t __p0, int16_t __p1)
{
    return __builtin_mve_vmulq_n_s16(__p0, __p1);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vmulq_n_s32(int32x4_t __p0, int32_t __p1)
{
    return __builtin_mve_vmulq_n_s32(__p0, __p1);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vmulq_n_s8(int8x16_t __p0, int8_t __p1)
{
    return __builtin_mve_vmulq_n_s8(__p0, __p1);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vmulq_n_u16(uint16x8_t __p0, uint16_t __p1)
{
    return __builtin_mve_vmulq_n_u16(__p0, __p1);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vmulq_n_u32(uint32x4_t __p0, uint32_t __p1)
{
    return __builtin_mve_vmulq_n_u32(__p0, __p1);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vmulq_n_u8(uint8x16_t __p0, uint8_t __p1)
{
    return __builtin_mve_vmulq_n_u8(__p0, __p1);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vmvnq_m_s16(int16x8_t __p0, int16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmvnq_m_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vmvnq_m_s32(int32x4_t __p0, int32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmvnq_m_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vmvnq_m_s8(int8x16_t __p0, int8x16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmvnq_m_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vmvnq_m_u16(uint16x8_t __p0, uint16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmvnq_m_u16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vmvnq_m_u32(uint32x4_t __p0, uint32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmvnq_m_u32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vmvnq_m_u8(uint8x16_t __p0, uint8x16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vmvnq_m_u8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vmvnq_s16(int16x8_t __p0)
{
    return __builtin_mve_vmvnq_s16(__p0);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vmvnq_s32(int32x4_t __p0)
{
    return __builtin_mve_vmvnq_s32(__p0);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vmvnq_s8(int8x16_t __p0)
{
    return __builtin_mve_vmvnq_s8(__p0);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vmvnq_u16(uint16x8_t __p0)
{
    return __builtin_mve_vmvnq_u16(__p0);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vmvnq_u32(uint32x4_t __p0)
{
    return __builtin_mve_vmvnq_u32(__p0);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vmvnq_u8(uint8x16_t __p0)
{
    return __builtin_mve_vmvnq_u8(__p0);
}

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

static __attribute__((__always_inline__))
float16x8_t __arm_vnegq_f16(float16x8_t __p0)
{
    return __builtin_mve_vnegq_f16(__p0);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vnegq_f32(float32x4_t __p0)
{
    return __builtin_mve_vnegq_f32(__p0);
}

static __attribute__((__always_inline__))
float16x8_t __arm_vnegq_m_f16(float16x8_t __p0, float16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vnegq_m_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vnegq_m_f32(float32x4_t __p0, float32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vnegq_m_f32(__p0, __p1, __p2);
}

#endif /* MVE floating point */

static __attribute__((__always_inline__))
int16x8_t __arm_vnegq_m_s16(int16x8_t __p0, int16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vnegq_m_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vnegq_m_s32(int32x4_t __p0, int32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vnegq_m_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vnegq_m_s8(int8x16_t __p0, int8x16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vnegq_m_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vnegq_s16(int16x8_t __p0)
{
    return __builtin_mve_vnegq_s16(__p0);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vnegq_s32(int32x4_t __p0)
{
    return __builtin_mve_vnegq_s32(__p0);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vnegq_s8(int8x16_t __p0)
{
    return __builtin_mve_vnegq_s8(__p0);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqabsq_m_s16(int16x8_t __p0, int16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vqabsq_m_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqabsq_m_s32(int32x4_t __p0, int32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vqabsq_m_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqabsq_m_s8(int8x16_t __p0, int8x16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vqabsq_m_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqabsq_s16(int16x8_t __p0)
{
    return __builtin_mve_vqabsq_s16(__p0);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqabsq_s32(int32x4_t __p0)
{
    return __builtin_mve_vqabsq_s32(__p0);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqabsq_s8(int8x16_t __p0)
{
    return __builtin_mve_vqabsq_s8(__p0);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqaddq_m_n_s16(int16x8_t __p0, int16x8_t __p1, int16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqaddq_m_n_s16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqaddq_m_n_s32(int32x4_t __p0, int32x4_t __p1, int32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqaddq_m_n_s32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqaddq_m_n_s8(int8x16_t __p0, int8x16_t __p1, int8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqaddq_m_n_s8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vqaddq_m_n_u16(uint16x8_t __p0, uint16x8_t __p1, uint16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqaddq_m_n_u16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vqaddq_m_n_u32(uint32x4_t __p0, uint32x4_t __p1, uint32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqaddq_m_n_u32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vqaddq_m_n_u8(uint8x16_t __p0, uint8x16_t __p1, uint8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqaddq_m_n_u8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqaddq_n_s16(int16x8_t __p0, int16_t __p1)
{
    return __builtin_mve_vqaddq_n_s16(__p0, __p1);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqaddq_n_s32(int32x4_t __p0, int32_t __p1)
{
    return __builtin_mve_vqaddq_n_s32(__p0, __p1);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqaddq_n_s8(int8x16_t __p0, int8_t __p1)
{
    return __builtin_mve_vqaddq_n_s8(__p0, __p1);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vqaddq_n_u16(uint16x8_t __p0, uint16_t __p1)
{
    return __builtin_mve_vqaddq_n_u16(__p0, __p1);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vqaddq_n_u32(uint32x4_t __p0, uint32_t __p1)
{
    return __builtin_mve_vqaddq_n_u32(__p0, __p1);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vqaddq_n_u8(uint8x16_t __p0, uint8_t __p1)
{
    return __builtin_mve_vqaddq_n_u8(__p0, __p1);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqdmladhq_m_s16(int16x8_t __p0, int16x8_t __p1, int16x8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqdmladhq_m_s16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqdmladhq_m_s32(int32x4_t __p0, int32x4_t __p1, int32x4_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqdmladhq_m_s32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqdmladhq_m_s8(int8x16_t __p0, int8x16_t __p1, int8x16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqdmladhq_m_s8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqdmladhq_s16(int16x8_t __p0, int16x8_t __p1, int16x8_t __p2)
{
    return __builtin_mve_vqdmladhq_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqdmladhq_s32(int32x4_t __p0, int32x4_t __p1, int32x4_t __p2)
{
    return __builtin_mve_vqdmladhq_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqdmladhq_s8(int8x16_t __p0, int8x16_t __p1, int8x16_t __p2)
{
    return __builtin_mve_vqdmladhq_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqdmladhxq_m_s16(int16x8_t __p0, int16x8_t __p1, int16x8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqdmladhxq_m_s16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqdmladhxq_m_s32(int32x4_t __p0, int32x4_t __p1, int32x4_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqdmladhxq_m_s32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqdmladhxq_m_s8(int8x16_t __p0, int8x16_t __p1, int8x16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqdmladhxq_m_s8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqdmladhxq_s16(int16x8_t __p0, int16x8_t __p1, int16x8_t __p2)
{
    return __builtin_mve_vqdmladhxq_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqdmladhxq_s32(int32x4_t __p0, int32x4_t __p1, int32x4_t __p2)
{
    return __builtin_mve_vqdmladhxq_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqdmladhxq_s8(int8x16_t __p0, int8x16_t __p1, int8x16_t __p2)
{
    return __builtin_mve_vqdmladhxq_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqdmlahq_m_n_s16(int16x8_t __p0, int16x8_t __p1, int16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqdmlahq_m_n_s16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqdmlahq_m_n_s32(int32x4_t __p0, int32x4_t __p1, int32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqdmlahq_m_n_s32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqdmlahq_m_n_s8(int8x16_t __p0, int8x16_t __p1, int8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqdmlahq_m_n_s8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqdmlahq_n_s16(int16x8_t __p0, int16x8_t __p1, int16_t __p2)
{
    return __builtin_mve_vqdmlahq_n_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqdmlahq_n_s32(int32x4_t __p0, int32x4_t __p1, int32_t __p2)
{
    return __builtin_mve_vqdmlahq_n_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqdmlahq_n_s8(int8x16_t __p0, int8x16_t __p1, int8_t __p2)
{
    return __builtin_mve_vqdmlahq_n_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqdmlsdhq_m_s16(int16x8_t __p0, int16x8_t __p1, int16x8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqdmlsdhq_m_s16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqdmlsdhq_m_s32(int32x4_t __p0, int32x4_t __p1, int32x4_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqdmlsdhq_m_s32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqdmlsdhq_m_s8(int8x16_t __p0, int8x16_t __p1, int8x16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqdmlsdhq_m_s8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqdmlsdhq_s16(int16x8_t __p0, int16x8_t __p1, int16x8_t __p2)
{
    return __builtin_mve_vqdmlsdhq_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqdmlsdhq_s32(int32x4_t __p0, int32x4_t __p1, int32x4_t __p2)
{
    return __builtin_mve_vqdmlsdhq_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqdmlsdhq_s8(int8x16_t __p0, int8x16_t __p1, int8x16_t __p2)
{
    return __builtin_mve_vqdmlsdhq_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqdmlsdhxq_m_s16(int16x8_t __p0, int16x8_t __p1, int16x8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqdmlsdhxq_m_s16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqdmlsdhxq_m_s32(int32x4_t __p0, int32x4_t __p1, int32x4_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqdmlsdhxq_m_s32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqdmlsdhxq_m_s8(int8x16_t __p0, int8x16_t __p1, int8x16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqdmlsdhxq_m_s8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqdmlsdhxq_s16(int16x8_t __p0, int16x8_t __p1, int16x8_t __p2)
{
    return __builtin_mve_vqdmlsdhxq_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqdmlsdhxq_s32(int32x4_t __p0, int32x4_t __p1, int32x4_t __p2)
{
    return __builtin_mve_vqdmlsdhxq_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqdmlsdhxq_s8(int8x16_t __p0, int8x16_t __p1, int8x16_t __p2)
{
    return __builtin_mve_vqdmlsdhxq_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqdmulhq_m_n_s16(int16x8_t __p0, int16x8_t __p1, int16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqdmulhq_m_n_s16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqdmulhq_m_n_s32(int32x4_t __p0, int32x4_t __p1, int32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqdmulhq_m_n_s32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqdmulhq_m_n_s8(int8x16_t __p0, int8x16_t __p1, int8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqdmulhq_m_n_s8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqdmulhq_n_s16(int16x8_t __p0, int16_t __p1)
{
    return __builtin_mve_vqdmulhq_n_s16(__p0, __p1);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqdmulhq_n_s32(int32x4_t __p0, int32_t __p1)
{
    return __builtin_mve_vqdmulhq_n_s32(__p0, __p1);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqdmulhq_n_s8(int8x16_t __p0, int8_t __p1)
{
    return __builtin_mve_vqdmulhq_n_s8(__p0, __p1);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqdmullbq_m_n_s16(int32x4_t __p0, int16x8_t __p1, int16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqdmullbq_m_n_s16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int64x2_t __arm_vqdmullbq_m_n_s32(int64x2_t __p0, int32x4_t __p1, int32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqdmullbq_m_n_s32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqdmullbq_m_s16(int32x4_t __p0, int16x8_t __p1, int16x8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqdmullbq_m_s16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int64x2_t __arm_vqdmullbq_m_s32(int64x2_t __p0, int32x4_t __p1, int32x4_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqdmullbq_m_s32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqdmullbq_n_s16(int16x8_t __p0, int16_t __p1)
{
    return __builtin_mve_vqdmullbq_n_s16(__p0, __p1);
}

static __attribute__((__always_inline__))
int64x2_t __arm_vqdmullbq_n_s32(int32x4_t __p0, int32_t __p1)
{
    return __builtin_mve_vqdmullbq_n_s32(__p0, __p1);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqdmullbq_s16(int16x8_t __p0, int16x8_t __p1)
{
    return __builtin_mve_vqdmullbq_s16(__p0, __p1);
}

static __attribute__((__always_inline__))
int64x2_t __arm_vqdmullbq_s32(int32x4_t __p0, int32x4_t __p1)
{
    return __builtin_mve_vqdmullbq_s32(__p0, __p1);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqdmulltq_m_n_s16(int32x4_t __p0, int16x8_t __p1, int16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqdmulltq_m_n_s16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int64x2_t __arm_vqdmulltq_m_n_s32(int64x2_t __p0, int32x4_t __p1, int32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqdmulltq_m_n_s32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqdmulltq_m_s16(int32x4_t __p0, int16x8_t __p1, int16x8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqdmulltq_m_s16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int64x2_t __arm_vqdmulltq_m_s32(int64x2_t __p0, int32x4_t __p1, int32x4_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqdmulltq_m_s32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqdmulltq_n_s16(int16x8_t __p0, int16_t __p1)
{
    return __builtin_mve_vqdmulltq_n_s16(__p0, __p1);
}

static __attribute__((__always_inline__))
int64x2_t __arm_vqdmulltq_n_s32(int32x4_t __p0, int32_t __p1)
{
    return __builtin_mve_vqdmulltq_n_s32(__p0, __p1);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqdmulltq_s16(int16x8_t __p0, int16x8_t __p1)
{
    return __builtin_mve_vqdmulltq_s16(__p0, __p1);
}

static __attribute__((__always_inline__))
int64x2_t __arm_vqdmulltq_s32(int32x4_t __p0, int32x4_t __p1)
{
    return __builtin_mve_vqdmulltq_s32(__p0, __p1);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqmovnbq_m_s16(int8x16_t __p0, int16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vqmovnbq_m_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqmovnbq_m_s32(int16x8_t __p0, int32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vqmovnbq_m_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vqmovnbq_m_u16(uint8x16_t __p0, uint16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vqmovnbq_m_u16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vqmovnbq_m_u32(uint16x8_t __p0, uint32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vqmovnbq_m_u32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqmovnbq_s16(int8x16_t __p0, int16x8_t __p1)
{
    return __builtin_mve_vqmovnbq_s16(__p0, __p1);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqmovnbq_s32(int16x8_t __p0, int32x4_t __p1)
{
    return __builtin_mve_vqmovnbq_s32(__p0, __p1);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vqmovnbq_u16(uint8x16_t __p0, uint16x8_t __p1)
{
    return __builtin_mve_vqmovnbq_u16(__p0, __p1);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vqmovnbq_u32(uint16x8_t __p0, uint32x4_t __p1)
{
    return __builtin_mve_vqmovnbq_u32(__p0, __p1);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqmovntq_m_s16(int8x16_t __p0, int16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vqmovntq_m_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqmovntq_m_s32(int16x8_t __p0, int32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vqmovntq_m_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vqmovntq_m_u16(uint8x16_t __p0, uint16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vqmovntq_m_u16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vqmovntq_m_u32(uint16x8_t __p0, uint32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vqmovntq_m_u32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqmovntq_s16(int8x16_t __p0, int16x8_t __p1)
{
    return __builtin_mve_vqmovntq_s16(__p0, __p1);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqmovntq_s32(int16x8_t __p0, int32x4_t __p1)
{
    return __builtin_mve_vqmovntq_s32(__p0, __p1);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vqmovntq_u16(uint8x16_t __p0, uint16x8_t __p1)
{
    return __builtin_mve_vqmovntq_u16(__p0, __p1);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vqmovntq_u32(uint16x8_t __p0, uint32x4_t __p1)
{
    return __builtin_mve_vqmovntq_u32(__p0, __p1);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vqmovunbq_m_s16(uint8x16_t __p0, int16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vqmovunbq_m_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vqmovunbq_m_s32(uint16x8_t __p0, int32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vqmovunbq_m_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vqmovunbq_s16(uint8x16_t __p0, int16x8_t __p1)
{
    return __builtin_mve_vqmovunbq_s16(__p0, __p1);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vqmovunbq_s32(uint16x8_t __p0, int32x4_t __p1)
{
    return __builtin_mve_vqmovunbq_s32(__p0, __p1);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vqmovuntq_m_s16(uint8x16_t __p0, int16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vqmovuntq_m_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vqmovuntq_m_s32(uint16x8_t __p0, int32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vqmovuntq_m_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vqmovuntq_s16(uint8x16_t __p0, int16x8_t __p1)
{
    return __builtin_mve_vqmovuntq_s16(__p0, __p1);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vqmovuntq_s32(uint16x8_t __p0, int32x4_t __p1)
{
    return __builtin_mve_vqmovuntq_s32(__p0, __p1);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqnegq_m_s16(int16x8_t __p0, int16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vqnegq_m_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqnegq_m_s32(int32x4_t __p0, int32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vqnegq_m_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqnegq_m_s8(int8x16_t __p0, int8x16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vqnegq_m_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqnegq_s16(int16x8_t __p0)
{
    return __builtin_mve_vqnegq_s16(__p0);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqnegq_s32(int32x4_t __p0)
{
    return __builtin_mve_vqnegq_s32(__p0);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqnegq_s8(int8x16_t __p0)
{
    return __builtin_mve_vqnegq_s8(__p0);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqrdmladhq_m_s16(int16x8_t __p0, int16x8_t __p1, int16x8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqrdmladhq_m_s16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqrdmladhq_m_s32(int32x4_t __p0, int32x4_t __p1, int32x4_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqrdmladhq_m_s32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqrdmladhq_m_s8(int8x16_t __p0, int8x16_t __p1, int8x16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqrdmladhq_m_s8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqrdmladhq_s16(int16x8_t __p0, int16x8_t __p1, int16x8_t __p2)
{
    return __builtin_mve_vqrdmladhq_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqrdmladhq_s32(int32x4_t __p0, int32x4_t __p1, int32x4_t __p2)
{
    return __builtin_mve_vqrdmladhq_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqrdmladhq_s8(int8x16_t __p0, int8x16_t __p1, int8x16_t __p2)
{
    return __builtin_mve_vqrdmladhq_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqrdmladhxq_m_s16(int16x8_t __p0, int16x8_t __p1, int16x8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqrdmladhxq_m_s16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqrdmladhxq_m_s32(int32x4_t __p0, int32x4_t __p1, int32x4_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqrdmladhxq_m_s32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqrdmladhxq_m_s8(int8x16_t __p0, int8x16_t __p1, int8x16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqrdmladhxq_m_s8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqrdmladhxq_s16(int16x8_t __p0, int16x8_t __p1, int16x8_t __p2)
{
    return __builtin_mve_vqrdmladhxq_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqrdmladhxq_s32(int32x4_t __p0, int32x4_t __p1, int32x4_t __p2)
{
    return __builtin_mve_vqrdmladhxq_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqrdmladhxq_s8(int8x16_t __p0, int8x16_t __p1, int8x16_t __p2)
{
    return __builtin_mve_vqrdmladhxq_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqrdmlahq_m_n_s16(int16x8_t __p0, int16x8_t __p1, int16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqrdmlahq_m_n_s16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqrdmlahq_m_n_s32(int32x4_t __p0, int32x4_t __p1, int32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqrdmlahq_m_n_s32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqrdmlahq_m_n_s8(int8x16_t __p0, int8x16_t __p1, int8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqrdmlahq_m_n_s8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqrdmlahq_n_s16(int16x8_t __p0, int16x8_t __p1, int16_t __p2)
{
    return __builtin_mve_vqrdmlahq_n_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqrdmlahq_n_s32(int32x4_t __p0, int32x4_t __p1, int32_t __p2)
{
    return __builtin_mve_vqrdmlahq_n_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqrdmlahq_n_s8(int8x16_t __p0, int8x16_t __p1, int8_t __p2)
{
    return __builtin_mve_vqrdmlahq_n_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqrdmlashq_m_n_s16(int16x8_t __p0, int16x8_t __p1, int16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqrdmlashq_m_n_s16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqrdmlashq_m_n_s32(int32x4_t __p0, int32x4_t __p1, int32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqrdmlashq_m_n_s32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqrdmlashq_m_n_s8(int8x16_t __p0, int8x16_t __p1, int8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqrdmlashq_m_n_s8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqrdmlashq_n_s16(int16x8_t __p0, int16x8_t __p1, int16_t __p2)
{
    return __builtin_mve_vqrdmlashq_n_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqrdmlashq_n_s32(int32x4_t __p0, int32x4_t __p1, int32_t __p2)
{
    return __builtin_mve_vqrdmlashq_n_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqrdmlashq_n_s8(int8x16_t __p0, int8x16_t __p1, int8_t __p2)
{
    return __builtin_mve_vqrdmlashq_n_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqrdmlsdhq_m_s16(int16x8_t __p0, int16x8_t __p1, int16x8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqrdmlsdhq_m_s16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqrdmlsdhq_m_s32(int32x4_t __p0, int32x4_t __p1, int32x4_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqrdmlsdhq_m_s32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqrdmlsdhq_m_s8(int8x16_t __p0, int8x16_t __p1, int8x16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqrdmlsdhq_m_s8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqrdmlsdhq_s16(int16x8_t __p0, int16x8_t __p1, int16x8_t __p2)
{
    return __builtin_mve_vqrdmlsdhq_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqrdmlsdhq_s32(int32x4_t __p0, int32x4_t __p1, int32x4_t __p2)
{
    return __builtin_mve_vqrdmlsdhq_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqrdmlsdhq_s8(int8x16_t __p0, int8x16_t __p1, int8x16_t __p2)
{
    return __builtin_mve_vqrdmlsdhq_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqrdmlsdhxq_m_s16(int16x8_t __p0, int16x8_t __p1, int16x8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqrdmlsdhxq_m_s16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqrdmlsdhxq_m_s32(int32x4_t __p0, int32x4_t __p1, int32x4_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqrdmlsdhxq_m_s32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqrdmlsdhxq_m_s8(int8x16_t __p0, int8x16_t __p1, int8x16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqrdmlsdhxq_m_s8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqrdmlsdhxq_s16(int16x8_t __p0, int16x8_t __p1, int16x8_t __p2)
{
    return __builtin_mve_vqrdmlsdhxq_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqrdmlsdhxq_s32(int32x4_t __p0, int32x4_t __p1, int32x4_t __p2)
{
    return __builtin_mve_vqrdmlsdhxq_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqrdmlsdhxq_s8(int8x16_t __p0, int8x16_t __p1, int8x16_t __p2)
{
    return __builtin_mve_vqrdmlsdhxq_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqrdmulhq_m_n_s16(int16x8_t __p0, int16x8_t __p1, int16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqrdmulhq_m_n_s16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqrdmulhq_m_n_s32(int32x4_t __p0, int32x4_t __p1, int32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqrdmulhq_m_n_s32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqrdmulhq_m_n_s8(int8x16_t __p0, int8x16_t __p1, int8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqrdmulhq_m_n_s8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqrdmulhq_n_s16(int16x8_t __p0, int16_t __p1)
{
    return __builtin_mve_vqrdmulhq_n_s16(__p0, __p1);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqrdmulhq_n_s32(int32x4_t __p0, int32_t __p1)
{
    return __builtin_mve_vqrdmulhq_n_s32(__p0, __p1);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqrdmulhq_n_s8(int8x16_t __p0, int8_t __p1)
{
    return __builtin_mve_vqrdmulhq_n_s8(__p0, __p1);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqsubq_m_n_s16(int16x8_t __p0, int16x8_t __p1, int16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqsubq_m_n_s16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqsubq_m_n_s32(int32x4_t __p0, int32x4_t __p1, int32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqsubq_m_n_s32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqsubq_m_n_s8(int8x16_t __p0, int8x16_t __p1, int8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqsubq_m_n_s8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vqsubq_m_n_u16(uint16x8_t __p0, uint16x8_t __p1, uint16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqsubq_m_n_u16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vqsubq_m_n_u32(uint32x4_t __p0, uint32x4_t __p1, uint32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqsubq_m_n_u32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vqsubq_m_n_u8(uint8x16_t __p0, uint8x16_t __p1, uint8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vqsubq_m_n_u8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vqsubq_n_s16(int16x8_t __p0, int16_t __p1)
{
    return __builtin_mve_vqsubq_n_s16(__p0, __p1);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vqsubq_n_s32(int32x4_t __p0, int32_t __p1)
{
    return __builtin_mve_vqsubq_n_s32(__p0, __p1);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vqsubq_n_s8(int8x16_t __p0, int8_t __p1)
{
    return __builtin_mve_vqsubq_n_s8(__p0, __p1);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vqsubq_n_u16(uint16x8_t __p0, uint16_t __p1)
{
    return __builtin_mve_vqsubq_n_u16(__p0, __p1);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vqsubq_n_u32(uint32x4_t __p0, uint32_t __p1)
{
    return __builtin_mve_vqsubq_n_u32(__p0, __p1);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vqsubq_n_u8(uint8x16_t __p0, uint8_t __p1)
{
    return __builtin_mve_vqsubq_n_u8(__p0, __p1);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vrev16q_m_s8(int8x16_t __p0, int8x16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vrev16q_m_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vrev16q_m_u8(uint8x16_t __p0, uint8x16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vrev16q_m_u8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vrev16q_s8(int8x16_t __p0)
{
    return __builtin_mve_vrev16q_s8(__p0);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vrev16q_u8(uint8x16_t __p0)
{
    return __builtin_mve_vrev16q_u8(__p0);
}

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

static __attribute__((__always_inline__))
float16x8_t __arm_vrev32q_f16(float16x8_t __p0)
{
    return __builtin_mve_vrev32q_f16(__p0);
}

static __attribute__((__always_inline__))
float16x8_t __arm_vrev32q_m_f16(float16x8_t __p0, float16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vrev32q_m_f16(__p0, __p1, __p2);
}

#endif /* MVE floating point */

static __attribute__((__always_inline__))
int16x8_t __arm_vrev32q_m_s16(int16x8_t __p0, int16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vrev32q_m_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vrev32q_m_s8(int8x16_t __p0, int8x16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vrev32q_m_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vrev32q_m_u16(uint16x8_t __p0, uint16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vrev32q_m_u16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vrev32q_m_u8(uint8x16_t __p0, uint8x16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vrev32q_m_u8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vrev32q_s16(int16x8_t __p0)
{
    return __builtin_mve_vrev32q_s16(__p0);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vrev32q_s8(int8x16_t __p0)
{
    return __builtin_mve_vrev32q_s8(__p0);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vrev32q_u16(uint16x8_t __p0)
{
    return __builtin_mve_vrev32q_u16(__p0);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vrev32q_u8(uint8x16_t __p0)
{
    return __builtin_mve_vrev32q_u8(__p0);
}

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

static __attribute__((__always_inline__))
float16x8_t __arm_vrev64q_f16(float16x8_t __p0)
{
    return __builtin_mve_vrev64q_f16(__p0);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vrev64q_f32(float32x4_t __p0)
{
    return __builtin_mve_vrev64q_f32(__p0);
}

static __attribute__((__always_inline__))
float16x8_t __arm_vrev64q_m_f16(float16x8_t __p0, float16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vrev64q_m_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vrev64q_m_f32(float32x4_t __p0, float32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vrev64q_m_f32(__p0, __p1, __p2);
}

#endif /* MVE floating point */

static __attribute__((__always_inline__))
int16x8_t __arm_vrev64q_m_s16(int16x8_t __p0, int16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vrev64q_m_s16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vrev64q_m_s32(int32x4_t __p0, int32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vrev64q_m_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vrev64q_m_s8(int8x16_t __p0, int8x16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vrev64q_m_s8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vrev64q_m_u16(uint16x8_t __p0, uint16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vrev64q_m_u16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vrev64q_m_u32(uint32x4_t __p0, uint32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vrev64q_m_u32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vrev64q_m_u8(uint8x16_t __p0, uint8x16_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vrev64q_m_u8(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int16x8_t __arm_vrev64q_s16(int16x8_t __p0)
{
    return __builtin_mve_vrev64q_s16(__p0);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vrev64q_s32(int32x4_t __p0)
{
    return __builtin_mve_vrev64q_s32(__p0);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vrev64q_s8(int8x16_t __p0)
{
    return __builtin_mve_vrev64q_s8(__p0);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vrev64q_u16(uint16x8_t __p0)
{
    return __builtin_mve_vrev64q_u16(__p0);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vrev64q_u32(uint32x4_t __p0)
{
    return __builtin_mve_vrev64q_u32(__p0);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vrev64q_u8(uint8x16_t __p0)
{
    return __builtin_mve_vrev64q_u8(__p0);
}

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

static __attribute__((__always_inline__))
float16x8_t __arm_vrndaq_f16(float16x8_t __p0)
{
    return __builtin_mve_vrndaq_f16(__p0);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vrndaq_f32(float32x4_t __p0)
{
    return __builtin_mve_vrndaq_f32(__p0);
}

static __attribute__((__always_inline__))
float16x8_t __arm_vrndaq_m_f16(float16x8_t __p0, float16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vrndaq_m_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vrndaq_m_f32(float32x4_t __p0, float32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vrndaq_m_f32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float16x8_t __arm_vrndmq_f16(float16x8_t __p0)
{
    return __builtin_mve_vrndmq_f16(__p0);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vrndmq_f32(float32x4_t __p0)
{
    return __builtin_mve_vrndmq_f32(__p0);
}

static __attribute__((__always_inline__))
float16x8_t __arm_vrndmq_m_f16(float16x8_t __p0, float16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vrndmq_m_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vrndmq_m_f32(float32x4_t __p0, float32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vrndmq_m_f32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float16x8_t __arm_vrndnq_f16(float16x8_t __p0)
{
    return __builtin_mve_vrndnq_f16(__p0);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vrndnq_f32(float32x4_t __p0)
{
    return __builtin_mve_vrndnq_f32(__p0);
}

static __attribute__((__always_inline__))
float16x8_t __arm_vrndnq_m_f16(float16x8_t __p0, float16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vrndnq_m_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vrndnq_m_f32(float32x4_t __p0, float32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vrndnq_m_f32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float16x8_t __arm_vrndpq_f16(float16x8_t __p0)
{
    return __builtin_mve_vrndpq_f16(__p0);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vrndpq_f32(float32x4_t __p0)
{
    return __builtin_mve_vrndpq_f32(__p0);
}

static __attribute__((__always_inline__))
float16x8_t __arm_vrndpq_m_f16(float16x8_t __p0, float16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vrndpq_m_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vrndpq_m_f32(float32x4_t __p0, float32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vrndpq_m_f32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float16x8_t __arm_vrndq_f16(float16x8_t __p0)
{
    return __builtin_mve_vrndq_f16(__p0);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vrndq_f32(float32x4_t __p0)
{
    return __builtin_mve_vrndq_f32(__p0);
}

static __attribute__((__always_inline__))
float16x8_t __arm_vrndq_m_f16(float16x8_t __p0, float16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vrndq_m_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vrndq_m_f32(float32x4_t __p0, float32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vrndq_m_f32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float16x8_t __arm_vrndxq_f16(float16x8_t __p0)
{
    return __builtin_mve_vrndxq_f16(__p0);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vrndxq_f32(float32x4_t __p0)
{
    return __builtin_mve_vrndxq_f32(__p0);
}

static __attribute__((__always_inline__))
float16x8_t __arm_vrndxq_m_f16(float16x8_t __p0, float16x8_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vrndxq_m_f16(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vrndxq_m_f32(float32x4_t __p0, float32x4_t __p1, mve_pred16_t __p2)
{
    return __builtin_mve_vrndxq_m_f32(__p0, __p1, __p2);
}

#endif /* MVE floating point */

static __attribute__((__always_inline__))
int32x4_t __arm_vsbciq_m_s32(int32x4_t __p0, int32x4_t __p1, int32x4_t __p2, uint32_t *__p3, mve_pred16_t __p4)
{
    return __builtin_mve_vsbciq_m_s32(__p0, __p1, __p2, __p3, __p4);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vsbciq_m_u32(uint32x4_t __p0, uint32x4_t __p1, uint32x4_t __p2, uint32_t *__p3, mve_pred16_t __p4)
{
    return __builtin_mve_vsbciq_m_u32(__p0, __p1, __p2, __p3, __p4);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vsbciq_s32(int32x4_t __p0, int32x4_t __p1, uint32_t *__p2)
{
    return __builtin_mve_vsbciq_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vsbciq_u32(uint32x4_t __p0, uint32x4_t __p1, uint32_t *__p2)
{
    return __builtin_mve_vsbciq_u32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vsbcq_m_s32(int32x4_t __p0, int32x4_t __p1, int32x4_t __p2, uint32_t *__p3, mve_pred16_t __p4)
{
    return __builtin_mve_vsbcq_m_s32(__p0, __p1, __p2, __p3, __p4);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vsbcq_m_u32(uint32x4_t __p0, uint32x4_t __p1, uint32x4_t __p2, uint32_t *__p3, mve_pred16_t __p4)
{
    return __builtin_mve_vsbcq_m_u32(__p0, __p1, __p2, __p3, __p4);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vsbcq_s32(int32x4_t __p0, int32x4_t __p1, uint32_t *__p2)
{
    return __builtin_mve_vsbcq_s32(__p0, __p1, __p2);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vsbcq_u32(uint32x4_t __p0, uint32x4_t __p1, uint32_t *__p2)
{
    return __builtin_mve_vsbcq_u32(__p0, __p1, __p2);
}

#define __arm_vshlcq_m_s16(__p0, __p1, __p2, __p3) ({ \
    __builtin_mve_vshlcq_m_s16(__p0, __p1, __p2, __p3); \
})

#define __arm_vshlcq_m_s32(__p0, __p1, __p2, __p3) ({ \
    __builtin_mve_vshlcq_m_s32(__p0, __p1, __p2, __p3); \
})

#define __arm_vshlcq_m_s8(__p0, __p1, __p2, __p3) ({ \
    __builtin_mve_vshlcq_m_s8(__p0, __p1, __p2, __p3); \
})

#define __arm_vshlcq_m_u16(__p0, __p1, __p2, __p3) ({ \
    __builtin_mve_vshlcq_m_u16(__p0, __p1, __p2, __p3); \
})

#define __arm_vshlcq_m_u32(__p0, __p1, __p2, __p3) ({ \
    __builtin_mve_vshlcq_m_u32(__p0, __p1, __p2, __p3); \
})

#define __arm_vshlcq_m_u8(__p0, __p1, __p2, __p3) ({ \
    __builtin_mve_vshlcq_m_u8(__p0, __p1, __p2, __p3); \
})

#define __arm_vshlcq_s16(__p0, __p1, __p2) ({ \
    __builtin_mve_vshlcq_s16(__p0, __p1, __p2); \
})

#define __arm_vshlcq_s32(__p0, __p1, __p2) ({ \
    __builtin_mve_vshlcq_s32(__p0, __p1, __p2); \
})

#define __arm_vshlcq_s8(__p0, __p1, __p2) ({ \
    __builtin_mve_vshlcq_s8(__p0, __p1, __p2); \
})

#define __arm_vshlcq_u16(__p0, __p1, __p2) ({ \
    __builtin_mve_vshlcq_u16(__p0, __p1, __p2); \
})

#define __arm_vshlcq_u32(__p0, __p1, __p2) ({ \
    __builtin_mve_vshlcq_u32(__p0, __p1, __p2); \
})

#define __arm_vshlcq_u8(__p0, __p1, __p2) ({ \
    __builtin_mve_vshlcq_u8(__p0, __p1, __p2); \
})

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

static __attribute__((__always_inline__))
float16x8_t __arm_vsubq_m_n_f16(float16x8_t __p0, float16x8_t __p1, float16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vsubq_m_n_f16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vsubq_m_n_f32(float32x4_t __p0, float32x4_t __p1, float32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vsubq_m_n_f32(__p0, __p1, __p2, __p3);
}

#endif /* MVE floating point */

static __attribute__((__always_inline__))
int16x8_t __arm_vsubq_m_n_s16(int16x8_t __p0, int16x8_t __p1, int16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vsubq_m_n_s16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vsubq_m_n_s32(int32x4_t __p0, int32x4_t __p1, int32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vsubq_m_n_s32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vsubq_m_n_s8(int8x16_t __p0, int8x16_t __p1, int8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vsubq_m_n_s8(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vsubq_m_n_u16(uint16x8_t __p0, uint16x8_t __p1, uint16_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vsubq_m_n_u16(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vsubq_m_n_u32(uint32x4_t __p0, uint32x4_t __p1, uint32_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vsubq_m_n_u32(__p0, __p1, __p2, __p3);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vsubq_m_n_u8(uint8x16_t __p0, uint8x16_t __p1, uint8_t __p2, mve_pred16_t __p3)
{
    return __builtin_mve_vsubq_m_n_u8(__p0, __p1, __p2, __p3);
}

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

static __attribute__((__always_inline__))
float16x8_t __arm_vsubq_n_f16(float16x8_t __p0, float16_t __p1)
{
    return __builtin_mve_vsubq_n_f16(__p0, __p1);
}

static __attribute__((__always_inline__))
float32x4_t __arm_vsubq_n_f32(float32x4_t __p0, float32_t __p1)
{
    return __builtin_mve_vsubq_n_f32(__p0, __p1);
}

#endif /* MVE floating point */

static __attribute__((__always_inline__))
int16x8_t __arm_vsubq_n_s16(int16x8_t __p0, int16_t __p1)
{
    return __builtin_mve_vsubq_n_s16(__p0, __p1);
}

static __attribute__((__always_inline__))
int32x4_t __arm_vsubq_n_s32(int32x4_t __p0, int32_t __p1)
{
    return __builtin_mve_vsubq_n_s32(__p0, __p1);
}

static __attribute__((__always_inline__))
int8x16_t __arm_vsubq_n_s8(int8x16_t __p0, int8_t __p1)
{
    return __builtin_mve_vsubq_n_s8(__p0, __p1);
}

static __attribute__((__always_inline__))
uint16x8_t __arm_vsubq_n_u16(uint16x8_t __p0, uint16_t __p1)
{
    return __builtin_mve_vsubq_n_u16(__p0, __p1);
}

static __attribute__((__always_inline__))
uint32x4_t __arm_vsubq_n_u32(uint32x4_t __p0, uint32_t __p1)
{
    return __builtin_mve_vsubq_n_u32(__p0, __p1);
}

static __attribute__((__always_inline__))
uint8x16_t __arm_vsubq_n_u8(uint8x16_t __p0, uint8_t __p1)
{
    return __builtin_mve_vsubq_n_u8(__p0, __p1);
}

extern void *__ARM_undef; /* for use in untaken _Generic branches */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __ARM_mve_typeof(param) __typeof(_Generic(param, \
    float16_t: 0.0, float: 0.0, double: 0.0, \
    int8_t: 0, uint8_t: 0, \
    int16_t: 0, uint16_t: 0, \
    int32_t: 0, uint32_t: 0, \
    int64_t: 0, uint64_t: 0, \
    default: _Generic(param, \
    signed char: 0, unsigned char: 0, \
    signed short: 0, unsigned short: 0, \
    signed int: 0, unsigned int: 0, \
    signed long: 0, unsigned long: 0, \
    signed long long: 0, unsigned long long: 0, \
    default: param)))

#else /* MVE floating point */

#define __ARM_mve_typeof(param) __typeof(_Generic(param, \
    int8_t: 0, uint8_t: 0, \
    int16_t: 0, uint16_t: 0, \
    int32_t: 0, uint32_t: 0, \
    int64_t: 0, uint64_t: 0, \
    default: _Generic(param, \
    signed char: 0, unsigned char: 0, \
    signed short: 0, unsigned short: 0, \
    signed int: 0, unsigned int: 0, \
    signed long: 0, unsigned long: 0, \
    signed long long: 0, unsigned long long: 0, \
    default: param)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vabsq(p0) _Generic( \
    (void (*)(__ARM_mve_typeof(p0)))0, \
     void (*)(float16x8_t): __arm_vabsq_f16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(float16x8_t): p0, default: *(float16x8_t *)__ARM_undef)), \
     void (*)(float32x4_t): __arm_vabsq_f32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(float32x4_t): p0, default: *(float32x4_t *)__ARM_undef)), \
     void (*)(int16x8_t): __arm_vabsq_s16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int16x8_t): p0, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t): __arm_vabsq_s32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int32x4_t): p0, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t): __arm_vabsq_s8(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int8x16_t): p0, default: *(int8x16_t *)__ARM_undef)))

#else /* MVE floating point */

#define __arm_vabsq(p0) _Generic( \
    (void (*)(__ARM_mve_typeof(p0)))0, \
     void (*)(int16x8_t): __arm_vabsq_s16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int16x8_t): p0, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t): __arm_vabsq_s32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int32x4_t): p0, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t): __arm_vabsq_s8(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int8x16_t): p0, default: *(int8x16_t *)__ARM_undef)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vabsq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(float16x8_t, float16x8_t, int): __arm_vabsq_m_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p2, default: 0)), \
     void (*)(float32x4_t, float32x4_t, int): __arm_vabsq_m_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, int): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, int): p2, default: 0)), \
     void (*)(int16x8_t, int16x8_t, int): __arm_vabsq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p2, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int): __arm_vabsq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p2, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int): __arm_vabsq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p2, default: 0)))

#else /* MVE floating point */

#define __arm_vabsq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, int16x8_t, int): __arm_vabsq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p2, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int): __arm_vabsq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p2, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int): __arm_vabsq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p2, default: 0)))

#endif /* MVE floating point */

#define __arm_vaddlvaq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int, int32x4_t): __arm_vaddlvaq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int32x4_t): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int, uint32x4_t): __arm_vaddlvaq_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, uint32x4_t): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, uint32x4_t): p1, default: *(uint32x4_t *)__ARM_undef)))

#define __arm_vaddlvaq_p(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int, int32x4_t, int): __arm_vaddlvaq_p_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int32x4_t, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int32x4_t, int): p2, default: 0)), \
     void (*)(int, uint32x4_t, int): __arm_vaddlvaq_p_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint32x4_t, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint32x4_t, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint32x4_t, int): p2, default: 0)))

#define __arm_vaddlvq(p0) _Generic( \
    (void (*)(__ARM_mve_typeof(p0)))0, \
     void (*)(int32x4_t): __arm_vaddlvq_s32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int32x4_t): p0, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(uint32x4_t): __arm_vaddlvq_u32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(uint32x4_t): p0, default: *(uint32x4_t *)__ARM_undef)))

#define __arm_vaddlvq_p(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int32x4_t, int): __arm_vaddlvq_p_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p1, default: 0)), \
     void (*)(uint32x4_t, int): __arm_vaddlvq_p_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p1, default: 0)))

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vaddq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(float16x8_t, float16x8_t): __arm_vaddq_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float16x8_t, float16x8_t): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float16x8_t, float16x8_t): p1, default: *(float16x8_t *)__ARM_undef)), \
     void (*)(float32x4_t, float32x4_t): __arm_vaddq_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float32x4_t, float32x4_t): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float32x4_t, float32x4_t): p1, default: *(float32x4_t *)__ARM_undef)), \
     void (*)(float16x8_t, double): __arm_vaddq_n_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float16x8_t, double): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float16x8_t, double): p1, default: 0.0)), \
     void (*)(float32x4_t, double): __arm_vaddq_n_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float32x4_t, double): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float32x4_t, double): p1, default: 0.0)), \
     void (*)(int16x8_t, int): __arm_vaddq_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p1, default: 0)), \
     void (*)(int32x4_t, int): __arm_vaddq_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p1, default: 0)), \
     void (*)(int8x16_t, int): __arm_vaddq_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p1, default: 0)), \
     void (*)(uint16x8_t, int): __arm_vaddq_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p1, default: 0)), \
     void (*)(uint32x4_t, int): __arm_vaddq_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p1, default: 0)), \
     void (*)(uint8x16_t, int): __arm_vaddq_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int): p1, default: 0)), \
     void (*)(int16x8_t, int16x8_t): __arm_vaddq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t, int32x4_t): __arm_vaddq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t, int8x16_t): __arm_vaddq_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int8x16_t): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int8x16_t): p1, default: *(int8x16_t *)__ARM_undef)), \
     void (*)(uint16x8_t, uint16x8_t): __arm_vaddq_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint16x8_t): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint16x8_t): p1, default: *(uint16x8_t *)__ARM_undef)), \
     void (*)(uint32x4_t, uint32x4_t): __arm_vaddq_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, uint32x4_t): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, uint32x4_t): p1, default: *(uint32x4_t *)__ARM_undef)), \
     void (*)(uint8x16_t, uint8x16_t): __arm_vaddq_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint8x16_t): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint8x16_t): p1, default: *(uint8x16_t *)__ARM_undef)))

#else /* MVE floating point */

#define __arm_vaddq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int16x8_t, int): __arm_vaddq_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p1, default: 0)), \
     void (*)(int32x4_t, int): __arm_vaddq_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p1, default: 0)), \
     void (*)(int8x16_t, int): __arm_vaddq_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p1, default: 0)), \
     void (*)(uint16x8_t, int): __arm_vaddq_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p1, default: 0)), \
     void (*)(uint32x4_t, int): __arm_vaddq_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p1, default: 0)), \
     void (*)(uint8x16_t, int): __arm_vaddq_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int): p1, default: 0)), \
     void (*)(int16x8_t, int16x8_t): __arm_vaddq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t, int32x4_t): __arm_vaddq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t, int8x16_t): __arm_vaddq_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int8x16_t): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int8x16_t): p1, default: *(int8x16_t *)__ARM_undef)), \
     void (*)(uint16x8_t, uint16x8_t): __arm_vaddq_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint16x8_t): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint16x8_t): p1, default: *(uint16x8_t *)__ARM_undef)), \
     void (*)(uint32x4_t, uint32x4_t): __arm_vaddq_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, uint32x4_t): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, uint32x4_t): p1, default: *(uint32x4_t *)__ARM_undef)), \
     void (*)(uint8x16_t, uint8x16_t): __arm_vaddq_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint8x16_t): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint8x16_t): p1, default: *(uint8x16_t *)__ARM_undef)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vaddq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(float16x8_t, float16x8_t, float16x8_t, int): __arm_vaddq_m_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, float16x8_t, int): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, float16x8_t, int): p2, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, float16x8_t, int): p3, default: 0)), \
     void (*)(float32x4_t, float32x4_t, float32x4_t, int): __arm_vaddq_m_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, float32x4_t, int): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, float32x4_t, int): p2, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, float32x4_t, int): p3, default: 0)), \
     void (*)(float16x8_t, float16x8_t, double, int): __arm_vaddq_m_n_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, double, int): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, double, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, double, int): p2, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, double, int): p3, default: 0)), \
     void (*)(float32x4_t, float32x4_t, double, int): __arm_vaddq_m_n_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, double, int): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, double, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, double, int): p2, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, double, int): p3, default: 0)), \
     void (*)(int16x8_t, int16x8_t, int, int): __arm_vaddq_m_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int, int): __arm_vaddq_m_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int, int): __arm_vaddq_m_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p3, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, int, int): __arm_vaddq_m_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p3, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, int, int): __arm_vaddq_m_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p3, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, int, int): __arm_vaddq_m_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p3, default: 0)), \
     void (*)(int16x8_t, int16x8_t, int16x8_t, int): __arm_vaddq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p2, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t, int): __arm_vaddq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p2, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t, int): __arm_vaddq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p2, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p3, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): __arm_vaddq_m_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p2, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p3, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): __arm_vaddq_m_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p2, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p3, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): __arm_vaddq_m_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p2, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p3, default: 0)))

#else /* MVE floating point */

#define __arm_vaddq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(int16x8_t, int16x8_t, int, int): __arm_vaddq_m_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int, int): __arm_vaddq_m_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int, int): __arm_vaddq_m_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p3, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, int, int): __arm_vaddq_m_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p3, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, int, int): __arm_vaddq_m_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p3, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, int, int): __arm_vaddq_m_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p3, default: 0)), \
     void (*)(int16x8_t, int16x8_t, int16x8_t, int): __arm_vaddq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p2, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t, int): __arm_vaddq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p2, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t, int): __arm_vaddq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p2, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p3, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): __arm_vaddq_m_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p2, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p3, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): __arm_vaddq_m_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p2, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p3, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): __arm_vaddq_m_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p2, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p3, default: 0)))

#endif /* MVE floating point */

#define __arm_vaddvaq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int, int16x8_t): __arm_vaddvaq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int16x8_t): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int, int32x4_t): __arm_vaddvaq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int32x4_t): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int, int8x16_t): __arm_vaddvaq_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int8x16_t): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int8x16_t): p1, default: *(int8x16_t *)__ARM_undef)), \
     void (*)(int, uint16x8_t): __arm_vaddvaq_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, uint16x8_t): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, uint16x8_t): p1, default: *(uint16x8_t *)__ARM_undef)), \
     void (*)(int, uint32x4_t): __arm_vaddvaq_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, uint32x4_t): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, uint32x4_t): p1, default: *(uint32x4_t *)__ARM_undef)), \
     void (*)(int, uint8x16_t): __arm_vaddvaq_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, uint8x16_t): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, uint8x16_t): p1, default: *(uint8x16_t *)__ARM_undef)))

#define __arm_vaddvaq_p(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int, int16x8_t, int): __arm_vaddvaq_p_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int16x8_t, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int16x8_t, int): p2, default: 0)), \
     void (*)(int, int32x4_t, int): __arm_vaddvaq_p_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int32x4_t, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int32x4_t, int): p2, default: 0)), \
     void (*)(int, int8x16_t, int): __arm_vaddvaq_p_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int8x16_t, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int8x16_t, int): p2, default: 0)), \
     void (*)(int, uint16x8_t, int): __arm_vaddvaq_p_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint16x8_t, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint16x8_t, int): p2, default: 0)), \
     void (*)(int, uint32x4_t, int): __arm_vaddvaq_p_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint32x4_t, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint32x4_t, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint32x4_t, int): p2, default: 0)), \
     void (*)(int, uint8x16_t, int): __arm_vaddvaq_p_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint8x16_t, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint8x16_t, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint8x16_t, int): p2, default: 0)))

#define __arm_vaddvq(p0) _Generic( \
    (void (*)(__ARM_mve_typeof(p0)))0, \
     void (*)(int16x8_t): __arm_vaddvq_s16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int16x8_t): p0, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t): __arm_vaddvq_s32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int32x4_t): p0, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t): __arm_vaddvq_s8(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int8x16_t): p0, default: *(int8x16_t *)__ARM_undef)), \
     void (*)(uint16x8_t): __arm_vaddvq_u16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(uint16x8_t): p0, default: *(uint16x8_t *)__ARM_undef)), \
     void (*)(uint32x4_t): __arm_vaddvq_u32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(uint32x4_t): p0, default: *(uint32x4_t *)__ARM_undef)), \
     void (*)(uint8x16_t): __arm_vaddvq_u8(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(uint8x16_t): p0, default: *(uint8x16_t *)__ARM_undef)))

#define __arm_vaddvq_p(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int16x8_t, int): __arm_vaddvq_p_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p1, default: 0)), \
     void (*)(int32x4_t, int): __arm_vaddvq_p_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p1, default: 0)), \
     void (*)(int8x16_t, int): __arm_vaddvq_p_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p1, default: 0)), \
     void (*)(uint16x8_t, int): __arm_vaddvq_p_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p1, default: 0)), \
     void (*)(uint32x4_t, int): __arm_vaddvq_p_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p1, default: 0)), \
     void (*)(uint8x16_t, int): __arm_vaddvq_p_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int): p1, default: 0)))

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vbrsrq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(float16x8_t, int): __arm_vbrsrq_n_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float16x8_t, int): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float16x8_t, int): p1, default: 0)), \
     void (*)(float32x4_t, int): __arm_vbrsrq_n_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float32x4_t, int): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float32x4_t, int): p1, default: 0)), \
     void (*)(int16x8_t, int): __arm_vbrsrq_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p1, default: 0)), \
     void (*)(int32x4_t, int): __arm_vbrsrq_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p1, default: 0)), \
     void (*)(int8x16_t, int): __arm_vbrsrq_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p1, default: 0)), \
     void (*)(uint16x8_t, int): __arm_vbrsrq_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p1, default: 0)), \
     void (*)(uint32x4_t, int): __arm_vbrsrq_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p1, default: 0)), \
     void (*)(uint8x16_t, int): __arm_vbrsrq_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int): p1, default: 0)))

#else /* MVE floating point */

#define __arm_vbrsrq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int16x8_t, int): __arm_vbrsrq_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p1, default: 0)), \
     void (*)(int32x4_t, int): __arm_vbrsrq_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p1, default: 0)), \
     void (*)(int8x16_t, int): __arm_vbrsrq_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p1, default: 0)), \
     void (*)(uint16x8_t, int): __arm_vbrsrq_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p1, default: 0)), \
     void (*)(uint32x4_t, int): __arm_vbrsrq_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p1, default: 0)), \
     void (*)(uint8x16_t, int): __arm_vbrsrq_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int): p1, default: 0)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vbrsrq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(float16x8_t, float16x8_t, int, int): __arm_vbrsrq_m_n_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, int, int): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, int, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, int, int): p3, default: 0)), \
     void (*)(float32x4_t, float32x4_t, int, int): __arm_vbrsrq_m_n_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, int, int): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, int, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, int, int): p3, default: 0)), \
     void (*)(int16x8_t, int16x8_t, int, int): __arm_vbrsrq_m_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int, int): __arm_vbrsrq_m_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int, int): __arm_vbrsrq_m_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p3, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, int, int): __arm_vbrsrq_m_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p3, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, int, int): __arm_vbrsrq_m_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p3, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, int, int): __arm_vbrsrq_m_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p3, default: 0)))

#else /* MVE floating point */

#define __arm_vbrsrq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(int16x8_t, int16x8_t, int, int): __arm_vbrsrq_m_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int, int): __arm_vbrsrq_m_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int, int): __arm_vbrsrq_m_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p3, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, int, int): __arm_vbrsrq_m_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p3, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, int, int): __arm_vbrsrq_m_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p3, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, int, int): __arm_vbrsrq_m_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p3, default: 0)))

#endif /* MVE floating point */

#define __arm_vclsq(p0) _Generic( \
    (void (*)(__ARM_mve_typeof(p0)))0, \
     void (*)(int16x8_t): __arm_vclsq_s16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int16x8_t): p0, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t): __arm_vclsq_s32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int32x4_t): p0, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t): __arm_vclsq_s8(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int8x16_t): p0, default: *(int8x16_t *)__ARM_undef)))

#define __arm_vclsq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, int16x8_t, int): __arm_vclsq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p2, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int): __arm_vclsq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p2, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int): __arm_vclsq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p2, default: 0)))

#define __arm_vclzq(p0) _Generic( \
    (void (*)(__ARM_mve_typeof(p0)))0, \
     void (*)(int16x8_t): __arm_vclzq_s16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int16x8_t): p0, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t): __arm_vclzq_s32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int32x4_t): p0, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t): __arm_vclzq_s8(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int8x16_t): p0, default: *(int8x16_t *)__ARM_undef)), \
     void (*)(uint16x8_t): __arm_vclzq_u16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(uint16x8_t): p0, default: *(uint16x8_t *)__ARM_undef)), \
     void (*)(uint32x4_t): __arm_vclzq_u32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(uint32x4_t): p0, default: *(uint32x4_t *)__ARM_undef)), \
     void (*)(uint8x16_t): __arm_vclzq_u8(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(uint8x16_t): p0, default: *(uint8x16_t *)__ARM_undef)))

#define __arm_vclzq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, int16x8_t, int): __arm_vclzq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p2, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int): __arm_vclzq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p2, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int): __arm_vclzq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p2, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, int): __arm_vclzq_m_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint16x8_t, int): p2, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, int): __arm_vclzq_m_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint32x4_t, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint32x4_t, int): p2, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, int): __arm_vclzq_m_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint8x16_t, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint8x16_t, int): p2, default: 0)))

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vcvtaq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, float16x8_t, int): __arm_vcvtaq_m_s16_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, float16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, float16x8_t, int): p2, default: 0)), \
     void (*)(int32x4_t, float32x4_t, int): __arm_vcvtaq_m_s32_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, float32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, float32x4_t, int): p2, default: 0)), \
     void (*)(uint16x8_t, float16x8_t, int): __arm_vcvtaq_m_u16_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, float16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, float16x8_t, int): p2, default: 0)), \
     void (*)(uint32x4_t, float32x4_t, int): __arm_vcvtaq_m_u32_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, float32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, float32x4_t, int): p2, default: 0)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vcvtmq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, float16x8_t, int): __arm_vcvtmq_m_s16_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, float16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, float16x8_t, int): p2, default: 0)), \
     void (*)(int32x4_t, float32x4_t, int): __arm_vcvtmq_m_s32_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, float32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, float32x4_t, int): p2, default: 0)), \
     void (*)(uint16x8_t, float16x8_t, int): __arm_vcvtmq_m_u16_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, float16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, float16x8_t, int): p2, default: 0)), \
     void (*)(uint32x4_t, float32x4_t, int): __arm_vcvtmq_m_u32_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, float32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, float32x4_t, int): p2, default: 0)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vcvtnq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, float16x8_t, int): __arm_vcvtnq_m_s16_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, float16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, float16x8_t, int): p2, default: 0)), \
     void (*)(int32x4_t, float32x4_t, int): __arm_vcvtnq_m_s32_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, float32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, float32x4_t, int): p2, default: 0)), \
     void (*)(uint16x8_t, float16x8_t, int): __arm_vcvtnq_m_u16_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, float16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, float16x8_t, int): p2, default: 0)), \
     void (*)(uint32x4_t, float32x4_t, int): __arm_vcvtnq_m_u32_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, float32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, float32x4_t, int): p2, default: 0)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vcvtpq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, float16x8_t, int): __arm_vcvtpq_m_s16_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, float16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, float16x8_t, int): p2, default: 0)), \
     void (*)(int32x4_t, float32x4_t, int): __arm_vcvtpq_m_s32_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, float32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, float32x4_t, int): p2, default: 0)), \
     void (*)(uint16x8_t, float16x8_t, int): __arm_vcvtpq_m_u16_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, float16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, float16x8_t, int): p2, default: 0)), \
     void (*)(uint32x4_t, float32x4_t, int): __arm_vcvtpq_m_u32_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, float32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, float32x4_t, int): p2, default: 0)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vcvtq(p0) _Generic( \
    (void (*)(__ARM_mve_typeof(p0)))0, \
     void (*)(int16x8_t): __arm_vcvtq_f16_s16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int16x8_t): p0, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(uint16x8_t): __arm_vcvtq_f16_u16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(uint16x8_t): p0, default: *(uint16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t): __arm_vcvtq_f32_s32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int32x4_t): p0, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(uint32x4_t): __arm_vcvtq_f32_u32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(uint32x4_t): p0, default: *(uint32x4_t *)__ARM_undef)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vcvtq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(float16x8_t, int16x8_t, int): __arm_vcvtq_m_f16_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, int16x8_t, int): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, int16x8_t, int): p2, default: 0)), \
     void (*)(float16x8_t, uint16x8_t, int): __arm_vcvtq_m_f16_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, uint16x8_t, int): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, uint16x8_t, int): p2, default: 0)), \
     void (*)(float32x4_t, int32x4_t, int): __arm_vcvtq_m_f32_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, int32x4_t, int): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, int32x4_t, int): p2, default: 0)), \
     void (*)(float32x4_t, uint32x4_t, int): __arm_vcvtq_m_f32_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, uint32x4_t, int): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, uint32x4_t, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, uint32x4_t, int): p2, default: 0)), \
     void (*)(int16x8_t, float16x8_t, int): __arm_vcvtq_m_s16_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, float16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, float16x8_t, int): p2, default: 0)), \
     void (*)(int32x4_t, float32x4_t, int): __arm_vcvtq_m_s32_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, float32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, float32x4_t, int): p2, default: 0)), \
     void (*)(uint16x8_t, float16x8_t, int): __arm_vcvtq_m_u16_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, float16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, float16x8_t, int): p2, default: 0)), \
     void (*)(uint32x4_t, float32x4_t, int): __arm_vcvtq_m_u32_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, float32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, float32x4_t, int): p2, default: 0)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vcvtq_m_n(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(float16x8_t, int16x8_t, int, int): __arm_vcvtq_m_n_f16_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, int16x8_t, int, int): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, int16x8_t, int, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, int16x8_t, int, int): p2, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, int16x8_t, int, int): p3, default: 0)), \
     void (*)(float16x8_t, uint16x8_t, int, int): __arm_vcvtq_m_n_f16_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, uint16x8_t, int, int): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, uint16x8_t, int, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, uint16x8_t, int, int): p2, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, uint16x8_t, int, int): p3, default: 0)), \
     void (*)(float32x4_t, int32x4_t, int, int): __arm_vcvtq_m_n_f32_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, int32x4_t, int, int): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, int32x4_t, int, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, int32x4_t, int, int): p2, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, int32x4_t, int, int): p3, default: 0)), \
     void (*)(float32x4_t, uint32x4_t, int, int): __arm_vcvtq_m_n_f32_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, uint32x4_t, int, int): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, uint32x4_t, int, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, uint32x4_t, int, int): p2, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, uint32x4_t, int, int): p3, default: 0)), \
     void (*)(int16x8_t, float16x8_t, int, int): __arm_vcvtq_m_n_s16_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, float16x8_t, int, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, float16x8_t, int, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, float16x8_t, int, int): p2, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, float16x8_t, int, int): p3, default: 0)), \
     void (*)(int32x4_t, float32x4_t, int, int): __arm_vcvtq_m_n_s32_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, float32x4_t, int, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, float32x4_t, int, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, float32x4_t, int, int): p2, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, float32x4_t, int, int): p3, default: 0)), \
     void (*)(uint16x8_t, float16x8_t, int, int): __arm_vcvtq_m_n_u16_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, float16x8_t, int, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, float16x8_t, int, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, float16x8_t, int, int): p2, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, float16x8_t, int, int): p3, default: 0)), \
     void (*)(uint32x4_t, float32x4_t, int, int): __arm_vcvtq_m_n_u32_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, float32x4_t, int, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, float32x4_t, int, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, float32x4_t, int, int): p2, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, float32x4_t, int, int): p3, default: 0)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vcvtq_n(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int16x8_t, int): __arm_vcvtq_n_f16_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p1, default: 1)), \
     void (*)(uint16x8_t, int): __arm_vcvtq_n_f16_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p1, default: 1)), \
     void (*)(int32x4_t, int): __arm_vcvtq_n_f32_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p1, default: 1)), \
     void (*)(uint32x4_t, int): __arm_vcvtq_n_f32_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p1, default: 1)))

#endif /* MVE floating point */

#define __arm_vddupq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(uint16x8_t, int, int, int): __arm_vddupq_m_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, int, int, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, int, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, int, int, int): p2, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, int, int, int): p3, default: 0)), \
     void (*)(uint32x4_t, int, int, int): __arm_vddupq_m_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, int, int, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, int, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, int, int, int): p2, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, int, int, int): p3, default: 0)), \
     void (*)(uint8x16_t, int, int, int): __arm_vddupq_m_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, int, int, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, int, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, int, int, int): p2, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, int, int, int): p3, default: 0)), \
     void (*)(uint16x8_t, uint32_t *, int, int): __arm_vddupq_m_wb_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint32_t *, int, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint32_t *, int, int): p1, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint32_t *, int, int): p2, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint32_t *, int, int): p3, default: 0)), \
     void (*)(uint32x4_t, uint32_t *, int, int): __arm_vddupq_m_wb_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32_t *, int, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32_t *, int, int): p1, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32_t *, int, int): p2, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32_t *, int, int): p3, default: 0)), \
     void (*)(uint8x16_t, uint32_t *, int, int): __arm_vddupq_m_wb_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint32_t *, int, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint32_t *, int, int): p1, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint32_t *, int, int): p2, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint32_t *, int, int): p3, default: 0)))

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vdupq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(float16x8_t, double, int): __arm_vdupq_m_n_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, double, int): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, double, int): p1, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, double, int): p2, default: 0)), \
     void (*)(float32x4_t, double, int): __arm_vdupq_m_n_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, double, int): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, double, int): p1, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, double, int): p2, default: 0)), \
     void (*)(int16x8_t, int, int): __arm_vdupq_m_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int, int): p2, default: 0)), \
     void (*)(int32x4_t, int, int): __arm_vdupq_m_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int, int): p2, default: 0)), \
     void (*)(int8x16_t, int, int): __arm_vdupq_m_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int, int): p2, default: 0)), \
     void (*)(uint16x8_t, int, int): __arm_vdupq_m_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, int, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, int, int): p2, default: 0)), \
     void (*)(uint32x4_t, int, int): __arm_vdupq_m_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, int, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, int, int): p2, default: 0)), \
     void (*)(uint8x16_t, int, int): __arm_vdupq_m_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, int, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, int, int): p2, default: 0)))

#else /* MVE floating point */

#define __arm_vdupq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, int, int): __arm_vdupq_m_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int, int): p2, default: 0)), \
     void (*)(int32x4_t, int, int): __arm_vdupq_m_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int, int): p2, default: 0)), \
     void (*)(int8x16_t, int, int): __arm_vdupq_m_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int, int): p2, default: 0)), \
     void (*)(uint16x8_t, int, int): __arm_vdupq_m_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, int, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, int, int): p2, default: 0)), \
     void (*)(uint32x4_t, int, int): __arm_vdupq_m_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, int, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, int, int): p2, default: 0)), \
     void (*)(uint8x16_t, int, int): __arm_vdupq_m_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, int, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, int, int): p2, default: 0)))

#endif /* MVE floating point */

#define __arm_vdwdupq_m(p0, p1, p2, p3, p4) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, \
     void (*)(uint16x8_t, int, int, int, int): __arm_vdwdupq_m_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint16x8_t, int, int, int, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint16x8_t, int, int, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint16x8_t, int, int, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint16x8_t, int, int, int, int): p3, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint16x8_t, int, int, int, int): p4, default: 0)), \
     void (*)(uint32x4_t, int, int, int, int): __arm_vdwdupq_m_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, int, int, int, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, int, int, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, int, int, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, int, int, int, int): p3, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, int, int, int, int): p4, default: 0)), \
     void (*)(uint8x16_t, int, int, int, int): __arm_vdwdupq_m_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint8x16_t, int, int, int, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint8x16_t, int, int, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint8x16_t, int, int, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint8x16_t, int, int, int, int): p3, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint8x16_t, int, int, int, int): p4, default: 0)), \
     void (*)(uint16x8_t, uint32_t *, int, int, int): __arm_vdwdupq_m_wb_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint16x8_t, uint32_t *, int, int, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint16x8_t, uint32_t *, int, int, int): p1, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint16x8_t, uint32_t *, int, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint16x8_t, uint32_t *, int, int, int): p3, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint16x8_t, uint32_t *, int, int, int): p4, default: 0)), \
     void (*)(uint32x4_t, uint32_t *, int, int, int): __arm_vdwdupq_m_wb_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, uint32_t *, int, int, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, uint32_t *, int, int, int): p1, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, uint32_t *, int, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, uint32_t *, int, int, int): p3, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, uint32_t *, int, int, int): p4, default: 0)), \
     void (*)(uint8x16_t, uint32_t *, int, int, int): __arm_vdwdupq_m_wb_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint8x16_t, uint32_t *, int, int, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint8x16_t, uint32_t *, int, int, int): p1, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint8x16_t, uint32_t *, int, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint8x16_t, uint32_t *, int, int, int): p3, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint8x16_t, uint32_t *, int, int, int): p4, default: 0)))

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vfmaq(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(float16x8_t, float16x8_t, float16x8_t): __arm_vfmaq_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, float16x8_t): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, float16x8_t): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, float16x8_t): p2, default: *(float16x8_t *)__ARM_undef)), \
     void (*)(float32x4_t, float32x4_t, float32x4_t): __arm_vfmaq_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, float32x4_t): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, float32x4_t): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, float32x4_t): p2, default: *(float32x4_t *)__ARM_undef)), \
     void (*)(float16x8_t, float16x8_t, double): __arm_vfmaq_n_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, double): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, double): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, double): p2, default: 0.0)), \
     void (*)(float32x4_t, float32x4_t, double): __arm_vfmaq_n_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, double): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, double): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, double): p2, default: 0.0)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vfmaq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(float16x8_t, float16x8_t, float16x8_t, int): __arm_vfmaq_m_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, float16x8_t, int): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, float16x8_t, int): p2, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, float16x8_t, int): p3, default: 0)), \
     void (*)(float32x4_t, float32x4_t, float32x4_t, int): __arm_vfmaq_m_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, float32x4_t, int): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, float32x4_t, int): p2, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, float32x4_t, int): p3, default: 0)), \
     void (*)(float16x8_t, float16x8_t, double, int): __arm_vfmaq_m_n_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, double, int): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, double, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, double, int): p2, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, double, int): p3, default: 0)), \
     void (*)(float32x4_t, float32x4_t, double, int): __arm_vfmaq_m_n_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, double, int): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, double, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, double, int): p2, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, double, int): p3, default: 0)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vfmasq(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(float16x8_t, float16x8_t, double): __arm_vfmasq_n_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, double): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, double): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, double): p2, default: 0.0)), \
     void (*)(float32x4_t, float32x4_t, double): __arm_vfmasq_n_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, double): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, double): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, double): p2, default: 0.0)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vfmasq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(float16x8_t, float16x8_t, double, int): __arm_vfmasq_m_n_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, double, int): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, double, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, double, int): p2, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, double, int): p3, default: 0)), \
     void (*)(float32x4_t, float32x4_t, double, int): __arm_vfmasq_m_n_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, double, int): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, double, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, double, int): p2, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, double, int): p3, default: 0)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vfmsq(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(float16x8_t, float16x8_t, float16x8_t): __arm_vfmsq_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, float16x8_t): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, float16x8_t): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, float16x8_t): p2, default: *(float16x8_t *)__ARM_undef)), \
     void (*)(float32x4_t, float32x4_t, float32x4_t): __arm_vfmsq_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, float32x4_t): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, float32x4_t): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, float32x4_t): p2, default: *(float32x4_t *)__ARM_undef)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vfmsq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(float16x8_t, float16x8_t, float16x8_t, int): __arm_vfmsq_m_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, float16x8_t, int): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, float16x8_t, int): p2, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, float16x8_t, int): p3, default: 0)), \
     void (*)(float32x4_t, float32x4_t, float32x4_t, int): __arm_vfmsq_m_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, float32x4_t, int): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, float32x4_t, int): p2, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, float32x4_t, int): p3, default: 0)))

#endif /* MVE floating point */

#define __arm_vhaddq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int16x8_t, int): __arm_vhaddq_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p1, default: 0)), \
     void (*)(int32x4_t, int): __arm_vhaddq_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p1, default: 0)), \
     void (*)(int8x16_t, int): __arm_vhaddq_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p1, default: 0)), \
     void (*)(uint16x8_t, int): __arm_vhaddq_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p1, default: 0)), \
     void (*)(uint32x4_t, int): __arm_vhaddq_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p1, default: 0)), \
     void (*)(uint8x16_t, int): __arm_vhaddq_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int): p1, default: 0)), \
     void (*)(int16x8_t, int16x8_t): __arm_vhaddq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t, int32x4_t): __arm_vhaddq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t, int8x16_t): __arm_vhaddq_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int8x16_t): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int8x16_t): p1, default: *(int8x16_t *)__ARM_undef)), \
     void (*)(uint16x8_t, uint16x8_t): __arm_vhaddq_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint16x8_t): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint16x8_t): p1, default: *(uint16x8_t *)__ARM_undef)), \
     void (*)(uint32x4_t, uint32x4_t): __arm_vhaddq_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, uint32x4_t): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, uint32x4_t): p1, default: *(uint32x4_t *)__ARM_undef)), \
     void (*)(uint8x16_t, uint8x16_t): __arm_vhaddq_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint8x16_t): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint8x16_t): p1, default: *(uint8x16_t *)__ARM_undef)))

#define __arm_vhaddq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(int16x8_t, int16x8_t, int, int): __arm_vhaddq_m_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int, int): __arm_vhaddq_m_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int, int): __arm_vhaddq_m_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p3, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, int, int): __arm_vhaddq_m_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p3, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, int, int): __arm_vhaddq_m_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p3, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, int, int): __arm_vhaddq_m_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p3, default: 0)), \
     void (*)(int16x8_t, int16x8_t, int16x8_t, int): __arm_vhaddq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p2, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t, int): __arm_vhaddq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p2, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t, int): __arm_vhaddq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p2, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p3, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): __arm_vhaddq_m_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p2, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p3, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): __arm_vhaddq_m_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p2, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p3, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): __arm_vhaddq_m_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p2, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p3, default: 0)))

#define __arm_vhsubq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int16x8_t, int): __arm_vhsubq_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p1, default: 0)), \
     void (*)(int32x4_t, int): __arm_vhsubq_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p1, default: 0)), \
     void (*)(int8x16_t, int): __arm_vhsubq_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p1, default: 0)), \
     void (*)(uint16x8_t, int): __arm_vhsubq_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p1, default: 0)), \
     void (*)(uint32x4_t, int): __arm_vhsubq_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p1, default: 0)), \
     void (*)(uint8x16_t, int): __arm_vhsubq_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int): p1, default: 0)), \
     void (*)(int16x8_t, int16x8_t): __arm_vhsubq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t, int32x4_t): __arm_vhsubq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t, int8x16_t): __arm_vhsubq_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int8x16_t): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int8x16_t): p1, default: *(int8x16_t *)__ARM_undef)), \
     void (*)(uint16x8_t, uint16x8_t): __arm_vhsubq_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint16x8_t): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint16x8_t): p1, default: *(uint16x8_t *)__ARM_undef)), \
     void (*)(uint32x4_t, uint32x4_t): __arm_vhsubq_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, uint32x4_t): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, uint32x4_t): p1, default: *(uint32x4_t *)__ARM_undef)), \
     void (*)(uint8x16_t, uint8x16_t): __arm_vhsubq_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint8x16_t): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint8x16_t): p1, default: *(uint8x16_t *)__ARM_undef)))

#define __arm_vhsubq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(int16x8_t, int16x8_t, int, int): __arm_vhsubq_m_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int, int): __arm_vhsubq_m_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int, int): __arm_vhsubq_m_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p3, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, int, int): __arm_vhsubq_m_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p3, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, int, int): __arm_vhsubq_m_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p3, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, int, int): __arm_vhsubq_m_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p3, default: 0)), \
     void (*)(int16x8_t, int16x8_t, int16x8_t, int): __arm_vhsubq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p2, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t, int): __arm_vhsubq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p2, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t, int): __arm_vhsubq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p2, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p3, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): __arm_vhsubq_m_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p2, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p3, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): __arm_vhsubq_m_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p2, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p3, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): __arm_vhsubq_m_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p2, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p3, default: 0)))

#define __arm_vidupq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(uint16x8_t, int, int, int): __arm_vidupq_m_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, int, int, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, int, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, int, int, int): p2, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, int, int, int): p3, default: 0)), \
     void (*)(uint32x4_t, int, int, int): __arm_vidupq_m_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, int, int, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, int, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, int, int, int): p2, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, int, int, int): p3, default: 0)), \
     void (*)(uint8x16_t, int, int, int): __arm_vidupq_m_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, int, int, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, int, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, int, int, int): p2, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, int, int, int): p3, default: 0)), \
     void (*)(uint16x8_t, uint32_t *, int, int): __arm_vidupq_m_wb_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint32_t *, int, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint32_t *, int, int): p1, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint32_t *, int, int): p2, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint32_t *, int, int): p3, default: 0)), \
     void (*)(uint32x4_t, uint32_t *, int, int): __arm_vidupq_m_wb_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32_t *, int, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32_t *, int, int): p1, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32_t *, int, int): p2, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32_t *, int, int): p3, default: 0)), \
     void (*)(uint8x16_t, uint32_t *, int, int): __arm_vidupq_m_wb_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint32_t *, int, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint32_t *, int, int): p1, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint32_t *, int, int): p2, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint32_t *, int, int): p3, default: 0)))

#define __arm_viwdupq_m(p0, p1, p2, p3, p4) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, \
     void (*)(uint16x8_t, int, int, int, int): __arm_viwdupq_m_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint16x8_t, int, int, int, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint16x8_t, int, int, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint16x8_t, int, int, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint16x8_t, int, int, int, int): p3, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint16x8_t, int, int, int, int): p4, default: 0)), \
     void (*)(uint32x4_t, int, int, int, int): __arm_viwdupq_m_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, int, int, int, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, int, int, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, int, int, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, int, int, int, int): p3, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, int, int, int, int): p4, default: 0)), \
     void (*)(uint8x16_t, int, int, int, int): __arm_viwdupq_m_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint8x16_t, int, int, int, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint8x16_t, int, int, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint8x16_t, int, int, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint8x16_t, int, int, int, int): p3, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint8x16_t, int, int, int, int): p4, default: 0)), \
     void (*)(uint16x8_t, uint32_t *, int, int, int): __arm_viwdupq_m_wb_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint16x8_t, uint32_t *, int, int, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint16x8_t, uint32_t *, int, int, int): p1, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint16x8_t, uint32_t *, int, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint16x8_t, uint32_t *, int, int, int): p3, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint16x8_t, uint32_t *, int, int, int): p4, default: 0)), \
     void (*)(uint32x4_t, uint32_t *, int, int, int): __arm_viwdupq_m_wb_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, uint32_t *, int, int, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, uint32_t *, int, int, int): p1, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, uint32_t *, int, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, uint32_t *, int, int, int): p3, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, uint32_t *, int, int, int): p4, default: 0)), \
     void (*)(uint8x16_t, uint32_t *, int, int, int): __arm_viwdupq_m_wb_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint8x16_t, uint32_t *, int, int, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint8x16_t, uint32_t *, int, int, int): p1, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint8x16_t, uint32_t *, int, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint8x16_t, uint32_t *, int, int, int): p3, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint8x16_t, uint32_t *, int, int, int): p4, default: 0)))

#define __arm_vmaxavq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int, int16x8_t): __arm_vmaxavq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int16x8_t): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int, int32x4_t): __arm_vmaxavq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int32x4_t): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int, int8x16_t): __arm_vmaxavq_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int8x16_t): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int8x16_t): p1, default: *(int8x16_t *)__ARM_undef)))

#define __arm_vmaxavq_p(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int, int16x8_t, int): __arm_vmaxavq_p_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int16x8_t, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int16x8_t, int): p2, default: 0)), \
     void (*)(int, int32x4_t, int): __arm_vmaxavq_p_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int32x4_t, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int32x4_t, int): p2, default: 0)), \
     void (*)(int, int8x16_t, int): __arm_vmaxavq_p_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int8x16_t, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int8x16_t, int): p2, default: 0)))

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vmaxnmavq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(double, float16x8_t): __arm_vmaxnmavq_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(double, float16x8_t): p0, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(double, float16x8_t): p1, default: *(float16x8_t *)__ARM_undef)), \
     void (*)(double, float32x4_t): __arm_vmaxnmavq_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(double, float32x4_t): p0, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(double, float32x4_t): p1, default: *(float32x4_t *)__ARM_undef)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vmaxnmavq_p(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(double, float16x8_t, int): __arm_vmaxnmavq_p_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(double, float16x8_t, int): p0, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(double, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(double, float16x8_t, int): p2, default: 0)), \
     void (*)(double, float32x4_t, int): __arm_vmaxnmavq_p_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(double, float32x4_t, int): p0, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(double, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(double, float32x4_t, int): p2, default: 0)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vmaxnmvq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(double, float16x8_t): __arm_vmaxnmvq_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(double, float16x8_t): p0, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(double, float16x8_t): p1, default: *(float16x8_t *)__ARM_undef)), \
     void (*)(double, float32x4_t): __arm_vmaxnmvq_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(double, float32x4_t): p0, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(double, float32x4_t): p1, default: *(float32x4_t *)__ARM_undef)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vmaxnmvq_p(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(double, float16x8_t, int): __arm_vmaxnmvq_p_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(double, float16x8_t, int): p0, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(double, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(double, float16x8_t, int): p2, default: 0)), \
     void (*)(double, float32x4_t, int): __arm_vmaxnmvq_p_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(double, float32x4_t, int): p0, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(double, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(double, float32x4_t, int): p2, default: 0)))

#endif /* MVE floating point */

#define __arm_vmaxvq_p(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int, int16x8_t, int): __arm_vmaxvq_p_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int16x8_t, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int16x8_t, int): p2, default: 0)), \
     void (*)(int, int32x4_t, int): __arm_vmaxvq_p_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int32x4_t, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int32x4_t, int): p2, default: 0)), \
     void (*)(int, int8x16_t, int): __arm_vmaxvq_p_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int8x16_t, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int8x16_t, int): p2, default: 0)), \
     void (*)(int, uint16x8_t, int): __arm_vmaxvq_p_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint16x8_t, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint16x8_t, int): p2, default: 0)), \
     void (*)(int, uint32x4_t, int): __arm_vmaxvq_p_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint32x4_t, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint32x4_t, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint32x4_t, int): p2, default: 0)), \
     void (*)(int, uint8x16_t, int): __arm_vmaxvq_p_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint8x16_t, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint8x16_t, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint8x16_t, int): p2, default: 0)))

#define __arm_vminavq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int, int16x8_t): __arm_vminavq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int16x8_t): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int, int32x4_t): __arm_vminavq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int32x4_t): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int, int8x16_t): __arm_vminavq_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int8x16_t): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int8x16_t): p1, default: *(int8x16_t *)__ARM_undef)))

#define __arm_vminavq_p(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int, int16x8_t, int): __arm_vminavq_p_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int16x8_t, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int16x8_t, int): p2, default: 0)), \
     void (*)(int, int32x4_t, int): __arm_vminavq_p_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int32x4_t, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int32x4_t, int): p2, default: 0)), \
     void (*)(int, int8x16_t, int): __arm_vminavq_p_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int8x16_t, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int8x16_t, int): p2, default: 0)))

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vminnmavq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(double, float16x8_t): __arm_vminnmavq_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(double, float16x8_t): p0, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(double, float16x8_t): p1, default: *(float16x8_t *)__ARM_undef)), \
     void (*)(double, float32x4_t): __arm_vminnmavq_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(double, float32x4_t): p0, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(double, float32x4_t): p1, default: *(float32x4_t *)__ARM_undef)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vminnmavq_p(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(double, float16x8_t, int): __arm_vminnmavq_p_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(double, float16x8_t, int): p0, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(double, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(double, float16x8_t, int): p2, default: 0)), \
     void (*)(double, float32x4_t, int): __arm_vminnmavq_p_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(double, float32x4_t, int): p0, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(double, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(double, float32x4_t, int): p2, default: 0)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vminnmvq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(double, float16x8_t): __arm_vminnmvq_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(double, float16x8_t): p0, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(double, float16x8_t): p1, default: *(float16x8_t *)__ARM_undef)), \
     void (*)(double, float32x4_t): __arm_vminnmvq_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(double, float32x4_t): p0, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(double, float32x4_t): p1, default: *(float32x4_t *)__ARM_undef)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vminnmvq_p(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(double, float16x8_t, int): __arm_vminnmvq_p_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(double, float16x8_t, int): p0, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(double, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(double, float16x8_t, int): p2, default: 0)), \
     void (*)(double, float32x4_t, int): __arm_vminnmvq_p_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(double, float32x4_t, int): p0, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(double, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(double, float32x4_t, int): p2, default: 0)))

#endif /* MVE floating point */

#define __arm_vminvq_p(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int, int16x8_t, int): __arm_vminvq_p_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int16x8_t, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int16x8_t, int): p2, default: 0)), \
     void (*)(int, int32x4_t, int): __arm_vminvq_p_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int32x4_t, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int32x4_t, int): p2, default: 0)), \
     void (*)(int, int8x16_t, int): __arm_vminvq_p_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int8x16_t, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int8x16_t, int): p2, default: 0)), \
     void (*)(int, uint16x8_t, int): __arm_vminvq_p_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint16x8_t, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint16x8_t, int): p2, default: 0)), \
     void (*)(int, uint32x4_t, int): __arm_vminvq_p_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint32x4_t, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint32x4_t, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint32x4_t, int): p2, default: 0)), \
     void (*)(int, uint8x16_t, int): __arm_vminvq_p_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint8x16_t, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint8x16_t, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, uint8x16_t, int): p2, default: 0)))

#define __arm_vmlaq(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, int16x8_t, int): __arm_vmlaq_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p2, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int): __arm_vmlaq_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p2, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int): __arm_vmlaq_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p2, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, int): __arm_vmlaq_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint16x8_t, int): p2, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, int): __arm_vmlaq_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint32x4_t, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint32x4_t, int): p2, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, int): __arm_vmlaq_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint8x16_t, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint8x16_t, int): p2, default: 0)))

#define __arm_vmlaq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(int16x8_t, int16x8_t, int, int): __arm_vmlaq_m_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int, int): __arm_vmlaq_m_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int, int): __arm_vmlaq_m_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p3, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, int, int): __arm_vmlaq_m_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p3, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, int, int): __arm_vmlaq_m_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p3, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, int, int): __arm_vmlaq_m_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p3, default: 0)))

#define __arm_vmlasq(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, int16x8_t, int): __arm_vmlasq_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p2, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int): __arm_vmlasq_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p2, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int): __arm_vmlasq_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p2, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, int): __arm_vmlasq_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint16x8_t, int): p2, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, int): __arm_vmlasq_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint32x4_t, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint32x4_t, int): p2, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, int): __arm_vmlasq_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint8x16_t, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint8x16_t, int): p2, default: 0)))

#define __arm_vmlasq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(int16x8_t, int16x8_t, int, int): __arm_vmlasq_m_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int, int): __arm_vmlasq_m_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int, int): __arm_vmlasq_m_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p3, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, int, int): __arm_vmlasq_m_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p3, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, int, int): __arm_vmlasq_m_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p3, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, int, int): __arm_vmlasq_m_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p3, default: 0)))

#define __arm_vmovlbq(p0) _Generic( \
    (void (*)(__ARM_mve_typeof(p0)))0, \
     void (*)(int16x8_t): __arm_vmovlbq_s16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int16x8_t): p0, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int8x16_t): __arm_vmovlbq_s8(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int8x16_t): p0, default: *(int8x16_t *)__ARM_undef)), \
     void (*)(uint16x8_t): __arm_vmovlbq_u16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(uint16x8_t): p0, default: *(uint16x8_t *)__ARM_undef)), \
     void (*)(uint8x16_t): __arm_vmovlbq_u8(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(uint8x16_t): p0, default: *(uint8x16_t *)__ARM_undef)))

#define __arm_vmovlbq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int32x4_t, int16x8_t, int): __arm_vmovlbq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int16x8_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int16x8_t, int): p2, default: 0)), \
     void (*)(int16x8_t, int8x16_t, int): __arm_vmovlbq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int8x16_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int8x16_t, int): p2, default: 0)), \
     void (*)(uint32x4_t, uint16x8_t, int): __arm_vmovlbq_m_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint16x8_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint16x8_t, int): p2, default: 0)), \
     void (*)(uint16x8_t, uint8x16_t, int): __arm_vmovlbq_m_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint8x16_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint8x16_t, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint8x16_t, int): p2, default: 0)))

#define __arm_vmovltq(p0) _Generic( \
    (void (*)(__ARM_mve_typeof(p0)))0, \
     void (*)(int16x8_t): __arm_vmovltq_s16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int16x8_t): p0, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int8x16_t): __arm_vmovltq_s8(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int8x16_t): p0, default: *(int8x16_t *)__ARM_undef)), \
     void (*)(uint16x8_t): __arm_vmovltq_u16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(uint16x8_t): p0, default: *(uint16x8_t *)__ARM_undef)), \
     void (*)(uint8x16_t): __arm_vmovltq_u8(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(uint8x16_t): p0, default: *(uint8x16_t *)__ARM_undef)))

#define __arm_vmovltq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int32x4_t, int16x8_t, int): __arm_vmovltq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int16x8_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int16x8_t, int): p2, default: 0)), \
     void (*)(int16x8_t, int8x16_t, int): __arm_vmovltq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int8x16_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int8x16_t, int): p2, default: 0)), \
     void (*)(uint32x4_t, uint16x8_t, int): __arm_vmovltq_m_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint16x8_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint16x8_t, int): p2, default: 0)), \
     void (*)(uint16x8_t, uint8x16_t, int): __arm_vmovltq_m_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint8x16_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint8x16_t, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint8x16_t, int): p2, default: 0)))

#define __arm_vmovnbq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int8x16_t, int16x8_t): __arm_vmovnbq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int16x8_t): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int16x8_t, int32x4_t): __arm_vmovnbq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int32x4_t): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(uint8x16_t, uint16x8_t): __arm_vmovnbq_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint16x8_t): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint16x8_t): p1, default: *(uint16x8_t *)__ARM_undef)), \
     void (*)(uint16x8_t, uint32x4_t): __arm_vmovnbq_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint32x4_t): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint32x4_t): p1, default: *(uint32x4_t *)__ARM_undef)))

#define __arm_vmovnbq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int8x16_t, int16x8_t, int): __arm_vmovnbq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int16x8_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int16x8_t, int): p2, default: 0)), \
     void (*)(int16x8_t, int32x4_t, int): __arm_vmovnbq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int32x4_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int32x4_t, int): p2, default: 0)), \
     void (*)(uint8x16_t, uint16x8_t, int): __arm_vmovnbq_m_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint16x8_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint16x8_t, int): p2, default: 0)), \
     void (*)(uint16x8_t, uint32x4_t, int): __arm_vmovnbq_m_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint32x4_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint32x4_t, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint32x4_t, int): p2, default: 0)))

#define __arm_vmovntq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int8x16_t, int16x8_t): __arm_vmovntq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int16x8_t): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int16x8_t, int32x4_t): __arm_vmovntq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int32x4_t): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(uint8x16_t, uint16x8_t): __arm_vmovntq_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint16x8_t): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint16x8_t): p1, default: *(uint16x8_t *)__ARM_undef)), \
     void (*)(uint16x8_t, uint32x4_t): __arm_vmovntq_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint32x4_t): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint32x4_t): p1, default: *(uint32x4_t *)__ARM_undef)))

#define __arm_vmovntq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int8x16_t, int16x8_t, int): __arm_vmovntq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int16x8_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int16x8_t, int): p2, default: 0)), \
     void (*)(int16x8_t, int32x4_t, int): __arm_vmovntq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int32x4_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int32x4_t, int): p2, default: 0)), \
     void (*)(uint8x16_t, uint16x8_t, int): __arm_vmovntq_m_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint16x8_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint16x8_t, int): p2, default: 0)), \
     void (*)(uint16x8_t, uint32x4_t, int): __arm_vmovntq_m_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint32x4_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint32x4_t, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint32x4_t, int): p2, default: 0)))

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vmulq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(float16x8_t, float16x8_t): __arm_vmulq_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float16x8_t, float16x8_t): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float16x8_t, float16x8_t): p1, default: *(float16x8_t *)__ARM_undef)), \
     void (*)(float32x4_t, float32x4_t): __arm_vmulq_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float32x4_t, float32x4_t): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float32x4_t, float32x4_t): p1, default: *(float32x4_t *)__ARM_undef)), \
     void (*)(float16x8_t, double): __arm_vmulq_n_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float16x8_t, double): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float16x8_t, double): p1, default: 0.0)), \
     void (*)(float32x4_t, double): __arm_vmulq_n_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float32x4_t, double): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float32x4_t, double): p1, default: 0.0)), \
     void (*)(int16x8_t, int): __arm_vmulq_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p1, default: 0)), \
     void (*)(int32x4_t, int): __arm_vmulq_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p1, default: 0)), \
     void (*)(int8x16_t, int): __arm_vmulq_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p1, default: 0)), \
     void (*)(uint16x8_t, int): __arm_vmulq_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p1, default: 0)), \
     void (*)(uint32x4_t, int): __arm_vmulq_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p1, default: 0)), \
     void (*)(uint8x16_t, int): __arm_vmulq_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int): p1, default: 0)), \
     void (*)(int16x8_t, int16x8_t): __arm_vmulq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t, int32x4_t): __arm_vmulq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t, int8x16_t): __arm_vmulq_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int8x16_t): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int8x16_t): p1, default: *(int8x16_t *)__ARM_undef)), \
     void (*)(uint16x8_t, uint16x8_t): __arm_vmulq_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint16x8_t): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint16x8_t): p1, default: *(uint16x8_t *)__ARM_undef)), \
     void (*)(uint32x4_t, uint32x4_t): __arm_vmulq_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, uint32x4_t): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, uint32x4_t): p1, default: *(uint32x4_t *)__ARM_undef)), \
     void (*)(uint8x16_t, uint8x16_t): __arm_vmulq_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint8x16_t): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint8x16_t): p1, default: *(uint8x16_t *)__ARM_undef)))

#else /* MVE floating point */

#define __arm_vmulq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int16x8_t, int): __arm_vmulq_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p1, default: 0)), \
     void (*)(int32x4_t, int): __arm_vmulq_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p1, default: 0)), \
     void (*)(int8x16_t, int): __arm_vmulq_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p1, default: 0)), \
     void (*)(uint16x8_t, int): __arm_vmulq_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p1, default: 0)), \
     void (*)(uint32x4_t, int): __arm_vmulq_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p1, default: 0)), \
     void (*)(uint8x16_t, int): __arm_vmulq_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int): p1, default: 0)), \
     void (*)(int16x8_t, int16x8_t): __arm_vmulq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t, int32x4_t): __arm_vmulq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t, int8x16_t): __arm_vmulq_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int8x16_t): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int8x16_t): p1, default: *(int8x16_t *)__ARM_undef)), \
     void (*)(uint16x8_t, uint16x8_t): __arm_vmulq_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint16x8_t): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint16x8_t): p1, default: *(uint16x8_t *)__ARM_undef)), \
     void (*)(uint32x4_t, uint32x4_t): __arm_vmulq_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, uint32x4_t): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, uint32x4_t): p1, default: *(uint32x4_t *)__ARM_undef)), \
     void (*)(uint8x16_t, uint8x16_t): __arm_vmulq_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint8x16_t): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint8x16_t): p1, default: *(uint8x16_t *)__ARM_undef)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vmulq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(float16x8_t, float16x8_t, float16x8_t, int): __arm_vmulq_m_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, float16x8_t, int): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, float16x8_t, int): p2, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, float16x8_t, int): p3, default: 0)), \
     void (*)(float32x4_t, float32x4_t, float32x4_t, int): __arm_vmulq_m_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, float32x4_t, int): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, float32x4_t, int): p2, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, float32x4_t, int): p3, default: 0)), \
     void (*)(float16x8_t, float16x8_t, double, int): __arm_vmulq_m_n_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, double, int): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, double, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, double, int): p2, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, double, int): p3, default: 0)), \
     void (*)(float32x4_t, float32x4_t, double, int): __arm_vmulq_m_n_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, double, int): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, double, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, double, int): p2, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, double, int): p3, default: 0)), \
     void (*)(int16x8_t, int16x8_t, int, int): __arm_vmulq_m_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int, int): __arm_vmulq_m_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int, int): __arm_vmulq_m_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p3, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, int, int): __arm_vmulq_m_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p3, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, int, int): __arm_vmulq_m_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p3, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, int, int): __arm_vmulq_m_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p3, default: 0)), \
     void (*)(int16x8_t, int16x8_t, int16x8_t, int): __arm_vmulq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p2, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t, int): __arm_vmulq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p2, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t, int): __arm_vmulq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p2, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p3, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): __arm_vmulq_m_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p2, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p3, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): __arm_vmulq_m_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p2, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p3, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): __arm_vmulq_m_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p2, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p3, default: 0)))

#else /* MVE floating point */

#define __arm_vmulq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(int16x8_t, int16x8_t, int, int): __arm_vmulq_m_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int, int): __arm_vmulq_m_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int, int): __arm_vmulq_m_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p3, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, int, int): __arm_vmulq_m_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p3, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, int, int): __arm_vmulq_m_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p3, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, int, int): __arm_vmulq_m_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p3, default: 0)), \
     void (*)(int16x8_t, int16x8_t, int16x8_t, int): __arm_vmulq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p2, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t, int): __arm_vmulq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p2, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t, int): __arm_vmulq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p2, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p3, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): __arm_vmulq_m_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p2, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p3, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): __arm_vmulq_m_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p2, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p3, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): __arm_vmulq_m_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p2, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p3, default: 0)))

#endif /* MVE floating point */

#define __arm_vmvnq(p0) _Generic( \
    (void (*)(__ARM_mve_typeof(p0)))0, \
     void (*)(int16x8_t): __arm_vmvnq_s16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int16x8_t): p0, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t): __arm_vmvnq_s32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int32x4_t): p0, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t): __arm_vmvnq_s8(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int8x16_t): p0, default: *(int8x16_t *)__ARM_undef)), \
     void (*)(uint16x8_t): __arm_vmvnq_u16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(uint16x8_t): p0, default: *(uint16x8_t *)__ARM_undef)), \
     void (*)(uint32x4_t): __arm_vmvnq_u32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(uint32x4_t): p0, default: *(uint32x4_t *)__ARM_undef)), \
     void (*)(uint8x16_t): __arm_vmvnq_u8(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(uint8x16_t): p0, default: *(uint8x16_t *)__ARM_undef)))

#define __arm_vmvnq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, int, int): __arm_vmvnq_m_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int, int): p2, default: 0)), \
     void (*)(int32x4_t, int, int): __arm_vmvnq_m_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int, int): p2, default: 0)), \
     void (*)(uint16x8_t, int, int): __arm_vmvnq_m_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, int, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, int, int): p2, default: 0)), \
     void (*)(uint32x4_t, int, int): __arm_vmvnq_m_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, int, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, int, int): p2, default: 0)), \
     void (*)(int16x8_t, int16x8_t, int): __arm_vmvnq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p2, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int): __arm_vmvnq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p2, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int): __arm_vmvnq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p2, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, int): __arm_vmvnq_m_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint16x8_t, int): p2, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, int): __arm_vmvnq_m_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint32x4_t, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint32x4_t, int): p2, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, int): __arm_vmvnq_m_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint8x16_t, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint8x16_t, int): p2, default: 0)))

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vnegq(p0) _Generic( \
    (void (*)(__ARM_mve_typeof(p0)))0, \
     void (*)(float16x8_t): __arm_vnegq_f16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(float16x8_t): p0, default: *(float16x8_t *)__ARM_undef)), \
     void (*)(float32x4_t): __arm_vnegq_f32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(float32x4_t): p0, default: *(float32x4_t *)__ARM_undef)), \
     void (*)(int16x8_t): __arm_vnegq_s16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int16x8_t): p0, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t): __arm_vnegq_s32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int32x4_t): p0, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t): __arm_vnegq_s8(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int8x16_t): p0, default: *(int8x16_t *)__ARM_undef)))

#else /* MVE floating point */

#define __arm_vnegq(p0) _Generic( \
    (void (*)(__ARM_mve_typeof(p0)))0, \
     void (*)(int16x8_t): __arm_vnegq_s16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int16x8_t): p0, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t): __arm_vnegq_s32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int32x4_t): p0, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t): __arm_vnegq_s8(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int8x16_t): p0, default: *(int8x16_t *)__ARM_undef)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vnegq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(float16x8_t, float16x8_t, int): __arm_vnegq_m_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p2, default: 0)), \
     void (*)(float32x4_t, float32x4_t, int): __arm_vnegq_m_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, int): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, int): p2, default: 0)), \
     void (*)(int16x8_t, int16x8_t, int): __arm_vnegq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p2, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int): __arm_vnegq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p2, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int): __arm_vnegq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p2, default: 0)))

#else /* MVE floating point */

#define __arm_vnegq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, int16x8_t, int): __arm_vnegq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p2, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int): __arm_vnegq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p2, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int): __arm_vnegq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p2, default: 0)))

#endif /* MVE floating point */

#define __arm_vqabsq(p0) _Generic( \
    (void (*)(__ARM_mve_typeof(p0)))0, \
     void (*)(int16x8_t): __arm_vqabsq_s16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int16x8_t): p0, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t): __arm_vqabsq_s32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int32x4_t): p0, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t): __arm_vqabsq_s8(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int8x16_t): p0, default: *(int8x16_t *)__ARM_undef)))

#define __arm_vqabsq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, int16x8_t, int): __arm_vqabsq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p2, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int): __arm_vqabsq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p2, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int): __arm_vqabsq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p2, default: 0)))

#define __arm_vqaddq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int16x8_t, int): __arm_vqaddq_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p1, default: 0)), \
     void (*)(int32x4_t, int): __arm_vqaddq_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p1, default: 0)), \
     void (*)(int8x16_t, int): __arm_vqaddq_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p1, default: 0)), \
     void (*)(uint16x8_t, int): __arm_vqaddq_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p1, default: 0)), \
     void (*)(uint32x4_t, int): __arm_vqaddq_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p1, default: 0)), \
     void (*)(uint8x16_t, int): __arm_vqaddq_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int): p1, default: 0)), \
     void (*)(int16x8_t, int16x8_t): __arm_vqaddq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t, int32x4_t): __arm_vqaddq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t, int8x16_t): __arm_vqaddq_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int8x16_t): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int8x16_t): p1, default: *(int8x16_t *)__ARM_undef)), \
     void (*)(uint16x8_t, uint16x8_t): __arm_vqaddq_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint16x8_t): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint16x8_t): p1, default: *(uint16x8_t *)__ARM_undef)), \
     void (*)(uint32x4_t, uint32x4_t): __arm_vqaddq_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, uint32x4_t): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, uint32x4_t): p1, default: *(uint32x4_t *)__ARM_undef)), \
     void (*)(uint8x16_t, uint8x16_t): __arm_vqaddq_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint8x16_t): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint8x16_t): p1, default: *(uint8x16_t *)__ARM_undef)))

#define __arm_vqaddq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(int16x8_t, int16x8_t, int, int): __arm_vqaddq_m_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int, int): __arm_vqaddq_m_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int, int): __arm_vqaddq_m_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p3, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, int, int): __arm_vqaddq_m_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p3, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, int, int): __arm_vqaddq_m_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p3, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, int, int): __arm_vqaddq_m_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p3, default: 0)), \
     void (*)(int16x8_t, int16x8_t, int16x8_t, int): __arm_vqaddq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p2, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t, int): __arm_vqaddq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p2, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t, int): __arm_vqaddq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p2, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p3, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): __arm_vqaddq_m_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p2, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p3, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): __arm_vqaddq_m_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p2, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p3, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): __arm_vqaddq_m_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p2, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p3, default: 0)))

#define __arm_vqdmladhq(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, int16x8_t, int16x8_t): __arm_vqdmladhq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int16x8_t): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int16x8_t): p2, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t): __arm_vqdmladhq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int32x4_t): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int32x4_t): p2, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t): __arm_vqdmladhq_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int8x16_t): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int8x16_t): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int8x16_t): p2, default: *(int8x16_t *)__ARM_undef)))

#define __arm_vqdmladhq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(int16x8_t, int16x8_t, int16x8_t, int): __arm_vqdmladhq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p2, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t, int): __arm_vqdmladhq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p2, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t, int): __arm_vqdmladhq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p2, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p3, default: 0)))

#define __arm_vqdmladhxq(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, int16x8_t, int16x8_t): __arm_vqdmladhxq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int16x8_t): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int16x8_t): p2, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t): __arm_vqdmladhxq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int32x4_t): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int32x4_t): p2, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t): __arm_vqdmladhxq_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int8x16_t): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int8x16_t): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int8x16_t): p2, default: *(int8x16_t *)__ARM_undef)))

#define __arm_vqdmladhxq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(int16x8_t, int16x8_t, int16x8_t, int): __arm_vqdmladhxq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p2, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t, int): __arm_vqdmladhxq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p2, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t, int): __arm_vqdmladhxq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p2, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p3, default: 0)))

#define __arm_vqdmlahq(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, int16x8_t, int): __arm_vqdmlahq_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p2, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int): __arm_vqdmlahq_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p2, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int): __arm_vqdmlahq_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p2, default: 0)))

#define __arm_vqdmlahq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(int16x8_t, int16x8_t, int, int): __arm_vqdmlahq_m_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int, int): __arm_vqdmlahq_m_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int, int): __arm_vqdmlahq_m_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p3, default: 0)))

#define __arm_vqdmlsdhq(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, int16x8_t, int16x8_t): __arm_vqdmlsdhq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int16x8_t): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int16x8_t): p2, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t): __arm_vqdmlsdhq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int32x4_t): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int32x4_t): p2, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t): __arm_vqdmlsdhq_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int8x16_t): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int8x16_t): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int8x16_t): p2, default: *(int8x16_t *)__ARM_undef)))

#define __arm_vqdmlsdhq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(int16x8_t, int16x8_t, int16x8_t, int): __arm_vqdmlsdhq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p2, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t, int): __arm_vqdmlsdhq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p2, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t, int): __arm_vqdmlsdhq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p2, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p3, default: 0)))

#define __arm_vqdmlsdhxq(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, int16x8_t, int16x8_t): __arm_vqdmlsdhxq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int16x8_t): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int16x8_t): p2, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t): __arm_vqdmlsdhxq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int32x4_t): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int32x4_t): p2, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t): __arm_vqdmlsdhxq_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int8x16_t): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int8x16_t): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int8x16_t): p2, default: *(int8x16_t *)__ARM_undef)))

#define __arm_vqdmlsdhxq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(int16x8_t, int16x8_t, int16x8_t, int): __arm_vqdmlsdhxq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p2, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t, int): __arm_vqdmlsdhxq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p2, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t, int): __arm_vqdmlsdhxq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p2, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p3, default: 0)))

#define __arm_vqdmulhq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int16x8_t, int): __arm_vqdmulhq_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p1, default: 0)), \
     void (*)(int32x4_t, int): __arm_vqdmulhq_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p1, default: 0)), \
     void (*)(int8x16_t, int): __arm_vqdmulhq_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p1, default: 0)), \
     void (*)(int16x8_t, int16x8_t): __arm_vqdmulhq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t, int32x4_t): __arm_vqdmulhq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t, int8x16_t): __arm_vqdmulhq_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int8x16_t): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int8x16_t): p1, default: *(int8x16_t *)__ARM_undef)))

#define __arm_vqdmulhq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(int16x8_t, int16x8_t, int, int): __arm_vqdmulhq_m_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int, int): __arm_vqdmulhq_m_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int, int): __arm_vqdmulhq_m_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p3, default: 0)), \
     void (*)(int16x8_t, int16x8_t, int16x8_t, int): __arm_vqdmulhq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p2, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t, int): __arm_vqdmulhq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p2, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t, int): __arm_vqdmulhq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p2, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p3, default: 0)))

#define __arm_vqdmullbq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int16x8_t, int): __arm_vqdmullbq_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p1, default: 0)), \
     void (*)(int32x4_t, int): __arm_vqdmullbq_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p1, default: 0)), \
     void (*)(int16x8_t, int16x8_t): __arm_vqdmullbq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t, int32x4_t): __arm_vqdmullbq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef)))

#define __arm_vqdmullbq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(int32x4_t, int16x8_t, int, int): __arm_vqdmullbq_m_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int16x8_t, int, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int16x8_t, int, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int16x8_t, int, int): p3, default: 0)), \
     void (*)(int64x2_t, int32x4_t, int, int): __arm_vqdmullbq_m_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int64x2_t, int32x4_t, int, int): p0, default: *(int64x2_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int64x2_t, int32x4_t, int, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int64x2_t, int32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int64x2_t, int32x4_t, int, int): p3, default: 0)), \
     void (*)(int32x4_t, int16x8_t, int16x8_t, int): __arm_vqdmullbq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int16x8_t, int16x8_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int16x8_t, int16x8_t, int): p2, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int16x8_t, int16x8_t, int): p3, default: 0)), \
     void (*)(int64x2_t, int32x4_t, int32x4_t, int): __arm_vqdmullbq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int64x2_t, int32x4_t, int32x4_t, int): p0, default: *(int64x2_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int64x2_t, int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int64x2_t, int32x4_t, int32x4_t, int): p2, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int64x2_t, int32x4_t, int32x4_t, int): p3, default: 0)))

#define __arm_vqdmulltq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int16x8_t, int): __arm_vqdmulltq_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p1, default: 0)), \
     void (*)(int32x4_t, int): __arm_vqdmulltq_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p1, default: 0)), \
     void (*)(int16x8_t, int16x8_t): __arm_vqdmulltq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t, int32x4_t): __arm_vqdmulltq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef)))

#define __arm_vqdmulltq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(int32x4_t, int16x8_t, int, int): __arm_vqdmulltq_m_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int16x8_t, int, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int16x8_t, int, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int16x8_t, int, int): p3, default: 0)), \
     void (*)(int64x2_t, int32x4_t, int, int): __arm_vqdmulltq_m_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int64x2_t, int32x4_t, int, int): p0, default: *(int64x2_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int64x2_t, int32x4_t, int, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int64x2_t, int32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int64x2_t, int32x4_t, int, int): p3, default: 0)), \
     void (*)(int32x4_t, int16x8_t, int16x8_t, int): __arm_vqdmulltq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int16x8_t, int16x8_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int16x8_t, int16x8_t, int): p2, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int16x8_t, int16x8_t, int): p3, default: 0)), \
     void (*)(int64x2_t, int32x4_t, int32x4_t, int): __arm_vqdmulltq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int64x2_t, int32x4_t, int32x4_t, int): p0, default: *(int64x2_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int64x2_t, int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int64x2_t, int32x4_t, int32x4_t, int): p2, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int64x2_t, int32x4_t, int32x4_t, int): p3, default: 0)))

#define __arm_vqmovnbq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int8x16_t, int16x8_t): __arm_vqmovnbq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int16x8_t): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int16x8_t, int32x4_t): __arm_vqmovnbq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int32x4_t): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(uint8x16_t, uint16x8_t): __arm_vqmovnbq_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint16x8_t): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint16x8_t): p1, default: *(uint16x8_t *)__ARM_undef)), \
     void (*)(uint16x8_t, uint32x4_t): __arm_vqmovnbq_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint32x4_t): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint32x4_t): p1, default: *(uint32x4_t *)__ARM_undef)))

#define __arm_vqmovnbq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int8x16_t, int16x8_t, int): __arm_vqmovnbq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int16x8_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int16x8_t, int): p2, default: 0)), \
     void (*)(int16x8_t, int32x4_t, int): __arm_vqmovnbq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int32x4_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int32x4_t, int): p2, default: 0)), \
     void (*)(uint8x16_t, uint16x8_t, int): __arm_vqmovnbq_m_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint16x8_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint16x8_t, int): p2, default: 0)), \
     void (*)(uint16x8_t, uint32x4_t, int): __arm_vqmovnbq_m_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint32x4_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint32x4_t, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint32x4_t, int): p2, default: 0)))

#define __arm_vqmovntq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int8x16_t, int16x8_t): __arm_vqmovntq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int16x8_t): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int16x8_t, int32x4_t): __arm_vqmovntq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int32x4_t): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(uint8x16_t, uint16x8_t): __arm_vqmovntq_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint16x8_t): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint16x8_t): p1, default: *(uint16x8_t *)__ARM_undef)), \
     void (*)(uint16x8_t, uint32x4_t): __arm_vqmovntq_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint32x4_t): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint32x4_t): p1, default: *(uint32x4_t *)__ARM_undef)))

#define __arm_vqmovntq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int8x16_t, int16x8_t, int): __arm_vqmovntq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int16x8_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int16x8_t, int): p2, default: 0)), \
     void (*)(int16x8_t, int32x4_t, int): __arm_vqmovntq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int32x4_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int32x4_t, int): p2, default: 0)), \
     void (*)(uint8x16_t, uint16x8_t, int): __arm_vqmovntq_m_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint16x8_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint16x8_t, int): p2, default: 0)), \
     void (*)(uint16x8_t, uint32x4_t, int): __arm_vqmovntq_m_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint32x4_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint32x4_t, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint32x4_t, int): p2, default: 0)))

#define __arm_vqmovunbq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(uint8x16_t, int16x8_t): __arm_vqmovunbq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int16x8_t): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(uint16x8_t, int32x4_t): __arm_vqmovunbq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int32x4_t): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef)))

#define __arm_vqmovunbq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(uint8x16_t, int16x8_t, int): __arm_vqmovunbq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, int16x8_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, int16x8_t, int): p2, default: 0)), \
     void (*)(uint16x8_t, int32x4_t, int): __arm_vqmovunbq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, int32x4_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, int32x4_t, int): p2, default: 0)))

#define __arm_vqmovuntq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(uint8x16_t, int16x8_t): __arm_vqmovuntq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int16x8_t): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(uint16x8_t, int32x4_t): __arm_vqmovuntq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int32x4_t): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef)))

#define __arm_vqmovuntq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(uint8x16_t, int16x8_t, int): __arm_vqmovuntq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, int16x8_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, int16x8_t, int): p2, default: 0)), \
     void (*)(uint16x8_t, int32x4_t, int): __arm_vqmovuntq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, int32x4_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, int32x4_t, int): p2, default: 0)))

#define __arm_vqnegq(p0) _Generic( \
    (void (*)(__ARM_mve_typeof(p0)))0, \
     void (*)(int16x8_t): __arm_vqnegq_s16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int16x8_t): p0, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t): __arm_vqnegq_s32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int32x4_t): p0, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t): __arm_vqnegq_s8(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int8x16_t): p0, default: *(int8x16_t *)__ARM_undef)))

#define __arm_vqnegq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, int16x8_t, int): __arm_vqnegq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p2, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int): __arm_vqnegq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p2, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int): __arm_vqnegq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p2, default: 0)))

#define __arm_vqrdmladhq(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, int16x8_t, int16x8_t): __arm_vqrdmladhq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int16x8_t): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int16x8_t): p2, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t): __arm_vqrdmladhq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int32x4_t): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int32x4_t): p2, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t): __arm_vqrdmladhq_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int8x16_t): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int8x16_t): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int8x16_t): p2, default: *(int8x16_t *)__ARM_undef)))

#define __arm_vqrdmladhq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(int16x8_t, int16x8_t, int16x8_t, int): __arm_vqrdmladhq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p2, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t, int): __arm_vqrdmladhq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p2, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t, int): __arm_vqrdmladhq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p2, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p3, default: 0)))

#define __arm_vqrdmladhxq(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, int16x8_t, int16x8_t): __arm_vqrdmladhxq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int16x8_t): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int16x8_t): p2, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t): __arm_vqrdmladhxq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int32x4_t): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int32x4_t): p2, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t): __arm_vqrdmladhxq_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int8x16_t): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int8x16_t): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int8x16_t): p2, default: *(int8x16_t *)__ARM_undef)))

#define __arm_vqrdmladhxq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(int16x8_t, int16x8_t, int16x8_t, int): __arm_vqrdmladhxq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p2, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t, int): __arm_vqrdmladhxq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p2, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t, int): __arm_vqrdmladhxq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p2, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p3, default: 0)))

#define __arm_vqrdmlahq(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, int16x8_t, int): __arm_vqrdmlahq_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p2, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int): __arm_vqrdmlahq_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p2, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int): __arm_vqrdmlahq_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p2, default: 0)))

#define __arm_vqrdmlahq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(int16x8_t, int16x8_t, int, int): __arm_vqrdmlahq_m_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int, int): __arm_vqrdmlahq_m_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int, int): __arm_vqrdmlahq_m_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p3, default: 0)))

#define __arm_vqrdmlashq(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, int16x8_t, int): __arm_vqrdmlashq_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p2, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int): __arm_vqrdmlashq_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p2, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int): __arm_vqrdmlashq_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p2, default: 0)))

#define __arm_vqrdmlashq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(int16x8_t, int16x8_t, int, int): __arm_vqrdmlashq_m_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int, int): __arm_vqrdmlashq_m_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int, int): __arm_vqrdmlashq_m_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p3, default: 0)))

#define __arm_vqrdmlsdhq(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, int16x8_t, int16x8_t): __arm_vqrdmlsdhq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int16x8_t): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int16x8_t): p2, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t): __arm_vqrdmlsdhq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int32x4_t): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int32x4_t): p2, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t): __arm_vqrdmlsdhq_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int8x16_t): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int8x16_t): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int8x16_t): p2, default: *(int8x16_t *)__ARM_undef)))

#define __arm_vqrdmlsdhq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(int16x8_t, int16x8_t, int16x8_t, int): __arm_vqrdmlsdhq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p2, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t, int): __arm_vqrdmlsdhq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p2, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t, int): __arm_vqrdmlsdhq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p2, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p3, default: 0)))

#define __arm_vqrdmlsdhxq(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, int16x8_t, int16x8_t): __arm_vqrdmlsdhxq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int16x8_t): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int16x8_t): p2, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t): __arm_vqrdmlsdhxq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int32x4_t): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int32x4_t): p2, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t): __arm_vqrdmlsdhxq_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int8x16_t): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int8x16_t): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int8x16_t): p2, default: *(int8x16_t *)__ARM_undef)))

#define __arm_vqrdmlsdhxq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(int16x8_t, int16x8_t, int16x8_t, int): __arm_vqrdmlsdhxq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p2, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t, int): __arm_vqrdmlsdhxq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p2, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t, int): __arm_vqrdmlsdhxq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p2, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p3, default: 0)))

#define __arm_vqrdmulhq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int16x8_t, int): __arm_vqrdmulhq_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p1, default: 0)), \
     void (*)(int32x4_t, int): __arm_vqrdmulhq_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p1, default: 0)), \
     void (*)(int8x16_t, int): __arm_vqrdmulhq_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p1, default: 0)), \
     void (*)(int16x8_t, int16x8_t): __arm_vqrdmulhq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t, int32x4_t): __arm_vqrdmulhq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t, int8x16_t): __arm_vqrdmulhq_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int8x16_t): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int8x16_t): p1, default: *(int8x16_t *)__ARM_undef)))

#define __arm_vqrdmulhq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(int16x8_t, int16x8_t, int, int): __arm_vqrdmulhq_m_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int, int): __arm_vqrdmulhq_m_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int, int): __arm_vqrdmulhq_m_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p3, default: 0)), \
     void (*)(int16x8_t, int16x8_t, int16x8_t, int): __arm_vqrdmulhq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p2, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t, int): __arm_vqrdmulhq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p2, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t, int): __arm_vqrdmulhq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p2, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p3, default: 0)))

#define __arm_vqsubq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int16x8_t, int): __arm_vqsubq_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p1, default: 0)), \
     void (*)(int32x4_t, int): __arm_vqsubq_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p1, default: 0)), \
     void (*)(int8x16_t, int): __arm_vqsubq_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p1, default: 0)), \
     void (*)(uint16x8_t, int): __arm_vqsubq_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p1, default: 0)), \
     void (*)(uint32x4_t, int): __arm_vqsubq_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p1, default: 0)), \
     void (*)(uint8x16_t, int): __arm_vqsubq_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int): p1, default: 0)), \
     void (*)(int16x8_t, int16x8_t): __arm_vqsubq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t, int32x4_t): __arm_vqsubq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t, int8x16_t): __arm_vqsubq_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int8x16_t): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int8x16_t): p1, default: *(int8x16_t *)__ARM_undef)), \
     void (*)(uint16x8_t, uint16x8_t): __arm_vqsubq_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint16x8_t): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint16x8_t): p1, default: *(uint16x8_t *)__ARM_undef)), \
     void (*)(uint32x4_t, uint32x4_t): __arm_vqsubq_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, uint32x4_t): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, uint32x4_t): p1, default: *(uint32x4_t *)__ARM_undef)), \
     void (*)(uint8x16_t, uint8x16_t): __arm_vqsubq_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint8x16_t): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint8x16_t): p1, default: *(uint8x16_t *)__ARM_undef)))

#define __arm_vqsubq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(int16x8_t, int16x8_t, int, int): __arm_vqsubq_m_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int, int): __arm_vqsubq_m_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int, int): __arm_vqsubq_m_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p3, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, int, int): __arm_vqsubq_m_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p3, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, int, int): __arm_vqsubq_m_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p3, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, int, int): __arm_vqsubq_m_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p3, default: 0)), \
     void (*)(int16x8_t, int16x8_t, int16x8_t, int): __arm_vqsubq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p2, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t, int): __arm_vqsubq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p2, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t, int): __arm_vqsubq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p2, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p3, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): __arm_vqsubq_m_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p2, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p3, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): __arm_vqsubq_m_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p2, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p3, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): __arm_vqsubq_m_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p2, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p3, default: 0)))

#define __arm_vrev16q(p0) _Generic( \
    (void (*)(__ARM_mve_typeof(p0)))0, \
     void (*)(int8x16_t): __arm_vrev16q_s8(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int8x16_t): p0, default: *(int8x16_t *)__ARM_undef)), \
     void (*)(uint8x16_t): __arm_vrev16q_u8(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(uint8x16_t): p0, default: *(uint8x16_t *)__ARM_undef)))

#define __arm_vrev16q_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int8x16_t, int8x16_t, int): __arm_vrev16q_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p2, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, int): __arm_vrev16q_m_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint8x16_t, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint8x16_t, int): p2, default: 0)))

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vrev32q(p0) _Generic( \
    (void (*)(__ARM_mve_typeof(p0)))0, \
     void (*)(float16x8_t): __arm_vrev32q_f16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(float16x8_t): p0, default: *(float16x8_t *)__ARM_undef)), \
     void (*)(int16x8_t): __arm_vrev32q_s16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int16x8_t): p0, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int8x16_t): __arm_vrev32q_s8(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int8x16_t): p0, default: *(int8x16_t *)__ARM_undef)), \
     void (*)(uint16x8_t): __arm_vrev32q_u16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(uint16x8_t): p0, default: *(uint16x8_t *)__ARM_undef)), \
     void (*)(uint8x16_t): __arm_vrev32q_u8(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(uint8x16_t): p0, default: *(uint8x16_t *)__ARM_undef)))

#else /* MVE floating point */

#define __arm_vrev32q(p0) _Generic( \
    (void (*)(__ARM_mve_typeof(p0)))0, \
     void (*)(int16x8_t): __arm_vrev32q_s16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int16x8_t): p0, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int8x16_t): __arm_vrev32q_s8(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int8x16_t): p0, default: *(int8x16_t *)__ARM_undef)), \
     void (*)(uint16x8_t): __arm_vrev32q_u16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(uint16x8_t): p0, default: *(uint16x8_t *)__ARM_undef)), \
     void (*)(uint8x16_t): __arm_vrev32q_u8(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(uint8x16_t): p0, default: *(uint8x16_t *)__ARM_undef)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vrev32q_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(float16x8_t, float16x8_t, int): __arm_vrev32q_m_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p2, default: 0)), \
     void (*)(int16x8_t, int16x8_t, int): __arm_vrev32q_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p2, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int): __arm_vrev32q_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p2, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, int): __arm_vrev32q_m_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint16x8_t, int): p2, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, int): __arm_vrev32q_m_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint8x16_t, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint8x16_t, int): p2, default: 0)))

#else /* MVE floating point */

#define __arm_vrev32q_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, int16x8_t, int): __arm_vrev32q_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p2, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int): __arm_vrev32q_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p2, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, int): __arm_vrev32q_m_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint16x8_t, int): p2, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, int): __arm_vrev32q_m_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint8x16_t, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint8x16_t, int): p2, default: 0)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vrev64q(p0) _Generic( \
    (void (*)(__ARM_mve_typeof(p0)))0, \
     void (*)(float16x8_t): __arm_vrev64q_f16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(float16x8_t): p0, default: *(float16x8_t *)__ARM_undef)), \
     void (*)(float32x4_t): __arm_vrev64q_f32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(float32x4_t): p0, default: *(float32x4_t *)__ARM_undef)), \
     void (*)(int16x8_t): __arm_vrev64q_s16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int16x8_t): p0, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t): __arm_vrev64q_s32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int32x4_t): p0, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t): __arm_vrev64q_s8(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int8x16_t): p0, default: *(int8x16_t *)__ARM_undef)), \
     void (*)(uint16x8_t): __arm_vrev64q_u16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(uint16x8_t): p0, default: *(uint16x8_t *)__ARM_undef)), \
     void (*)(uint32x4_t): __arm_vrev64q_u32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(uint32x4_t): p0, default: *(uint32x4_t *)__ARM_undef)), \
     void (*)(uint8x16_t): __arm_vrev64q_u8(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(uint8x16_t): p0, default: *(uint8x16_t *)__ARM_undef)))

#else /* MVE floating point */

#define __arm_vrev64q(p0) _Generic( \
    (void (*)(__ARM_mve_typeof(p0)))0, \
     void (*)(int16x8_t): __arm_vrev64q_s16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int16x8_t): p0, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t): __arm_vrev64q_s32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int32x4_t): p0, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t): __arm_vrev64q_s8(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(int8x16_t): p0, default: *(int8x16_t *)__ARM_undef)), \
     void (*)(uint16x8_t): __arm_vrev64q_u16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(uint16x8_t): p0, default: *(uint16x8_t *)__ARM_undef)), \
     void (*)(uint32x4_t): __arm_vrev64q_u32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(uint32x4_t): p0, default: *(uint32x4_t *)__ARM_undef)), \
     void (*)(uint8x16_t): __arm_vrev64q_u8(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(uint8x16_t): p0, default: *(uint8x16_t *)__ARM_undef)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vrev64q_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(float16x8_t, float16x8_t, int): __arm_vrev64q_m_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p2, default: 0)), \
     void (*)(float32x4_t, float32x4_t, int): __arm_vrev64q_m_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, int): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, int): p2, default: 0)), \
     void (*)(int16x8_t, int16x8_t, int): __arm_vrev64q_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p2, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int): __arm_vrev64q_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p2, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int): __arm_vrev64q_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p2, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, int): __arm_vrev64q_m_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint16x8_t, int): p2, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, int): __arm_vrev64q_m_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint32x4_t, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint32x4_t, int): p2, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, int): __arm_vrev64q_m_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint8x16_t, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint8x16_t, int): p2, default: 0)))

#else /* MVE floating point */

#define __arm_vrev64q_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, int16x8_t, int): __arm_vrev64q_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, int16x8_t, int): p2, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int): __arm_vrev64q_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, int): p2, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int): __arm_vrev64q_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, int8x16_t, int): p2, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, int): __arm_vrev64q_m_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint16x8_t, int): p2, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, int): __arm_vrev64q_m_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint32x4_t, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint32x4_t, int): p2, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, int): __arm_vrev64q_m_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint8x16_t, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint8x16_t, int): p2, default: 0)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vrndaq(p0) _Generic( \
    (void (*)(__ARM_mve_typeof(p0)))0, \
     void (*)(float16x8_t): __arm_vrndaq_f16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(float16x8_t): p0, default: *(float16x8_t *)__ARM_undef)), \
     void (*)(float32x4_t): __arm_vrndaq_f32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(float32x4_t): p0, default: *(float32x4_t *)__ARM_undef)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vrndaq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(float16x8_t, float16x8_t, int): __arm_vrndaq_m_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p2, default: 0)), \
     void (*)(float32x4_t, float32x4_t, int): __arm_vrndaq_m_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, int): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, int): p2, default: 0)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vrndmq(p0) _Generic( \
    (void (*)(__ARM_mve_typeof(p0)))0, \
     void (*)(float16x8_t): __arm_vrndmq_f16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(float16x8_t): p0, default: *(float16x8_t *)__ARM_undef)), \
     void (*)(float32x4_t): __arm_vrndmq_f32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(float32x4_t): p0, default: *(float32x4_t *)__ARM_undef)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vrndmq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(float16x8_t, float16x8_t, int): __arm_vrndmq_m_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p2, default: 0)), \
     void (*)(float32x4_t, float32x4_t, int): __arm_vrndmq_m_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, int): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, int): p2, default: 0)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vrndnq(p0) _Generic( \
    (void (*)(__ARM_mve_typeof(p0)))0, \
     void (*)(float16x8_t): __arm_vrndnq_f16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(float16x8_t): p0, default: *(float16x8_t *)__ARM_undef)), \
     void (*)(float32x4_t): __arm_vrndnq_f32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(float32x4_t): p0, default: *(float32x4_t *)__ARM_undef)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vrndnq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(float16x8_t, float16x8_t, int): __arm_vrndnq_m_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p2, default: 0)), \
     void (*)(float32x4_t, float32x4_t, int): __arm_vrndnq_m_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, int): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, int): p2, default: 0)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vrndpq(p0) _Generic( \
    (void (*)(__ARM_mve_typeof(p0)))0, \
     void (*)(float16x8_t): __arm_vrndpq_f16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(float16x8_t): p0, default: *(float16x8_t *)__ARM_undef)), \
     void (*)(float32x4_t): __arm_vrndpq_f32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(float32x4_t): p0, default: *(float32x4_t *)__ARM_undef)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vrndpq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(float16x8_t, float16x8_t, int): __arm_vrndpq_m_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p2, default: 0)), \
     void (*)(float32x4_t, float32x4_t, int): __arm_vrndpq_m_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, int): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, int): p2, default: 0)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vrndq(p0) _Generic( \
    (void (*)(__ARM_mve_typeof(p0)))0, \
     void (*)(float16x8_t): __arm_vrndq_f16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(float16x8_t): p0, default: *(float16x8_t *)__ARM_undef)), \
     void (*)(float32x4_t): __arm_vrndq_f32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(float32x4_t): p0, default: *(float32x4_t *)__ARM_undef)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vrndq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(float16x8_t, float16x8_t, int): __arm_vrndq_m_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p2, default: 0)), \
     void (*)(float32x4_t, float32x4_t, int): __arm_vrndq_m_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, int): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, int): p2, default: 0)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vrndxq(p0) _Generic( \
    (void (*)(__ARM_mve_typeof(p0)))0, \
     void (*)(float16x8_t): __arm_vrndxq_f16(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(float16x8_t): p0, default: *(float16x8_t *)__ARM_undef)), \
     void (*)(float32x4_t): __arm_vrndxq_f32(_Generic((void (*)(__ARM_mve_typeof(p0)))0, void (*)(float32x4_t): p0, default: *(float32x4_t *)__ARM_undef)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vrndxq_m(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(float16x8_t, float16x8_t, int): __arm_vrndxq_m_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float16x8_t, float16x8_t, int): p2, default: 0)), \
     void (*)(float32x4_t, float32x4_t, int): __arm_vrndxq_m_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, int): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(float32x4_t, float32x4_t, int): p2, default: 0)))

#endif /* MVE floating point */

#define __arm_vsbciq(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int32x4_t, int32x4_t, uint32_t *): __arm_vsbciq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, uint32_t *): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, uint32_t *): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, uint32_t *): p2, default: *(uint32_t * *)__ARM_undef)), \
     void (*)(uint32x4_t, uint32x4_t, uint32_t *): __arm_vsbciq_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint32x4_t, uint32_t *): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint32x4_t, uint32_t *): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint32x4_t, uint32_t *): p2, default: *(uint32_t * *)__ARM_undef)))

#define __arm_vsbciq_m(p0, p1, p2, p3, p4) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, \
     void (*)(int32x4_t, int32x4_t, int32x4_t, uint32_t *, int): __arm_vsbciq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, uint32_t *, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, uint32_t *, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, uint32_t *, int): p2, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, uint32_t *, int): p3, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, uint32_t *, int): p4, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, uint32x4_t, uint32_t *, int): __arm_vsbciq_m_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, uint32_t *, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, uint32_t *, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, uint32_t *, int): p2, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, uint32_t *, int): p3, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, uint32_t *, int): p4, default: 0)))

#define __arm_vsbcq(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int32x4_t, int32x4_t, uint32_t *): __arm_vsbcq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, uint32_t *): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, uint32_t *): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, int32x4_t, uint32_t *): p2, default: *(uint32_t * *)__ARM_undef)), \
     void (*)(uint32x4_t, uint32x4_t, uint32_t *): __arm_vsbcq_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint32x4_t, uint32_t *): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint32x4_t, uint32_t *): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint32x4_t, uint32_t *): p2, default: *(uint32_t * *)__ARM_undef)))

#define __arm_vsbcq_m(p0, p1, p2, p3, p4) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, \
     void (*)(int32x4_t, int32x4_t, int32x4_t, uint32_t *, int): __arm_vsbcq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, uint32_t *, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, uint32_t *, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, uint32_t *, int): p2, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, uint32_t *, int): p3, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, uint32_t *, int): p4, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, uint32x4_t, uint32_t *, int): __arm_vsbcq_m_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, uint32_t *, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, uint32_t *, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, uint32_t *, int): p2, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, uint32_t *, int): p3, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3), __ARM_mve_typeof(p4)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, uint32_t *, int): p4, default: 0)))

#define __arm_vshlcq(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int16x8_t, uint32_t *, int): __arm_vshlcq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, uint32_t *, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, uint32_t *, int): p1, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int16x8_t, uint32_t *, int): p2, default: 1)), \
     void (*)(int32x4_t, uint32_t *, int): __arm_vshlcq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, uint32_t *, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, uint32_t *, int): p1, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int32x4_t, uint32_t *, int): p2, default: 1)), \
     void (*)(int8x16_t, uint32_t *, int): __arm_vshlcq_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, uint32_t *, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, uint32_t *, int): p1, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int8x16_t, uint32_t *, int): p2, default: 1)), \
     void (*)(uint16x8_t, uint32_t *, int): __arm_vshlcq_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint32_t *, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint32_t *, int): p1, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint16x8_t, uint32_t *, int): p2, default: 1)), \
     void (*)(uint32x4_t, uint32_t *, int): __arm_vshlcq_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint32_t *, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint32_t *, int): p1, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32x4_t, uint32_t *, int): p2, default: 1)), \
     void (*)(uint8x16_t, uint32_t *, int): __arm_vshlcq_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint32_t *, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint32_t *, int): p1, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint8x16_t, uint32_t *, int): p2, default: 1)))

#define __arm_vshlcq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(int16x8_t, uint32_t *, int, int): __arm_vshlcq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, uint32_t *, int, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, uint32_t *, int, int): p1, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, uint32_t *, int, int): p2, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, uint32_t *, int, int): p3, default: 0)), \
     void (*)(int32x4_t, uint32_t *, int, int): __arm_vshlcq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, uint32_t *, int, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, uint32_t *, int, int): p1, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, uint32_t *, int, int): p2, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, uint32_t *, int, int): p3, default: 0)), \
     void (*)(int8x16_t, uint32_t *, int, int): __arm_vshlcq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, uint32_t *, int, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, uint32_t *, int, int): p1, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, uint32_t *, int, int): p2, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, uint32_t *, int, int): p3, default: 0)), \
     void (*)(uint16x8_t, uint32_t *, int, int): __arm_vshlcq_m_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint32_t *, int, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint32_t *, int, int): p1, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint32_t *, int, int): p2, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint32_t *, int, int): p3, default: 0)), \
     void (*)(uint32x4_t, uint32_t *, int, int): __arm_vshlcq_m_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32_t *, int, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32_t *, int, int): p1, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32_t *, int, int): p2, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32_t *, int, int): p3, default: 0)), \
     void (*)(uint8x16_t, uint32_t *, int, int): __arm_vshlcq_m_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint32_t *, int, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint32_t *, int, int): p1, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint32_t *, int, int): p2, default: 1), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint32_t *, int, int): p3, default: 0)))

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vsubq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(float16x8_t, float16x8_t): __arm_vsubq_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float16x8_t, float16x8_t): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float16x8_t, float16x8_t): p1, default: *(float16x8_t *)__ARM_undef)), \
     void (*)(float32x4_t, float32x4_t): __arm_vsubq_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float32x4_t, float32x4_t): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float32x4_t, float32x4_t): p1, default: *(float32x4_t *)__ARM_undef)), \
     void (*)(float16x8_t, double): __arm_vsubq_n_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float16x8_t, double): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float16x8_t, double): p1, default: 0.0)), \
     void (*)(float32x4_t, double): __arm_vsubq_n_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float32x4_t, double): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(float32x4_t, double): p1, default: 0.0)), \
     void (*)(int16x8_t, int): __arm_vsubq_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p1, default: 0)), \
     void (*)(int32x4_t, int): __arm_vsubq_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p1, default: 0)), \
     void (*)(int8x16_t, int): __arm_vsubq_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p1, default: 0)), \
     void (*)(uint16x8_t, int): __arm_vsubq_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p1, default: 0)), \
     void (*)(uint32x4_t, int): __arm_vsubq_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p1, default: 0)), \
     void (*)(uint8x16_t, int): __arm_vsubq_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int): p1, default: 0)), \
     void (*)(int16x8_t, int16x8_t): __arm_vsubq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t, int32x4_t): __arm_vsubq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t, int8x16_t): __arm_vsubq_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int8x16_t): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int8x16_t): p1, default: *(int8x16_t *)__ARM_undef)), \
     void (*)(uint16x8_t, uint16x8_t): __arm_vsubq_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint16x8_t): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint16x8_t): p1, default: *(uint16x8_t *)__ARM_undef)), \
     void (*)(uint32x4_t, uint32x4_t): __arm_vsubq_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, uint32x4_t): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, uint32x4_t): p1, default: *(uint32x4_t *)__ARM_undef)), \
     void (*)(uint8x16_t, uint8x16_t): __arm_vsubq_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint8x16_t): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint8x16_t): p1, default: *(uint8x16_t *)__ARM_undef)))

#else /* MVE floating point */

#define __arm_vsubq(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int16x8_t, int): __arm_vsubq_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int): p1, default: 0)), \
     void (*)(int32x4_t, int): __arm_vsubq_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int): p1, default: 0)), \
     void (*)(int8x16_t, int): __arm_vsubq_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int): p1, default: 0)), \
     void (*)(uint16x8_t, int): __arm_vsubq_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, int): p1, default: 0)), \
     void (*)(uint32x4_t, int): __arm_vsubq_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, int): p1, default: 0)), \
     void (*)(uint8x16_t, int): __arm_vsubq_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, int): p1, default: 0)), \
     void (*)(int16x8_t, int16x8_t): __arm_vsubq_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int16x8_t, int16x8_t): p1, default: *(int16x8_t *)__ARM_undef)), \
     void (*)(int32x4_t, int32x4_t): __arm_vsubq_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int32x4_t, int32x4_t): p1, default: *(int32x4_t *)__ARM_undef)), \
     void (*)(int8x16_t, int8x16_t): __arm_vsubq_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int8x16_t): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int8x16_t, int8x16_t): p1, default: *(int8x16_t *)__ARM_undef)), \
     void (*)(uint16x8_t, uint16x8_t): __arm_vsubq_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint16x8_t): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint16x8_t, uint16x8_t): p1, default: *(uint16x8_t *)__ARM_undef)), \
     void (*)(uint32x4_t, uint32x4_t): __arm_vsubq_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, uint32x4_t): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32x4_t, uint32x4_t): p1, default: *(uint32x4_t *)__ARM_undef)), \
     void (*)(uint8x16_t, uint8x16_t): __arm_vsubq_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint8x16_t): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint8x16_t, uint8x16_t): p1, default: *(uint8x16_t *)__ARM_undef)))

#endif /* MVE floating point */

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define __arm_vsubq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(float16x8_t, float16x8_t, float16x8_t, int): __arm_vsubq_m_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, float16x8_t, int): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, float16x8_t, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, float16x8_t, int): p2, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, float16x8_t, int): p3, default: 0)), \
     void (*)(float32x4_t, float32x4_t, float32x4_t, int): __arm_vsubq_m_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, float32x4_t, int): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, float32x4_t, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, float32x4_t, int): p2, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, float32x4_t, int): p3, default: 0)), \
     void (*)(float16x8_t, float16x8_t, double, int): __arm_vsubq_m_n_f16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, double, int): p0, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, double, int): p1, default: *(float16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, double, int): p2, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float16x8_t, float16x8_t, double, int): p3, default: 0)), \
     void (*)(float32x4_t, float32x4_t, double, int): __arm_vsubq_m_n_f32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, double, int): p0, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, double, int): p1, default: *(float32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, double, int): p2, default: 0.0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(float32x4_t, float32x4_t, double, int): p3, default: 0)), \
     void (*)(int16x8_t, int16x8_t, int, int): __arm_vsubq_m_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int, int): __arm_vsubq_m_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int, int): __arm_vsubq_m_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p3, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, int, int): __arm_vsubq_m_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p3, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, int, int): __arm_vsubq_m_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p3, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, int, int): __arm_vsubq_m_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p3, default: 0)), \
     void (*)(int16x8_t, int16x8_t, int16x8_t, int): __arm_vsubq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p2, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t, int): __arm_vsubq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p2, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t, int): __arm_vsubq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p2, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p3, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): __arm_vsubq_m_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p2, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p3, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): __arm_vsubq_m_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p2, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p3, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): __arm_vsubq_m_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p2, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p3, default: 0)))

#else /* MVE floating point */

#define __arm_vsubq_m(p0, p1, p2, p3) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, \
     void (*)(int16x8_t, int16x8_t, int, int): __arm_vsubq_m_n_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int, int): __arm_vsubq_m_n_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int, int): __arm_vsubq_m_n_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int, int): p3, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, int, int): __arm_vsubq_m_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, int, int): p3, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, int, int): __arm_vsubq_m_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, int, int): p3, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, int, int): __arm_vsubq_m_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p2, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, int, int): p3, default: 0)), \
     void (*)(int16x8_t, int16x8_t, int16x8_t, int): __arm_vsubq_m_s16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p0, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p1, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p2, default: *(int16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int16x8_t, int16x8_t, int16x8_t, int): p3, default: 0)), \
     void (*)(int32x4_t, int32x4_t, int32x4_t, int): __arm_vsubq_m_s32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p0, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p1, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p2, default: *(int32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int32x4_t, int32x4_t, int32x4_t, int): p3, default: 0)), \
     void (*)(int8x16_t, int8x16_t, int8x16_t, int): __arm_vsubq_m_s8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p0, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p1, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p2, default: *(int8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(int8x16_t, int8x16_t, int8x16_t, int): p3, default: 0)), \
     void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): __arm_vsubq_m_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p0, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p1, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p2, default: *(uint16x8_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint16x8_t, uint16x8_t, uint16x8_t, int): p3, default: 0)), \
     void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): __arm_vsubq_m_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p0, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p1, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p2, default: *(uint32x4_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint32x4_t, uint32x4_t, uint32x4_t, int): p3, default: 0)), \
     void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): __arm_vsubq_m_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p0, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p1, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p2, default: *(uint8x16_t *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2), __ARM_mve_typeof(p3)))0, void (*)(uint8x16_t, uint8x16_t, uint8x16_t, int): p3, default: 0)))

#endif /* MVE floating point */

#define __arm_vidupq_u8(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int, int): __arm_vidupq_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int): p1, default: 1)), \
     void (*)(uint32_t *, int): __arm_vidupq_wb_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32_t *, int): p0, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32_t *, int): p1, default: 1)))

#define __arm_vidupq_u16(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int, int): __arm_vidupq_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int): p1, default: 1)), \
     void (*)(uint32_t *, int): __arm_vidupq_wb_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32_t *, int): p0, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32_t *, int): p1, default: 1)))

#define __arm_vidupq_u32(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int, int): __arm_vidupq_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int): p1, default: 1)), \
     void (*)(uint32_t *, int): __arm_vidupq_wb_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32_t *, int): p0, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32_t *, int): p1, default: 1)))

#define __arm_viwdupq_u8(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int, int, int): __arm_viwdupq_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int, int): p2, default: 1)), \
     void (*)(uint32_t *, int, int): __arm_viwdupq_wb_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32_t *, int, int): p0, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32_t *, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32_t *, int, int): p2, default: 1)))

#define __arm_viwdupq_u16(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int, int, int): __arm_viwdupq_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int, int): p2, default: 1)), \
     void (*)(uint32_t *, int, int): __arm_viwdupq_wb_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32_t *, int, int): p0, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32_t *, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32_t *, int, int): p2, default: 1)))

#define __arm_viwdupq_u32(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int, int, int): __arm_viwdupq_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int, int): p2, default: 1)), \
     void (*)(uint32_t *, int, int): __arm_viwdupq_wb_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32_t *, int, int): p0, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32_t *, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32_t *, int, int): p2, default: 1)))

#define __arm_vddupq_u8(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int, int): __arm_vddupq_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int): p1, default: 1)), \
     void (*)(uint32_t *, int): __arm_vddupq_wb_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32_t *, int): p0, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32_t *, int): p1, default: 1)))

#define __arm_vddupq_u16(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int, int): __arm_vddupq_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int): p1, default: 1)), \
     void (*)(uint32_t *, int): __arm_vddupq_wb_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32_t *, int): p0, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32_t *, int): p1, default: 1)))

#define __arm_vddupq_u32(p0, p1) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, \
     void (*)(int, int): __arm_vddupq_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(int, int): p1, default: 1)), \
     void (*)(uint32_t *, int): __arm_vddupq_wb_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32_t *, int): p0, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1)))0, void (*)(uint32_t *, int): p1, default: 1)))

#define __arm_vdwdupq_u8(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int, int, int): __arm_vdwdupq_n_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int, int): p2, default: 1)), \
     void (*)(uint32_t *, int, int): __arm_vdwdupq_wb_u8(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32_t *, int, int): p0, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32_t *, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32_t *, int, int): p2, default: 1)))

#define __arm_vdwdupq_u16(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int, int, int): __arm_vdwdupq_n_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int, int): p2, default: 1)), \
     void (*)(uint32_t *, int, int): __arm_vdwdupq_wb_u16(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32_t *, int, int): p0, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32_t *, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32_t *, int, int): p2, default: 1)))

#define __arm_vdwdupq_u32(p0, p1, p2) _Generic( \
    (void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, \
     void (*)(int, int, int): __arm_vdwdupq_n_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int, int): p0, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(int, int, int): p2, default: 1)), \
     void (*)(uint32_t *, int, int): __arm_vdwdupq_wb_u32(_Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32_t *, int, int): p0, default: *(uint32_t * *)__ARM_undef), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32_t *, int, int): p1, default: 0), _Generic((void (*)(__ARM_mve_typeof(p0), __ARM_mve_typeof(p1), __ARM_mve_typeof(p2)))0, void (*)(uint32_t *, int, int): p2, default: 1)))

#ifndef __ARM_MVE_PRESERVE_USER_NAMESPACE

#define vabsq_m_s16 __arm_vabsq_m_s16
#define vabsq_m_s32 __arm_vabsq_m_s32
#define vabsq_m_s8 __arm_vabsq_m_s8
#define vabsq_s16 __arm_vabsq_s16
#define vabsq_s32 __arm_vabsq_s32
#define vabsq_s8 __arm_vabsq_s8
#define vaddlvaq_p_s32 __arm_vaddlvaq_p_s32
#define vaddlvaq_p_u32 __arm_vaddlvaq_p_u32
#define vaddlvaq_s32 __arm_vaddlvaq_s32
#define vaddlvaq_u32 __arm_vaddlvaq_u32
#define vaddlvq_p_s32 __arm_vaddlvq_p_s32
#define vaddlvq_p_u32 __arm_vaddlvq_p_u32
#define vaddlvq_s32 __arm_vaddlvq_s32
#define vaddlvq_u32 __arm_vaddlvq_u32
#define vaddq_m_n_s16 __arm_vaddq_m_n_s16
#define vaddq_m_n_s32 __arm_vaddq_m_n_s32
#define vaddq_m_n_s8 __arm_vaddq_m_n_s8
#define vaddq_m_n_u16 __arm_vaddq_m_n_u16
#define vaddq_m_n_u32 __arm_vaddq_m_n_u32
#define vaddq_m_n_u8 __arm_vaddq_m_n_u8
#define vaddq_n_s16 __arm_vaddq_n_s16
#define vaddq_n_s32 __arm_vaddq_n_s32
#define vaddq_n_s8 __arm_vaddq_n_s8
#define vaddq_n_u16 __arm_vaddq_n_u16
#define vaddq_n_u32 __arm_vaddq_n_u32
#define vaddq_n_u8 __arm_vaddq_n_u8
#define vaddvaq_p_s16 __arm_vaddvaq_p_s16
#define vaddvaq_p_s32 __arm_vaddvaq_p_s32
#define vaddvaq_p_s8 __arm_vaddvaq_p_s8
#define vaddvaq_p_u16 __arm_vaddvaq_p_u16
#define vaddvaq_p_u32 __arm_vaddvaq_p_u32
#define vaddvaq_p_u8 __arm_vaddvaq_p_u8
#define vaddvaq_s16 __arm_vaddvaq_s16
#define vaddvaq_s32 __arm_vaddvaq_s32
#define vaddvaq_s8 __arm_vaddvaq_s8
#define vaddvaq_u16 __arm_vaddvaq_u16
#define vaddvaq_u32 __arm_vaddvaq_u32
#define vaddvaq_u8 __arm_vaddvaq_u8
#define vaddvq_p_s16 __arm_vaddvq_p_s16
#define vaddvq_p_s32 __arm_vaddvq_p_s32
#define vaddvq_p_s8 __arm_vaddvq_p_s8
#define vaddvq_p_u16 __arm_vaddvq_p_u16
#define vaddvq_p_u32 __arm_vaddvq_p_u32
#define vaddvq_p_u8 __arm_vaddvq_p_u8
#define vaddvq_s16 __arm_vaddvq_s16
#define vaddvq_s32 __arm_vaddvq_s32
#define vaddvq_s8 __arm_vaddvq_s8
#define vaddvq_u16 __arm_vaddvq_u16
#define vaddvq_u32 __arm_vaddvq_u32
#define vaddvq_u8 __arm_vaddvq_u8
#define vbrsrq_m_n_s16 __arm_vbrsrq_m_n_s16
#define vbrsrq_m_n_s32 __arm_vbrsrq_m_n_s32
#define vbrsrq_m_n_s8 __arm_vbrsrq_m_n_s8
#define vbrsrq_m_n_u16 __arm_vbrsrq_m_n_u16
#define vbrsrq_m_n_u32 __arm_vbrsrq_m_n_u32
#define vbrsrq_m_n_u8 __arm_vbrsrq_m_n_u8
#define vbrsrq_n_s16 __arm_vbrsrq_n_s16
#define vbrsrq_n_s32 __arm_vbrsrq_n_s32
#define vbrsrq_n_s8 __arm_vbrsrq_n_s8
#define vbrsrq_n_u16 __arm_vbrsrq_n_u16
#define vbrsrq_n_u32 __arm_vbrsrq_n_u32
#define vbrsrq_n_u8 __arm_vbrsrq_n_u8
#define vclsq_m_s16 __arm_vclsq_m_s16
#define vclsq_m_s32 __arm_vclsq_m_s32
#define vclsq_m_s8 __arm_vclsq_m_s8
#define vclsq_s16 __arm_vclsq_s16
#define vclsq_s32 __arm_vclsq_s32
#define vclsq_s8 __arm_vclsq_s8
#define vclzq_m_s16 __arm_vclzq_m_s16
#define vclzq_m_s32 __arm_vclzq_m_s32
#define vclzq_m_s8 __arm_vclzq_m_s8
#define vclzq_m_u16 __arm_vclzq_m_u16
#define vclzq_m_u32 __arm_vclzq_m_u32
#define vclzq_m_u8 __arm_vclzq_m_u8
#define vclzq_s16 __arm_vclzq_s16
#define vclzq_s32 __arm_vclzq_s32
#define vclzq_s8 __arm_vclzq_s8
#define vclzq_u16 __arm_vclzq_u16
#define vclzq_u32 __arm_vclzq_u32
#define vclzq_u8 __arm_vclzq_u8
#define vddupq_m_n_u16 __arm_vddupq_m_n_u16
#define vddupq_m_n_u32 __arm_vddupq_m_n_u32
#define vddupq_m_n_u8 __arm_vddupq_m_n_u8
#define vddupq_m_wb_u16 __arm_vddupq_m_wb_u16
#define vddupq_m_wb_u32 __arm_vddupq_m_wb_u32
#define vddupq_m_wb_u8 __arm_vddupq_m_wb_u8
#define vddupq_n_u16 __arm_vddupq_n_u16
#define vddupq_n_u32 __arm_vddupq_n_u32
#define vddupq_n_u8 __arm_vddupq_n_u8
#define vddupq_wb_u16 __arm_vddupq_wb_u16
#define vddupq_wb_u32 __arm_vddupq_wb_u32
#define vddupq_wb_u8 __arm_vddupq_wb_u8
#define vdupq_m_n_s16 __arm_vdupq_m_n_s16
#define vdupq_m_n_s32 __arm_vdupq_m_n_s32
#define vdupq_m_n_s8 __arm_vdupq_m_n_s8
#define vdupq_m_n_u16 __arm_vdupq_m_n_u16
#define vdupq_m_n_u32 __arm_vdupq_m_n_u32
#define vdupq_m_n_u8 __arm_vdupq_m_n_u8
#define vdupq_n_s16 __arm_vdupq_n_s16
#define vdupq_n_s32 __arm_vdupq_n_s32
#define vdupq_n_s8 __arm_vdupq_n_s8
#define vdupq_n_u16 __arm_vdupq_n_u16
#define vdupq_n_u32 __arm_vdupq_n_u32
#define vdupq_n_u8 __arm_vdupq_n_u8
#define vdwdupq_m_n_u16 __arm_vdwdupq_m_n_u16
#define vdwdupq_m_n_u32 __arm_vdwdupq_m_n_u32
#define vdwdupq_m_n_u8 __arm_vdwdupq_m_n_u8
#define vdwdupq_m_wb_u16 __arm_vdwdupq_m_wb_u16
#define vdwdupq_m_wb_u32 __arm_vdwdupq_m_wb_u32
#define vdwdupq_m_wb_u8 __arm_vdwdupq_m_wb_u8
#define vdwdupq_n_u16 __arm_vdwdupq_n_u16
#define vdwdupq_n_u32 __arm_vdwdupq_n_u32
#define vdwdupq_n_u8 __arm_vdwdupq_n_u8
#define vdwdupq_wb_u16 __arm_vdwdupq_wb_u16
#define vdwdupq_wb_u32 __arm_vdwdupq_wb_u32
#define vdwdupq_wb_u8 __arm_vdwdupq_wb_u8
#define vhaddq_m_n_s16 __arm_vhaddq_m_n_s16
#define vhaddq_m_n_s32 __arm_vhaddq_m_n_s32
#define vhaddq_m_n_s8 __arm_vhaddq_m_n_s8
#define vhaddq_m_n_u16 __arm_vhaddq_m_n_u16
#define vhaddq_m_n_u32 __arm_vhaddq_m_n_u32
#define vhaddq_m_n_u8 __arm_vhaddq_m_n_u8
#define vhaddq_n_s16 __arm_vhaddq_n_s16
#define vhaddq_n_s32 __arm_vhaddq_n_s32
#define vhaddq_n_s8 __arm_vhaddq_n_s8
#define vhaddq_n_u16 __arm_vhaddq_n_u16
#define vhaddq_n_u32 __arm_vhaddq_n_u32
#define vhaddq_n_u8 __arm_vhaddq_n_u8
#define vhsubq_m_n_s16 __arm_vhsubq_m_n_s16
#define vhsubq_m_n_s32 __arm_vhsubq_m_n_s32
#define vhsubq_m_n_s8 __arm_vhsubq_m_n_s8
#define vhsubq_m_n_u16 __arm_vhsubq_m_n_u16
#define vhsubq_m_n_u32 __arm_vhsubq_m_n_u32
#define vhsubq_m_n_u8 __arm_vhsubq_m_n_u8
#define vhsubq_n_s16 __arm_vhsubq_n_s16
#define vhsubq_n_s32 __arm_vhsubq_n_s32
#define vhsubq_n_s8 __arm_vhsubq_n_s8
#define vhsubq_n_u16 __arm_vhsubq_n_u16
#define vhsubq_n_u32 __arm_vhsubq_n_u32
#define vhsubq_n_u8 __arm_vhsubq_n_u8
#define vidupq_m_n_u16 __arm_vidupq_m_n_u16
#define vidupq_m_n_u32 __arm_vidupq_m_n_u32
#define vidupq_m_n_u8 __arm_vidupq_m_n_u8
#define vidupq_m_wb_u16 __arm_vidupq_m_wb_u16
#define vidupq_m_wb_u32 __arm_vidupq_m_wb_u32
#define vidupq_m_wb_u8 __arm_vidupq_m_wb_u8
#define vidupq_n_u16 __arm_vidupq_n_u16
#define vidupq_n_u32 __arm_vidupq_n_u32
#define vidupq_n_u8 __arm_vidupq_n_u8
#define vidupq_wb_u16 __arm_vidupq_wb_u16
#define vidupq_wb_u32 __arm_vidupq_wb_u32
#define vidupq_wb_u8 __arm_vidupq_wb_u8
#define viwdupq_m_n_u16 __arm_viwdupq_m_n_u16
#define viwdupq_m_n_u32 __arm_viwdupq_m_n_u32
#define viwdupq_m_n_u8 __arm_viwdupq_m_n_u8
#define viwdupq_m_wb_u16 __arm_viwdupq_m_wb_u16
#define viwdupq_m_wb_u32 __arm_viwdupq_m_wb_u32
#define viwdupq_m_wb_u8 __arm_viwdupq_m_wb_u8
#define viwdupq_n_u16 __arm_viwdupq_n_u16
#define viwdupq_n_u32 __arm_viwdupq_n_u32
#define viwdupq_n_u8 __arm_viwdupq_n_u8
#define viwdupq_wb_u16 __arm_viwdupq_wb_u16
#define viwdupq_wb_u32 __arm_viwdupq_wb_u32
#define viwdupq_wb_u8 __arm_viwdupq_wb_u8
#define vmaxavq_p_s16 __arm_vmaxavq_p_s16
#define vmaxavq_p_s32 __arm_vmaxavq_p_s32
#define vmaxavq_p_s8 __arm_vmaxavq_p_s8
#define vmaxavq_s16 __arm_vmaxavq_s16
#define vmaxavq_s32 __arm_vmaxavq_s32
#define vmaxavq_s8 __arm_vmaxavq_s8
#define vmaxvq_p_s16 __arm_vmaxvq_p_s16
#define vmaxvq_p_s32 __arm_vmaxvq_p_s32
#define vmaxvq_p_s8 __arm_vmaxvq_p_s8
#define vmaxvq_p_u16 __arm_vmaxvq_p_u16
#define vmaxvq_p_u32 __arm_vmaxvq_p_u32
#define vmaxvq_p_u8 __arm_vmaxvq_p_u8
#define vminavq_p_s16 __arm_vminavq_p_s16
#define vminavq_p_s32 __arm_vminavq_p_s32
#define vminavq_p_s8 __arm_vminavq_p_s8
#define vminavq_s16 __arm_vminavq_s16
#define vminavq_s32 __arm_vminavq_s32
#define vminavq_s8 __arm_vminavq_s8
#define vminvq_p_s16 __arm_vminvq_p_s16
#define vminvq_p_s32 __arm_vminvq_p_s32
#define vminvq_p_s8 __arm_vminvq_p_s8
#define vminvq_p_u16 __arm_vminvq_p_u16
#define vminvq_p_u32 __arm_vminvq_p_u32
#define vminvq_p_u8 __arm_vminvq_p_u8
#define vmlaq_m_n_s16 __arm_vmlaq_m_n_s16
#define vmlaq_m_n_s32 __arm_vmlaq_m_n_s32
#define vmlaq_m_n_s8 __arm_vmlaq_m_n_s8
#define vmlaq_m_n_u16 __arm_vmlaq_m_n_u16
#define vmlaq_m_n_u32 __arm_vmlaq_m_n_u32
#define vmlaq_m_n_u8 __arm_vmlaq_m_n_u8
#define vmlaq_n_s16 __arm_vmlaq_n_s16
#define vmlaq_n_s32 __arm_vmlaq_n_s32
#define vmlaq_n_s8 __arm_vmlaq_n_s8
#define vmlaq_n_u16 __arm_vmlaq_n_u16
#define vmlaq_n_u32 __arm_vmlaq_n_u32
#define vmlaq_n_u8 __arm_vmlaq_n_u8
#define vmlasq_m_n_s16 __arm_vmlasq_m_n_s16
#define vmlasq_m_n_s32 __arm_vmlasq_m_n_s32
#define vmlasq_m_n_s8 __arm_vmlasq_m_n_s8
#define vmlasq_m_n_u16 __arm_vmlasq_m_n_u16
#define vmlasq_m_n_u32 __arm_vmlasq_m_n_u32
#define vmlasq_m_n_u8 __arm_vmlasq_m_n_u8
#define vmlasq_n_s16 __arm_vmlasq_n_s16
#define vmlasq_n_s32 __arm_vmlasq_n_s32
#define vmlasq_n_s8 __arm_vmlasq_n_s8
#define vmlasq_n_u16 __arm_vmlasq_n_u16
#define vmlasq_n_u32 __arm_vmlasq_n_u32
#define vmlasq_n_u8 __arm_vmlasq_n_u8
#define vmovlbq_m_s16 __arm_vmovlbq_m_s16
#define vmovlbq_m_s8 __arm_vmovlbq_m_s8
#define vmovlbq_m_u16 __arm_vmovlbq_m_u16
#define vmovlbq_m_u8 __arm_vmovlbq_m_u8
#define vmovlbq_s16 __arm_vmovlbq_s16
#define vmovlbq_s8 __arm_vmovlbq_s8
#define vmovlbq_u16 __arm_vmovlbq_u16
#define vmovlbq_u8 __arm_vmovlbq_u8
#define vmovltq_m_s16 __arm_vmovltq_m_s16
#define vmovltq_m_s8 __arm_vmovltq_m_s8
#define vmovltq_m_u16 __arm_vmovltq_m_u16
#define vmovltq_m_u8 __arm_vmovltq_m_u8
#define vmovltq_s16 __arm_vmovltq_s16
#define vmovltq_s8 __arm_vmovltq_s8
#define vmovltq_u16 __arm_vmovltq_u16
#define vmovltq_u8 __arm_vmovltq_u8
#define vmovnbq_m_s16 __arm_vmovnbq_m_s16
#define vmovnbq_m_s32 __arm_vmovnbq_m_s32
#define vmovnbq_m_u16 __arm_vmovnbq_m_u16
#define vmovnbq_m_u32 __arm_vmovnbq_m_u32
#define vmovnbq_s16 __arm_vmovnbq_s16
#define vmovnbq_s32 __arm_vmovnbq_s32
#define vmovnbq_u16 __arm_vmovnbq_u16
#define vmovnbq_u32 __arm_vmovnbq_u32
#define vmovntq_m_s16 __arm_vmovntq_m_s16
#define vmovntq_m_s32 __arm_vmovntq_m_s32
#define vmovntq_m_u16 __arm_vmovntq_m_u16
#define vmovntq_m_u32 __arm_vmovntq_m_u32
#define vmovntq_s16 __arm_vmovntq_s16
#define vmovntq_s32 __arm_vmovntq_s32
#define vmovntq_u16 __arm_vmovntq_u16
#define vmovntq_u32 __arm_vmovntq_u32
#define vmulq_m_n_s16 __arm_vmulq_m_n_s16
#define vmulq_m_n_s32 __arm_vmulq_m_n_s32
#define vmulq_m_n_s8 __arm_vmulq_m_n_s8
#define vmulq_m_n_u16 __arm_vmulq_m_n_u16
#define vmulq_m_n_u32 __arm_vmulq_m_n_u32
#define vmulq_m_n_u8 __arm_vmulq_m_n_u8
#define vmulq_n_s16 __arm_vmulq_n_s16
#define vmulq_n_s32 __arm_vmulq_n_s32
#define vmulq_n_s8 __arm_vmulq_n_s8
#define vmulq_n_u16 __arm_vmulq_n_u16
#define vmulq_n_u32 __arm_vmulq_n_u32
#define vmulq_n_u8 __arm_vmulq_n_u8
#define vmvnq_m_s16 __arm_vmvnq_m_s16
#define vmvnq_m_s32 __arm_vmvnq_m_s32
#define vmvnq_m_s8 __arm_vmvnq_m_s8
#define vmvnq_m_u16 __arm_vmvnq_m_u16
#define vmvnq_m_u32 __arm_vmvnq_m_u32
#define vmvnq_m_u8 __arm_vmvnq_m_u8
#define vmvnq_s16 __arm_vmvnq_s16
#define vmvnq_s32 __arm_vmvnq_s32
#define vmvnq_s8 __arm_vmvnq_s8
#define vmvnq_u16 __arm_vmvnq_u16
#define vmvnq_u32 __arm_vmvnq_u32
#define vmvnq_u8 __arm_vmvnq_u8
#define vnegq_m_s16 __arm_vnegq_m_s16
#define vnegq_m_s32 __arm_vnegq_m_s32
#define vnegq_m_s8 __arm_vnegq_m_s8
#define vnegq_s16 __arm_vnegq_s16
#define vnegq_s32 __arm_vnegq_s32
#define vnegq_s8 __arm_vnegq_s8
#define vqabsq_m_s16 __arm_vqabsq_m_s16
#define vqabsq_m_s32 __arm_vqabsq_m_s32
#define vqabsq_m_s8 __arm_vqabsq_m_s8
#define vqabsq_s16 __arm_vqabsq_s16
#define vqabsq_s32 __arm_vqabsq_s32
#define vqabsq_s8 __arm_vqabsq_s8
#define vqaddq_m_n_s16 __arm_vqaddq_m_n_s16
#define vqaddq_m_n_s32 __arm_vqaddq_m_n_s32
#define vqaddq_m_n_s8 __arm_vqaddq_m_n_s8
#define vqaddq_m_n_u16 __arm_vqaddq_m_n_u16
#define vqaddq_m_n_u32 __arm_vqaddq_m_n_u32
#define vqaddq_m_n_u8 __arm_vqaddq_m_n_u8
#define vqaddq_n_s16 __arm_vqaddq_n_s16
#define vqaddq_n_s32 __arm_vqaddq_n_s32
#define vqaddq_n_s8 __arm_vqaddq_n_s8
#define vqaddq_n_u16 __arm_vqaddq_n_u16
#define vqaddq_n_u32 __arm_vqaddq_n_u32
#define vqaddq_n_u8 __arm_vqaddq_n_u8
#define vqdmladhq_m_s16 __arm_vqdmladhq_m_s16
#define vqdmladhq_m_s32 __arm_vqdmladhq_m_s32
#define vqdmladhq_m_s8 __arm_vqdmladhq_m_s8
#define vqdmladhq_s16 __arm_vqdmladhq_s16
#define vqdmladhq_s32 __arm_vqdmladhq_s32
#define vqdmladhq_s8 __arm_vqdmladhq_s8
#define vqdmladhxq_m_s16 __arm_vqdmladhxq_m_s16
#define vqdmladhxq_m_s32 __arm_vqdmladhxq_m_s32
#define vqdmladhxq_m_s8 __arm_vqdmladhxq_m_s8
#define vqdmladhxq_s16 __arm_vqdmladhxq_s16
#define vqdmladhxq_s32 __arm_vqdmladhxq_s32
#define vqdmladhxq_s8 __arm_vqdmladhxq_s8
#define vqdmlahq_m_n_s16 __arm_vqdmlahq_m_n_s16
#define vqdmlahq_m_n_s32 __arm_vqdmlahq_m_n_s32
#define vqdmlahq_m_n_s8 __arm_vqdmlahq_m_n_s8
#define vqdmlahq_n_s16 __arm_vqdmlahq_n_s16
#define vqdmlahq_n_s32 __arm_vqdmlahq_n_s32
#define vqdmlahq_n_s8 __arm_vqdmlahq_n_s8
#define vqdmlsdhq_m_s16 __arm_vqdmlsdhq_m_s16
#define vqdmlsdhq_m_s32 __arm_vqdmlsdhq_m_s32
#define vqdmlsdhq_m_s8 __arm_vqdmlsdhq_m_s8
#define vqdmlsdhq_s16 __arm_vqdmlsdhq_s16
#define vqdmlsdhq_s32 __arm_vqdmlsdhq_s32
#define vqdmlsdhq_s8 __arm_vqdmlsdhq_s8
#define vqdmlsdhxq_m_s16 __arm_vqdmlsdhxq_m_s16
#define vqdmlsdhxq_m_s32 __arm_vqdmlsdhxq_m_s32
#define vqdmlsdhxq_m_s8 __arm_vqdmlsdhxq_m_s8
#define vqdmlsdhxq_s16 __arm_vqdmlsdhxq_s16
#define vqdmlsdhxq_s32 __arm_vqdmlsdhxq_s32
#define vqdmlsdhxq_s8 __arm_vqdmlsdhxq_s8
#define vqdmulhq_m_n_s16 __arm_vqdmulhq_m_n_s16
#define vqdmulhq_m_n_s32 __arm_vqdmulhq_m_n_s32
#define vqdmulhq_m_n_s8 __arm_vqdmulhq_m_n_s8
#define vqdmulhq_n_s16 __arm_vqdmulhq_n_s16
#define vqdmulhq_n_s32 __arm_vqdmulhq_n_s32
#define vqdmulhq_n_s8 __arm_vqdmulhq_n_s8
#define vqdmullbq_m_n_s16 __arm_vqdmullbq_m_n_s16
#define vqdmullbq_m_n_s32 __arm_vqdmullbq_m_n_s32
#define vqdmullbq_m_s16 __arm_vqdmullbq_m_s16
#define vqdmullbq_m_s32 __arm_vqdmullbq_m_s32
#define vqdmullbq_n_s16 __arm_vqdmullbq_n_s16
#define vqdmullbq_n_s32 __arm_vqdmullbq_n_s32
#define vqdmullbq_s16 __arm_vqdmullbq_s16
#define vqdmullbq_s32 __arm_vqdmullbq_s32
#define vqdmulltq_m_n_s16 __arm_vqdmulltq_m_n_s16
#define vqdmulltq_m_n_s32 __arm_vqdmulltq_m_n_s32
#define vqdmulltq_m_s16 __arm_vqdmulltq_m_s16
#define vqdmulltq_m_s32 __arm_vqdmulltq_m_s32
#define vqdmulltq_n_s16 __arm_vqdmulltq_n_s16
#define vqdmulltq_n_s32 __arm_vqdmulltq_n_s32
#define vqdmulltq_s16 __arm_vqdmulltq_s16
#define vqdmulltq_s32 __arm_vqdmulltq_s32
#define vqmovnbq_m_s16 __arm_vqmovnbq_m_s16
#define vqmovnbq_m_s32 __arm_vqmovnbq_m_s32
#define vqmovnbq_m_u16 __arm_vqmovnbq_m_u16
#define vqmovnbq_m_u32 __arm_vqmovnbq_m_u32
#define vqmovnbq_s16 __arm_vqmovnbq_s16
#define vqmovnbq_s32 __arm_vqmovnbq_s32
#define vqmovnbq_u16 __arm_vqmovnbq_u16
#define vqmovnbq_u32 __arm_vqmovnbq_u32
#define vqmovntq_m_s16 __arm_vqmovntq_m_s16
#define vqmovntq_m_s32 __arm_vqmovntq_m_s32
#define vqmovntq_m_u16 __arm_vqmovntq_m_u16
#define vqmovntq_m_u32 __arm_vqmovntq_m_u32
#define vqmovntq_s16 __arm_vqmovntq_s16
#define vqmovntq_s32 __arm_vqmovntq_s32
#define vqmovntq_u16 __arm_vqmovntq_u16
#define vqmovntq_u32 __arm_vqmovntq_u32
#define vqmovunbq_m_s16 __arm_vqmovunbq_m_s16
#define vqmovunbq_m_s32 __arm_vqmovunbq_m_s32
#define vqmovunbq_s16 __arm_vqmovunbq_s16
#define vqmovunbq_s32 __arm_vqmovunbq_s32
#define vqmovuntq_m_s16 __arm_vqmovuntq_m_s16
#define vqmovuntq_m_s32 __arm_vqmovuntq_m_s32
#define vqmovuntq_s16 __arm_vqmovuntq_s16
#define vqmovuntq_s32 __arm_vqmovuntq_s32
#define vqnegq_m_s16 __arm_vqnegq_m_s16
#define vqnegq_m_s32 __arm_vqnegq_m_s32
#define vqnegq_m_s8 __arm_vqnegq_m_s8
#define vqnegq_s16 __arm_vqnegq_s16
#define vqnegq_s32 __arm_vqnegq_s32
#define vqnegq_s8 __arm_vqnegq_s8
#define vqrdmladhq_m_s16 __arm_vqrdmladhq_m_s16
#define vqrdmladhq_m_s32 __arm_vqrdmladhq_m_s32
#define vqrdmladhq_m_s8 __arm_vqrdmladhq_m_s8
#define vqrdmladhq_s16 __arm_vqrdmladhq_s16
#define vqrdmladhq_s32 __arm_vqrdmladhq_s32
#define vqrdmladhq_s8 __arm_vqrdmladhq_s8
#define vqrdmladhxq_m_s16 __arm_vqrdmladhxq_m_s16
#define vqrdmladhxq_m_s32 __arm_vqrdmladhxq_m_s32
#define vqrdmladhxq_m_s8 __arm_vqrdmladhxq_m_s8
#define vqrdmladhxq_s16 __arm_vqrdmladhxq_s16
#define vqrdmladhxq_s32 __arm_vqrdmladhxq_s32
#define vqrdmladhxq_s8 __arm_vqrdmladhxq_s8
#define vqrdmlahq_m_n_s16 __arm_vqrdmlahq_m_n_s16
#define vqrdmlahq_m_n_s32 __arm_vqrdmlahq_m_n_s32
#define vqrdmlahq_m_n_s8 __arm_vqrdmlahq_m_n_s8
#define vqrdmlahq_n_s16 __arm_vqrdmlahq_n_s16
#define vqrdmlahq_n_s32 __arm_vqrdmlahq_n_s32
#define vqrdmlahq_n_s8 __arm_vqrdmlahq_n_s8
#define vqrdmlashq_m_n_s16 __arm_vqrdmlashq_m_n_s16
#define vqrdmlashq_m_n_s32 __arm_vqrdmlashq_m_n_s32
#define vqrdmlashq_m_n_s8 __arm_vqrdmlashq_m_n_s8
#define vqrdmlashq_n_s16 __arm_vqrdmlashq_n_s16
#define vqrdmlashq_n_s32 __arm_vqrdmlashq_n_s32
#define vqrdmlashq_n_s8 __arm_vqrdmlashq_n_s8
#define vqrdmlsdhq_m_s16 __arm_vqrdmlsdhq_m_s16
#define vqrdmlsdhq_m_s32 __arm_vqrdmlsdhq_m_s32
#define vqrdmlsdhq_m_s8 __arm_vqrdmlsdhq_m_s8
#define vqrdmlsdhq_s16 __arm_vqrdmlsdhq_s16
#define vqrdmlsdhq_s32 __arm_vqrdmlsdhq_s32
#define vqrdmlsdhq_s8 __arm_vqrdmlsdhq_s8
#define vqrdmlsdhxq_m_s16 __arm_vqrdmlsdhxq_m_s16
#define vqrdmlsdhxq_m_s32 __arm_vqrdmlsdhxq_m_s32
#define vqrdmlsdhxq_m_s8 __arm_vqrdmlsdhxq_m_s8
#define vqrdmlsdhxq_s16 __arm_vqrdmlsdhxq_s16
#define vqrdmlsdhxq_s32 __arm_vqrdmlsdhxq_s32
#define vqrdmlsdhxq_s8 __arm_vqrdmlsdhxq_s8
#define vqrdmulhq_m_n_s16 __arm_vqrdmulhq_m_n_s16
#define vqrdmulhq_m_n_s32 __arm_vqrdmulhq_m_n_s32
#define vqrdmulhq_m_n_s8 __arm_vqrdmulhq_m_n_s8
#define vqrdmulhq_n_s16 __arm_vqrdmulhq_n_s16
#define vqrdmulhq_n_s32 __arm_vqrdmulhq_n_s32
#define vqrdmulhq_n_s8 __arm_vqrdmulhq_n_s8
#define vqsubq_m_n_s16 __arm_vqsubq_m_n_s16
#define vqsubq_m_n_s32 __arm_vqsubq_m_n_s32
#define vqsubq_m_n_s8 __arm_vqsubq_m_n_s8
#define vqsubq_m_n_u16 __arm_vqsubq_m_n_u16
#define vqsubq_m_n_u32 __arm_vqsubq_m_n_u32
#define vqsubq_m_n_u8 __arm_vqsubq_m_n_u8
#define vqsubq_n_s16 __arm_vqsubq_n_s16
#define vqsubq_n_s32 __arm_vqsubq_n_s32
#define vqsubq_n_s8 __arm_vqsubq_n_s8
#define vqsubq_n_u16 __arm_vqsubq_n_u16
#define vqsubq_n_u32 __arm_vqsubq_n_u32
#define vqsubq_n_u8 __arm_vqsubq_n_u8
#define vrev16q_m_s8 __arm_vrev16q_m_s8
#define vrev16q_m_u8 __arm_vrev16q_m_u8
#define vrev16q_s8 __arm_vrev16q_s8
#define vrev16q_u8 __arm_vrev16q_u8
#define vrev32q_m_s16 __arm_vrev32q_m_s16
#define vrev32q_m_s8 __arm_vrev32q_m_s8
#define vrev32q_m_u16 __arm_vrev32q_m_u16
#define vrev32q_m_u8 __arm_vrev32q_m_u8
#define vrev32q_s16 __arm_vrev32q_s16
#define vrev32q_s8 __arm_vrev32q_s8
#define vrev32q_u16 __arm_vrev32q_u16
#define vrev32q_u8 __arm_vrev32q_u8
#define vrev64q_m_s16 __arm_vrev64q_m_s16
#define vrev64q_m_s32 __arm_vrev64q_m_s32
#define vrev64q_m_s8 __arm_vrev64q_m_s8
#define vrev64q_m_u16 __arm_vrev64q_m_u16
#define vrev64q_m_u32 __arm_vrev64q_m_u32
#define vrev64q_m_u8 __arm_vrev64q_m_u8
#define vrev64q_s16 __arm_vrev64q_s16
#define vrev64q_s32 __arm_vrev64q_s32
#define vrev64q_s8 __arm_vrev64q_s8
#define vrev64q_u16 __arm_vrev64q_u16
#define vrev64q_u32 __arm_vrev64q_u32
#define vrev64q_u8 __arm_vrev64q_u8
#define vsbciq_m_s32 __arm_vsbciq_m_s32
#define vsbciq_m_u32 __arm_vsbciq_m_u32
#define vsbciq_s32 __arm_vsbciq_s32
#define vsbciq_u32 __arm_vsbciq_u32
#define vsbcq_m_s32 __arm_vsbcq_m_s32
#define vsbcq_m_u32 __arm_vsbcq_m_u32
#define vsbcq_s32 __arm_vsbcq_s32
#define vsbcq_u32 __arm_vsbcq_u32
#define vshlcq_m_s16 __arm_vshlcq_m_s16
#define vshlcq_m_s32 __arm_vshlcq_m_s32
#define vshlcq_m_s8 __arm_vshlcq_m_s8
#define vshlcq_m_u16 __arm_vshlcq_m_u16
#define vshlcq_m_u32 __arm_vshlcq_m_u32
#define vshlcq_m_u8 __arm_vshlcq_m_u8
#define vshlcq_s16 __arm_vshlcq_s16
#define vshlcq_s32 __arm_vshlcq_s32
#define vshlcq_s8 __arm_vshlcq_s8
#define vshlcq_u16 __arm_vshlcq_u16
#define vshlcq_u32 __arm_vshlcq_u32
#define vshlcq_u8 __arm_vshlcq_u8
#define vsubq_m_n_s16 __arm_vsubq_m_n_s16
#define vsubq_m_n_s32 __arm_vsubq_m_n_s32
#define vsubq_m_n_s8 __arm_vsubq_m_n_s8
#define vsubq_m_n_u16 __arm_vsubq_m_n_u16
#define vsubq_m_n_u32 __arm_vsubq_m_n_u32
#define vsubq_m_n_u8 __arm_vsubq_m_n_u8
#define vsubq_n_s16 __arm_vsubq_n_s16
#define vsubq_n_s32 __arm_vsubq_n_s32
#define vsubq_n_s8 __arm_vsubq_n_s8
#define vsubq_n_u16 __arm_vsubq_n_u16
#define vsubq_n_u32 __arm_vsubq_n_u32
#define vsubq_n_u8 __arm_vsubq_n_u8
#define vabsq __arm_vabsq
#define vabsq_m __arm_vabsq_m
#define vaddlvaq __arm_vaddlvaq
#define vaddlvaq_p __arm_vaddlvaq_p
#define vaddlvq __arm_vaddlvq
#define vaddlvq_p __arm_vaddlvq_p
#define vaddq __arm_vaddq
#define vaddq_m __arm_vaddq_m
#define vaddvaq __arm_vaddvaq
#define vaddvaq_p __arm_vaddvaq_p
#define vaddvq __arm_vaddvq
#define vaddvq_p __arm_vaddvq_p
#define vbrsrq __arm_vbrsrq
#define vbrsrq_m __arm_vbrsrq_m
#define vclsq __arm_vclsq
#define vclsq_m __arm_vclsq_m
#define vclzq __arm_vclzq
#define vclzq_m __arm_vclzq_m
#define vddupq_m __arm_vddupq_m
#define vdupq_m __arm_vdupq_m
#define vdwdupq_m __arm_vdwdupq_m
#define vhaddq __arm_vhaddq
#define vhaddq_m __arm_vhaddq_m
#define vhsubq __arm_vhsubq
#define vhsubq_m __arm_vhsubq_m
#define vidupq_m __arm_vidupq_m
#define viwdupq_m __arm_viwdupq_m
#define vmaxavq __arm_vmaxavq
#define vmaxavq_p __arm_vmaxavq_p
#define vmaxvq_p __arm_vmaxvq_p
#define vminavq __arm_vminavq
#define vminavq_p __arm_vminavq_p
#define vminvq_p __arm_vminvq_p
#define vmlaq __arm_vmlaq
#define vmlaq_m __arm_vmlaq_m
#define vmlasq __arm_vmlasq
#define vmlasq_m __arm_vmlasq_m
#define vmovlbq __arm_vmovlbq
#define vmovlbq_m __arm_vmovlbq_m
#define vmovltq __arm_vmovltq
#define vmovltq_m __arm_vmovltq_m
#define vmovnbq __arm_vmovnbq
#define vmovnbq_m __arm_vmovnbq_m
#define vmovntq __arm_vmovntq
#define vmovntq_m __arm_vmovntq_m
#define vmulq __arm_vmulq
#define vmulq_m __arm_vmulq_m
#define vmvnq __arm_vmvnq
#define vmvnq_m __arm_vmvnq_m
#define vnegq __arm_vnegq
#define vnegq_m __arm_vnegq_m
#define vqabsq __arm_vqabsq
#define vqabsq_m __arm_vqabsq_m
#define vqaddq __arm_vqaddq
#define vqaddq_m __arm_vqaddq_m
#define vqdmladhq __arm_vqdmladhq
#define vqdmladhq_m __arm_vqdmladhq_m
#define vqdmladhxq __arm_vqdmladhxq
#define vqdmladhxq_m __arm_vqdmladhxq_m
#define vqdmlahq __arm_vqdmlahq
#define vqdmlahq_m __arm_vqdmlahq_m
#define vqdmlsdhq __arm_vqdmlsdhq
#define vqdmlsdhq_m __arm_vqdmlsdhq_m
#define vqdmlsdhxq __arm_vqdmlsdhxq
#define vqdmlsdhxq_m __arm_vqdmlsdhxq_m
#define vqdmulhq __arm_vqdmulhq
#define vqdmulhq_m __arm_vqdmulhq_m
#define vqdmullbq __arm_vqdmullbq
#define vqdmullbq_m __arm_vqdmullbq_m
#define vqdmulltq __arm_vqdmulltq
#define vqdmulltq_m __arm_vqdmulltq_m
#define vqmovnbq __arm_vqmovnbq
#define vqmovnbq_m __arm_vqmovnbq_m
#define vqmovntq __arm_vqmovntq
#define vqmovntq_m __arm_vqmovntq_m
#define vqmovunbq __arm_vqmovunbq
#define vqmovunbq_m __arm_vqmovunbq_m
#define vqmovuntq __arm_vqmovuntq
#define vqmovuntq_m __arm_vqmovuntq_m
#define vqnegq __arm_vqnegq
#define vqnegq_m __arm_vqnegq_m
#define vqrdmladhq __arm_vqrdmladhq
#define vqrdmladhq_m __arm_vqrdmladhq_m
#define vqrdmladhxq __arm_vqrdmladhxq
#define vqrdmladhxq_m __arm_vqrdmladhxq_m
#define vqrdmlahq __arm_vqrdmlahq
#define vqrdmlahq_m __arm_vqrdmlahq_m
#define vqrdmlashq __arm_vqrdmlashq
#define vqrdmlashq_m __arm_vqrdmlashq_m
#define vqrdmlsdhq __arm_vqrdmlsdhq
#define vqrdmlsdhq_m __arm_vqrdmlsdhq_m
#define vqrdmlsdhxq __arm_vqrdmlsdhxq
#define vqrdmlsdhxq_m __arm_vqrdmlsdhxq_m
#define vqrdmulhq __arm_vqrdmulhq
#define vqrdmulhq_m __arm_vqrdmulhq_m
#define vqsubq __arm_vqsubq
#define vqsubq_m __arm_vqsubq_m
#define vrev16q __arm_vrev16q
#define vrev16q_m __arm_vrev16q_m
#define vrev32q __arm_vrev32q
#define vrev32q_m __arm_vrev32q_m
#define vrev64q __arm_vrev64q
#define vrev64q_m __arm_vrev64q_m
#define vsbciq __arm_vsbciq
#define vsbciq_m __arm_vsbciq_m
#define vsbcq __arm_vsbcq
#define vsbcq_m __arm_vsbcq_m
#define vshlcq __arm_vshlcq
#define vshlcq_m __arm_vshlcq_m
#define vsubq __arm_vsubq
#define vsubq_m __arm_vsubq_m
#define vidupq_u8 __arm_vidupq_u8
#define vidupq_u16 __arm_vidupq_u16
#define vidupq_u32 __arm_vidupq_u32
#define viwdupq_u8 __arm_viwdupq_u8
#define viwdupq_u16 __arm_viwdupq_u16
#define viwdupq_u32 __arm_viwdupq_u32
#define vddupq_u8 __arm_vddupq_u8
#define vddupq_u16 __arm_vddupq_u16
#define vddupq_u32 __arm_vddupq_u32
#define vdwdupq_u8 __arm_vdwdupq_u8
#define vdwdupq_u16 __arm_vdwdupq_u16
#define vdwdupq_u32 __arm_vdwdupq_u32

#if (__ARM_FEATURE_MVE & 2) /* MVE floating point */

#define vabsq_f16 __arm_vabsq_f16
#define vabsq_f32 __arm_vabsq_f32
#define vabsq_m_f16 __arm_vabsq_m_f16
#define vabsq_m_f32 __arm_vabsq_m_f32
#define vaddq_m_n_f16 __arm_vaddq_m_n_f16
#define vaddq_m_n_f32 __arm_vaddq_m_n_f32
#define vaddq_n_f16 __arm_vaddq_n_f16
#define vaddq_n_f32 __arm_vaddq_n_f32
#define vbrsrq_m_n_f16 __arm_vbrsrq_m_n_f16
#define vbrsrq_m_n_f32 __arm_vbrsrq_m_n_f32
#define vbrsrq_n_f16 __arm_vbrsrq_n_f16
#define vbrsrq_n_f32 __arm_vbrsrq_n_f32
#define vcvtaq_m_s16_f16 __arm_vcvtaq_m_s16_f16
#define vcvtaq_m_s32_f32 __arm_vcvtaq_m_s32_f32
#define vcvtaq_m_u16_f16 __arm_vcvtaq_m_u16_f16
#define vcvtaq_m_u32_f32 __arm_vcvtaq_m_u32_f32
#define vcvtaq_s16_f16 __arm_vcvtaq_s16_f16
#define vcvtaq_s32_f32 __arm_vcvtaq_s32_f32
#define vcvtaq_u16_f16 __arm_vcvtaq_u16_f16
#define vcvtaq_u32_f32 __arm_vcvtaq_u32_f32
#define vcvtbq_f32_f16 __arm_vcvtbq_f32_f16
#define vcvtbq_m_f32_f16 __arm_vcvtbq_m_f32_f16
#define vcvtmq_m_s16_f16 __arm_vcvtmq_m_s16_f16
#define vcvtmq_m_s32_f32 __arm_vcvtmq_m_s32_f32
#define vcvtmq_m_u16_f16 __arm_vcvtmq_m_u16_f16
#define vcvtmq_m_u32_f32 __arm_vcvtmq_m_u32_f32
#define vcvtmq_s16_f16 __arm_vcvtmq_s16_f16
#define vcvtmq_s32_f32 __arm_vcvtmq_s32_f32
#define vcvtmq_u16_f16 __arm_vcvtmq_u16_f16
#define vcvtmq_u32_f32 __arm_vcvtmq_u32_f32
#define vcvtnq_m_s16_f16 __arm_vcvtnq_m_s16_f16
#define vcvtnq_m_s32_f32 __arm_vcvtnq_m_s32_f32
#define vcvtnq_m_u16_f16 __arm_vcvtnq_m_u16_f16
#define vcvtnq_m_u32_f32 __arm_vcvtnq_m_u32_f32
#define vcvtnq_s16_f16 __arm_vcvtnq_s16_f16
#define vcvtnq_s32_f32 __arm_vcvtnq_s32_f32
#define vcvtnq_u16_f16 __arm_vcvtnq_u16_f16
#define vcvtnq_u32_f32 __arm_vcvtnq_u32_f32
#define vcvtpq_m_s16_f16 __arm_vcvtpq_m_s16_f16
#define vcvtpq_m_s32_f32 __arm_vcvtpq_m_s32_f32
#define vcvtpq_m_u16_f16 __arm_vcvtpq_m_u16_f16
#define vcvtpq_m_u32_f32 __arm_vcvtpq_m_u32_f32
#define vcvtpq_s16_f16 __arm_vcvtpq_s16_f16
#define vcvtpq_s32_f32 __arm_vcvtpq_s32_f32
#define vcvtpq_u16_f16 __arm_vcvtpq_u16_f16
#define vcvtpq_u32_f32 __arm_vcvtpq_u32_f32
#define vcvtq_f16_s16 __arm_vcvtq_f16_s16
#define vcvtq_f16_u16 __arm_vcvtq_f16_u16
#define vcvtq_f32_s32 __arm_vcvtq_f32_s32
#define vcvtq_f32_u32 __arm_vcvtq_f32_u32
#define vcvtq_m_f16_s16 __arm_vcvtq_m_f16_s16
#define vcvtq_m_f16_u16 __arm_vcvtq_m_f16_u16
#define vcvtq_m_f32_s32 __arm_vcvtq_m_f32_s32
#define vcvtq_m_f32_u32 __arm_vcvtq_m_f32_u32
#define vcvtq_m_n_f16_s16 __arm_vcvtq_m_n_f16_s16
#define vcvtq_m_n_f16_u16 __arm_vcvtq_m_n_f16_u16
#define vcvtq_m_n_f32_s32 __arm_vcvtq_m_n_f32_s32
#define vcvtq_m_n_f32_u32 __arm_vcvtq_m_n_f32_u32
#define vcvtq_m_n_s16_f16 __arm_vcvtq_m_n_s16_f16
#define vcvtq_m_n_s32_f32 __arm_vcvtq_m_n_s32_f32
#define vcvtq_m_n_u16_f16 __arm_vcvtq_m_n_u16_f16
#define vcvtq_m_n_u32_f32 __arm_vcvtq_m_n_u32_f32
#define vcvtq_m_s16_f16 __arm_vcvtq_m_s16_f16
#define vcvtq_m_s32_f32 __arm_vcvtq_m_s32_f32
#define vcvtq_m_u16_f16 __arm_vcvtq_m_u16_f16
#define vcvtq_m_u32_f32 __arm_vcvtq_m_u32_f32
#define vcvtq_n_f16_s16 __arm_vcvtq_n_f16_s16
#define vcvtq_n_f16_u16 __arm_vcvtq_n_f16_u16
#define vcvtq_n_f32_s32 __arm_vcvtq_n_f32_s32
#define vcvtq_n_f32_u32 __arm_vcvtq_n_f32_u32
#define vcvtq_n_s16_f16 __arm_vcvtq_n_s16_f16
#define vcvtq_n_s32_f32 __arm_vcvtq_n_s32_f32
#define vcvtq_n_u16_f16 __arm_vcvtq_n_u16_f16
#define vcvtq_n_u32_f32 __arm_vcvtq_n_u32_f32
#define vcvtq_s16_f16 __arm_vcvtq_s16_f16
#define vcvtq_s32_f32 __arm_vcvtq_s32_f32
#define vcvtq_u16_f16 __arm_vcvtq_u16_f16
#define vcvtq_u32_f32 __arm_vcvtq_u32_f32
#define vcvttq_f32_f16 __arm_vcvttq_f32_f16
#define vcvttq_m_f32_f16 __arm_vcvttq_m_f32_f16
#define vdupq_m_n_f16 __arm_vdupq_m_n_f16
#define vdupq_m_n_f32 __arm_vdupq_m_n_f32
#define vdupq_n_f16 __arm_vdupq_n_f16
#define vdupq_n_f32 __arm_vdupq_n_f32
#define vfmaq_f16 __arm_vfmaq_f16
#define vfmaq_f32 __arm_vfmaq_f32
#define vfmaq_m_f16 __arm_vfmaq_m_f16
#define vfmaq_m_f32 __arm_vfmaq_m_f32
#define vfmaq_m_n_f16 __arm_vfmaq_m_n_f16
#define vfmaq_m_n_f32 __arm_vfmaq_m_n_f32
#define vfmaq_n_f16 __arm_vfmaq_n_f16
#define vfmaq_n_f32 __arm_vfmaq_n_f32
#define vfmasq_m_n_f16 __arm_vfmasq_m_n_f16
#define vfmasq_m_n_f32 __arm_vfmasq_m_n_f32
#define vfmasq_n_f16 __arm_vfmasq_n_f16
#define vfmasq_n_f32 __arm_vfmasq_n_f32
#define vfmsq_f16 __arm_vfmsq_f16
#define vfmsq_f32 __arm_vfmsq_f32
#define vfmsq_m_f16 __arm_vfmsq_m_f16
#define vfmsq_m_f32 __arm_vfmsq_m_f32
#define vmaxnmavq_f16 __arm_vmaxnmavq_f16
#define vmaxnmavq_f32 __arm_vmaxnmavq_f32
#define vmaxnmavq_p_f16 __arm_vmaxnmavq_p_f16
#define vmaxnmavq_p_f32 __arm_vmaxnmavq_p_f32
#define vmaxnmvq_f16 __arm_vmaxnmvq_f16
#define vmaxnmvq_f32 __arm_vmaxnmvq_f32
#define vmaxnmvq_p_f16 __arm_vmaxnmvq_p_f16
#define vmaxnmvq_p_f32 __arm_vmaxnmvq_p_f32
#define vminnmavq_f16 __arm_vminnmavq_f16
#define vminnmavq_f32 __arm_vminnmavq_f32
#define vminnmavq_p_f16 __arm_vminnmavq_p_f16
#define vminnmavq_p_f32 __arm_vminnmavq_p_f32
#define vminnmvq_f16 __arm_vminnmvq_f16
#define vminnmvq_f32 __arm_vminnmvq_f32
#define vminnmvq_p_f16 __arm_vminnmvq_p_f16
#define vminnmvq_p_f32 __arm_vminnmvq_p_f32
#define vmulq_m_n_f16 __arm_vmulq_m_n_f16
#define vmulq_m_n_f32 __arm_vmulq_m_n_f32
#define vmulq_n_f16 __arm_vmulq_n_f16
#define vmulq_n_f32 __arm_vmulq_n_f32
#define vnegq_f16 __arm_vnegq_f16
#define vnegq_f32 __arm_vnegq_f32
#define vnegq_m_f16 __arm_vnegq_m_f16
#define vnegq_m_f32 __arm_vnegq_m_f32
#define vrev32q_f16 __arm_vrev32q_f16
#define vrev32q_m_f16 __arm_vrev32q_m_f16
#define vrev64q_f16 __arm_vrev64q_f16
#define vrev64q_f32 __arm_vrev64q_f32
#define vrev64q_m_f16 __arm_vrev64q_m_f16
#define vrev64q_m_f32 __arm_vrev64q_m_f32
#define vrndaq_f16 __arm_vrndaq_f16
#define vrndaq_f32 __arm_vrndaq_f32
#define vrndaq_m_f16 __arm_vrndaq_m_f16
#define vrndaq_m_f32 __arm_vrndaq_m_f32
#define vrndmq_f16 __arm_vrndmq_f16
#define vrndmq_f32 __arm_vrndmq_f32
#define vrndmq_m_f16 __arm_vrndmq_m_f16
#define vrndmq_m_f32 __arm_vrndmq_m_f32
#define vrndnq_f16 __arm_vrndnq_f16
#define vrndnq_f32 __arm_vrndnq_f32
#define vrndnq_m_f16 __arm_vrndnq_m_f16
#define vrndnq_m_f32 __arm_vrndnq_m_f32
#define vrndpq_f16 __arm_vrndpq_f16
#define vrndpq_f32 __arm_vrndpq_f32
#define vrndpq_m_f16 __arm_vrndpq_m_f16
#define vrndpq_m_f32 __arm_vrndpq_m_f32
#define vrndq_f16 __arm_vrndq_f16
#define vrndq_f32 __arm_vrndq_f32
#define vrndq_m_f16 __arm_vrndq_m_f16
#define vrndq_m_f32 __arm_vrndq_m_f32
#define vrndxq_f16 __arm_vrndxq_f16
#define vrndxq_f32 __arm_vrndxq_f32
#define vrndxq_m_f16 __arm_vrndxq_m_f16
#define vrndxq_m_f32 __arm_vrndxq_m_f32
#define vsubq_m_n_f16 __arm_vsubq_m_n_f16
#define vsubq_m_n_f32 __arm_vsubq_m_n_f32
#define vsubq_n_f16 __arm_vsubq_n_f16
#define vsubq_n_f32 __arm_vsubq_n_f32
#define vcvtaq_m __arm_vcvtaq_m
#define vcvtmq_m __arm_vcvtmq_m
#define vcvtnq_m __arm_vcvtnq_m
#define vcvtpq_m __arm_vcvtpq_m
#define vcvtq __arm_vcvtq
#define vcvtq_m __arm_vcvtq_m
#define vcvtq_m_n __arm_vcvtq_m_n
#define vcvtq_n __arm_vcvtq_n
#define vfmaq __arm_vfmaq
#define vfmaq_m __arm_vfmaq_m
#define vfmasq __arm_vfmasq
#define vfmasq_m __arm_vfmasq_m
#define vfmsq __arm_vfmsq
#define vfmsq_m __arm_vfmsq_m
#define vmaxnmavq __arm_vmaxnmavq
#define vmaxnmavq_p __arm_vmaxnmavq_p
#define vmaxnmvq __arm_vmaxnmvq
#define vmaxnmvq_p __arm_vmaxnmvq_p
#define vminnmavq __arm_vminnmavq
#define vminnmavq_p __arm_vminnmavq_p
#define vminnmvq __arm_vminnmvq
#define vminnmvq_p __arm_vminnmvq_p
#define vrndaq __arm_vrndaq
#define vrndaq_m __arm_vrndaq_m
#define vrndmq __arm_vrndmq
#define vrndmq_m __arm_vrndmq_m
#define vrndnq __arm_vrndnq
#define vrndnq_m __arm_vrndnq_m
#define vrndpq __arm_vrndpq
#define vrndpq_m __arm_vrndpq_m
#define vrndq __arm_vrndq
#define vrndq_m __arm_vrndq_m
#define vrndxq __arm_vrndxq
#define vrndxq_m __arm_vrndxq_m

#endif /* MVE floating point */

#endif /* __ARM_MVE_PRESERVE_USER_NAMESPACE */

#endif /* __ARM_MVE_H */
