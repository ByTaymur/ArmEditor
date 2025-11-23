/* Modifications copyright (C) 2020 Arm Limited (or its affiliates). All rights reserved. */
/*===---- __arm_mve_reinterpret.h - ARM MVE vreinterpretq ------------------===
 *
 *
 * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
 * See https://llvm.org/LICENSE.txt for license information.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 *
 *===-----------------------------------------------------------------------===
 */

#ifndef __ARM_MVE_H
#error "This header must be included from arm_mve.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_s32)))
int16x8_t __arm_vreinterpretq_s16_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_s32)))
int16x8_t __arm_vreinterpretq_s16(int32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_s64)))
int16x8_t __arm_vreinterpretq_s16_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_s64)))
int16x8_t __arm_vreinterpretq_s16(int64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_s8)))
int16x8_t __arm_vreinterpretq_s16_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_s8)))
int16x8_t __arm_vreinterpretq_s16(int8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_u16)))
int16x8_t __arm_vreinterpretq_s16_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_u16)))
int16x8_t __arm_vreinterpretq_s16(uint16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_u32)))
int16x8_t __arm_vreinterpretq_s16_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_u32)))
int16x8_t __arm_vreinterpretq_s16(uint32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_u64)))
int16x8_t __arm_vreinterpretq_s16_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_u64)))
int16x8_t __arm_vreinterpretq_s16(uint64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_u8)))
int16x8_t __arm_vreinterpretq_s16_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_u8)))
int16x8_t __arm_vreinterpretq_s16(uint8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_s16)))
int32x4_t __arm_vreinterpretq_s32_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_s16)))
int32x4_t __arm_vreinterpretq_s32(int16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_s64)))
int32x4_t __arm_vreinterpretq_s32_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_s64)))
int32x4_t __arm_vreinterpretq_s32(int64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_s8)))
int32x4_t __arm_vreinterpretq_s32_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_s8)))
int32x4_t __arm_vreinterpretq_s32(int8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_u16)))
int32x4_t __arm_vreinterpretq_s32_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_u16)))
int32x4_t __arm_vreinterpretq_s32(uint16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_u32)))
int32x4_t __arm_vreinterpretq_s32_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_u32)))
int32x4_t __arm_vreinterpretq_s32(uint32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_u64)))
int32x4_t __arm_vreinterpretq_s32_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_u64)))
int32x4_t __arm_vreinterpretq_s32(uint64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_u8)))
int32x4_t __arm_vreinterpretq_s32_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_u8)))
int32x4_t __arm_vreinterpretq_s32(uint8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_s16)))
int64x2_t __arm_vreinterpretq_s64_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_s16)))
int64x2_t __arm_vreinterpretq_s64(int16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_s32)))
int64x2_t __arm_vreinterpretq_s64_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_s32)))
int64x2_t __arm_vreinterpretq_s64(int32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_s8)))
int64x2_t __arm_vreinterpretq_s64_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_s8)))
int64x2_t __arm_vreinterpretq_s64(int8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_u16)))
int64x2_t __arm_vreinterpretq_s64_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_u16)))
int64x2_t __arm_vreinterpretq_s64(uint16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_u32)))
int64x2_t __arm_vreinterpretq_s64_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_u32)))
int64x2_t __arm_vreinterpretq_s64(uint32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_u64)))
int64x2_t __arm_vreinterpretq_s64_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_u64)))
int64x2_t __arm_vreinterpretq_s64(uint64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_u8)))
int64x2_t __arm_vreinterpretq_s64_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_u8)))
int64x2_t __arm_vreinterpretq_s64(uint8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_s16)))
int8x16_t __arm_vreinterpretq_s8_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_s16)))
int8x16_t __arm_vreinterpretq_s8(int16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_s32)))
int8x16_t __arm_vreinterpretq_s8_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_s32)))
int8x16_t __arm_vreinterpretq_s8(int32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_s64)))
int8x16_t __arm_vreinterpretq_s8_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_s64)))
int8x16_t __arm_vreinterpretq_s8(int64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_u16)))
int8x16_t __arm_vreinterpretq_s8_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_u16)))
int8x16_t __arm_vreinterpretq_s8(uint16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_u32)))
int8x16_t __arm_vreinterpretq_s8_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_u32)))
int8x16_t __arm_vreinterpretq_s8(uint32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_u64)))
int8x16_t __arm_vreinterpretq_s8_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_u64)))
int8x16_t __arm_vreinterpretq_s8(uint64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_u8)))
int8x16_t __arm_vreinterpretq_s8_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_u8)))
int8x16_t __arm_vreinterpretq_s8(uint8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_s16)))
uint16x8_t __arm_vreinterpretq_u16_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_s16)))
uint16x8_t __arm_vreinterpretq_u16(int16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_s32)))
uint16x8_t __arm_vreinterpretq_u16_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_s32)))
uint16x8_t __arm_vreinterpretq_u16(int32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_s64)))
uint16x8_t __arm_vreinterpretq_u16_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_s64)))
uint16x8_t __arm_vreinterpretq_u16(int64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_s8)))
uint16x8_t __arm_vreinterpretq_u16_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_s8)))
uint16x8_t __arm_vreinterpretq_u16(int8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_u32)))
uint16x8_t __arm_vreinterpretq_u16_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_u32)))
uint16x8_t __arm_vreinterpretq_u16(uint32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_u64)))
uint16x8_t __arm_vreinterpretq_u16_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_u64)))
uint16x8_t __arm_vreinterpretq_u16(uint64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_u8)))
uint16x8_t __arm_vreinterpretq_u16_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_u8)))
uint16x8_t __arm_vreinterpretq_u16(uint8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_s16)))
uint32x4_t __arm_vreinterpretq_u32_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_s16)))
uint32x4_t __arm_vreinterpretq_u32(int16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_s32)))
uint32x4_t __arm_vreinterpretq_u32_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_s32)))
uint32x4_t __arm_vreinterpretq_u32(int32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_s64)))
uint32x4_t __arm_vreinterpretq_u32_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_s64)))
uint32x4_t __arm_vreinterpretq_u32(int64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_s8)))
uint32x4_t __arm_vreinterpretq_u32_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_s8)))
uint32x4_t __arm_vreinterpretq_u32(int8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_u16)))
uint32x4_t __arm_vreinterpretq_u32_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_u16)))
uint32x4_t __arm_vreinterpretq_u32(uint16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_u64)))
uint32x4_t __arm_vreinterpretq_u32_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_u64)))
uint32x4_t __arm_vreinterpretq_u32(uint64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_u8)))
uint32x4_t __arm_vreinterpretq_u32_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_u8)))
uint32x4_t __arm_vreinterpretq_u32(uint8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_s16)))
uint64x2_t __arm_vreinterpretq_u64_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_s16)))
uint64x2_t __arm_vreinterpretq_u64(int16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_s32)))
uint64x2_t __arm_vreinterpretq_u64_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_s32)))
uint64x2_t __arm_vreinterpretq_u64(int32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_s64)))
uint64x2_t __arm_vreinterpretq_u64_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_s64)))
uint64x2_t __arm_vreinterpretq_u64(int64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_s8)))
uint64x2_t __arm_vreinterpretq_u64_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_s8)))
uint64x2_t __arm_vreinterpretq_u64(int8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_u16)))
uint64x2_t __arm_vreinterpretq_u64_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_u16)))
uint64x2_t __arm_vreinterpretq_u64(uint16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_u32)))
uint64x2_t __arm_vreinterpretq_u64_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_u32)))
uint64x2_t __arm_vreinterpretq_u64(uint32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_u8)))
uint64x2_t __arm_vreinterpretq_u64_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_u8)))
uint64x2_t __arm_vreinterpretq_u64(uint8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_s16)))
uint8x16_t __arm_vreinterpretq_u8_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_s16)))
uint8x16_t __arm_vreinterpretq_u8(int16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_s32)))
uint8x16_t __arm_vreinterpretq_u8_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_s32)))
uint8x16_t __arm_vreinterpretq_u8(int32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_s64)))
uint8x16_t __arm_vreinterpretq_u8_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_s64)))
uint8x16_t __arm_vreinterpretq_u8(int64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_s8)))
uint8x16_t __arm_vreinterpretq_u8_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_s8)))
uint8x16_t __arm_vreinterpretq_u8(int8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_u16)))
uint8x16_t __arm_vreinterpretq_u8_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_u16)))
uint8x16_t __arm_vreinterpretq_u8(uint16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_u32)))
uint8x16_t __arm_vreinterpretq_u8_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_u32)))
uint8x16_t __arm_vreinterpretq_u8(uint32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_u64)))
uint8x16_t __arm_vreinterpretq_u8_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_u64)))
uint8x16_t __arm_vreinterpretq_u8(uint64x2_t);

#if (__ARM_FEATURE_MVE & 2)

static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_f32)))
float16x8_t __arm_vreinterpretq_f16_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_f32)))
float16x8_t __arm_vreinterpretq_f16(float32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_s16)))
float16x8_t __arm_vreinterpretq_f16_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_s16)))
float16x8_t __arm_vreinterpretq_f16(int16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_s32)))
float16x8_t __arm_vreinterpretq_f16_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_s32)))
float16x8_t __arm_vreinterpretq_f16(int32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_s64)))
float16x8_t __arm_vreinterpretq_f16_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_s64)))
float16x8_t __arm_vreinterpretq_f16(int64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_s8)))
float16x8_t __arm_vreinterpretq_f16_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_s8)))
float16x8_t __arm_vreinterpretq_f16(int8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_u16)))
float16x8_t __arm_vreinterpretq_f16_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_u16)))
float16x8_t __arm_vreinterpretq_f16(uint16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_u32)))
float16x8_t __arm_vreinterpretq_f16_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_u32)))
float16x8_t __arm_vreinterpretq_f16(uint32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_u64)))
float16x8_t __arm_vreinterpretq_f16_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_u64)))
float16x8_t __arm_vreinterpretq_f16(uint64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_u8)))
float16x8_t __arm_vreinterpretq_f16_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_u8)))
float16x8_t __arm_vreinterpretq_f16(uint8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_f16)))
float32x4_t __arm_vreinterpretq_f32_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_f16)))
float32x4_t __arm_vreinterpretq_f32(float16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_s16)))
float32x4_t __arm_vreinterpretq_f32_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_s16)))
float32x4_t __arm_vreinterpretq_f32(int16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_s32)))
float32x4_t __arm_vreinterpretq_f32_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_s32)))
float32x4_t __arm_vreinterpretq_f32(int32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_s64)))
float32x4_t __arm_vreinterpretq_f32_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_s64)))
float32x4_t __arm_vreinterpretq_f32(int64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_s8)))
float32x4_t __arm_vreinterpretq_f32_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_s8)))
float32x4_t __arm_vreinterpretq_f32(int8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_u16)))
float32x4_t __arm_vreinterpretq_f32_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_u16)))
float32x4_t __arm_vreinterpretq_f32(uint16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_u32)))
float32x4_t __arm_vreinterpretq_f32_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_u32)))
float32x4_t __arm_vreinterpretq_f32(uint32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_u64)))
float32x4_t __arm_vreinterpretq_f32_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_u64)))
float32x4_t __arm_vreinterpretq_f32(uint64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_u8)))
float32x4_t __arm_vreinterpretq_f32_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_u8)))
float32x4_t __arm_vreinterpretq_f32(uint8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_f16)))
int16x8_t __arm_vreinterpretq_s16_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_f16)))
int16x8_t __arm_vreinterpretq_s16(float16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_f32)))
int16x8_t __arm_vreinterpretq_s16_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_f32)))
int16x8_t __arm_vreinterpretq_s16(float32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_f16)))
int32x4_t __arm_vreinterpretq_s32_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_f16)))
int32x4_t __arm_vreinterpretq_s32(float16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_f32)))
int32x4_t __arm_vreinterpretq_s32_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_f32)))
int32x4_t __arm_vreinterpretq_s32(float32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_f16)))
int64x2_t __arm_vreinterpretq_s64_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_f16)))
int64x2_t __arm_vreinterpretq_s64(float16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_f32)))
int64x2_t __arm_vreinterpretq_s64_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_f32)))
int64x2_t __arm_vreinterpretq_s64(float32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_f16)))
int8x16_t __arm_vreinterpretq_s8_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_f16)))
int8x16_t __arm_vreinterpretq_s8(float16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_f32)))
int8x16_t __arm_vreinterpretq_s8_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_f32)))
int8x16_t __arm_vreinterpretq_s8(float32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_f16)))
uint16x8_t __arm_vreinterpretq_u16_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_f16)))
uint16x8_t __arm_vreinterpretq_u16(float16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_f32)))
uint16x8_t __arm_vreinterpretq_u16_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_f32)))
uint16x8_t __arm_vreinterpretq_u16(float32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_f16)))
uint32x4_t __arm_vreinterpretq_u32_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_f16)))
uint32x4_t __arm_vreinterpretq_u32(float16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_f32)))
uint32x4_t __arm_vreinterpretq_u32_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_f32)))
uint32x4_t __arm_vreinterpretq_u32(float32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_f16)))
uint64x2_t __arm_vreinterpretq_u64_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_f16)))
uint64x2_t __arm_vreinterpretq_u64(float16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_f32)))
uint64x2_t __arm_vreinterpretq_u64_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_f32)))
uint64x2_t __arm_vreinterpretq_u64(float32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_f16)))
uint8x16_t __arm_vreinterpretq_u8_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_f16)))
uint8x16_t __arm_vreinterpretq_u8(float16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_f32)))
uint8x16_t __arm_vreinterpretq_u8_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_f32)))
uint8x16_t __arm_vreinterpretq_u8(float32x4_t);

#endif /* (__ARM_FEATURE_MVE & 2) */

#if (!defined __ARM_MVE_PRESERVE_USER_NAMESPACE)

static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_s32)))
int16x8_t vreinterpretq_s16_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_s32)))
int16x8_t vreinterpretq_s16(int32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_s64)))
int16x8_t vreinterpretq_s16_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_s64)))
int16x8_t vreinterpretq_s16(int64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_s8)))
int16x8_t vreinterpretq_s16_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_s8)))
int16x8_t vreinterpretq_s16(int8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_u16)))
int16x8_t vreinterpretq_s16_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_u16)))
int16x8_t vreinterpretq_s16(uint16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_u32)))
int16x8_t vreinterpretq_s16_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_u32)))
int16x8_t vreinterpretq_s16(uint32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_u64)))
int16x8_t vreinterpretq_s16_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_u64)))
int16x8_t vreinterpretq_s16(uint64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_u8)))
int16x8_t vreinterpretq_s16_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_u8)))
int16x8_t vreinterpretq_s16(uint8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_s16)))
int32x4_t vreinterpretq_s32_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_s16)))
int32x4_t vreinterpretq_s32(int16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_s64)))
int32x4_t vreinterpretq_s32_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_s64)))
int32x4_t vreinterpretq_s32(int64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_s8)))
int32x4_t vreinterpretq_s32_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_s8)))
int32x4_t vreinterpretq_s32(int8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_u16)))
int32x4_t vreinterpretq_s32_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_u16)))
int32x4_t vreinterpretq_s32(uint16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_u32)))
int32x4_t vreinterpretq_s32_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_u32)))
int32x4_t vreinterpretq_s32(uint32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_u64)))
int32x4_t vreinterpretq_s32_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_u64)))
int32x4_t vreinterpretq_s32(uint64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_u8)))
int32x4_t vreinterpretq_s32_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_u8)))
int32x4_t vreinterpretq_s32(uint8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_s16)))
int64x2_t vreinterpretq_s64_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_s16)))
int64x2_t vreinterpretq_s64(int16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_s32)))
int64x2_t vreinterpretq_s64_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_s32)))
int64x2_t vreinterpretq_s64(int32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_s8)))
int64x2_t vreinterpretq_s64_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_s8)))
int64x2_t vreinterpretq_s64(int8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_u16)))
int64x2_t vreinterpretq_s64_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_u16)))
int64x2_t vreinterpretq_s64(uint16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_u32)))
int64x2_t vreinterpretq_s64_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_u32)))
int64x2_t vreinterpretq_s64(uint32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_u64)))
int64x2_t vreinterpretq_s64_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_u64)))
int64x2_t vreinterpretq_s64(uint64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_u8)))
int64x2_t vreinterpretq_s64_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_u8)))
int64x2_t vreinterpretq_s64(uint8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_s16)))
int8x16_t vreinterpretq_s8_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_s16)))
int8x16_t vreinterpretq_s8(int16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_s32)))
int8x16_t vreinterpretq_s8_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_s32)))
int8x16_t vreinterpretq_s8(int32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_s64)))
int8x16_t vreinterpretq_s8_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_s64)))
int8x16_t vreinterpretq_s8(int64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_u16)))
int8x16_t vreinterpretq_s8_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_u16)))
int8x16_t vreinterpretq_s8(uint16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_u32)))
int8x16_t vreinterpretq_s8_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_u32)))
int8x16_t vreinterpretq_s8(uint32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_u64)))
int8x16_t vreinterpretq_s8_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_u64)))
int8x16_t vreinterpretq_s8(uint64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_u8)))
int8x16_t vreinterpretq_s8_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_u8)))
int8x16_t vreinterpretq_s8(uint8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_s16)))
uint16x8_t vreinterpretq_u16_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_s16)))
uint16x8_t vreinterpretq_u16(int16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_s32)))
uint16x8_t vreinterpretq_u16_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_s32)))
uint16x8_t vreinterpretq_u16(int32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_s64)))
uint16x8_t vreinterpretq_u16_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_s64)))
uint16x8_t vreinterpretq_u16(int64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_s8)))
uint16x8_t vreinterpretq_u16_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_s8)))
uint16x8_t vreinterpretq_u16(int8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_u32)))
uint16x8_t vreinterpretq_u16_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_u32)))
uint16x8_t vreinterpretq_u16(uint32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_u64)))
uint16x8_t vreinterpretq_u16_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_u64)))
uint16x8_t vreinterpretq_u16(uint64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_u8)))
uint16x8_t vreinterpretq_u16_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_u8)))
uint16x8_t vreinterpretq_u16(uint8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_s16)))
uint32x4_t vreinterpretq_u32_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_s16)))
uint32x4_t vreinterpretq_u32(int16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_s32)))
uint32x4_t vreinterpretq_u32_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_s32)))
uint32x4_t vreinterpretq_u32(int32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_s64)))
uint32x4_t vreinterpretq_u32_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_s64)))
uint32x4_t vreinterpretq_u32(int64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_s8)))
uint32x4_t vreinterpretq_u32_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_s8)))
uint32x4_t vreinterpretq_u32(int8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_u16)))
uint32x4_t vreinterpretq_u32_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_u16)))
uint32x4_t vreinterpretq_u32(uint16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_u64)))
uint32x4_t vreinterpretq_u32_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_u64)))
uint32x4_t vreinterpretq_u32(uint64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_u8)))
uint32x4_t vreinterpretq_u32_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_u8)))
uint32x4_t vreinterpretq_u32(uint8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_s16)))
uint64x2_t vreinterpretq_u64_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_s16)))
uint64x2_t vreinterpretq_u64(int16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_s32)))
uint64x2_t vreinterpretq_u64_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_s32)))
uint64x2_t vreinterpretq_u64(int32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_s64)))
uint64x2_t vreinterpretq_u64_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_s64)))
uint64x2_t vreinterpretq_u64(int64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_s8)))
uint64x2_t vreinterpretq_u64_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_s8)))
uint64x2_t vreinterpretq_u64(int8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_u16)))
uint64x2_t vreinterpretq_u64_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_u16)))
uint64x2_t vreinterpretq_u64(uint16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_u32)))
uint64x2_t vreinterpretq_u64_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_u32)))
uint64x2_t vreinterpretq_u64(uint32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_u8)))
uint64x2_t vreinterpretq_u64_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_u8)))
uint64x2_t vreinterpretq_u64(uint8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_s16)))
uint8x16_t vreinterpretq_u8_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_s16)))
uint8x16_t vreinterpretq_u8(int16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_s32)))
uint8x16_t vreinterpretq_u8_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_s32)))
uint8x16_t vreinterpretq_u8(int32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_s64)))
uint8x16_t vreinterpretq_u8_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_s64)))
uint8x16_t vreinterpretq_u8(int64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_s8)))
uint8x16_t vreinterpretq_u8_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_s8)))
uint8x16_t vreinterpretq_u8(int8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_u16)))
uint8x16_t vreinterpretq_u8_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_u16)))
uint8x16_t vreinterpretq_u8(uint16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_u32)))
uint8x16_t vreinterpretq_u8_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_u32)))
uint8x16_t vreinterpretq_u8(uint32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_u64)))
uint8x16_t vreinterpretq_u8_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_u64)))
uint8x16_t vreinterpretq_u8(uint64x2_t);

#endif /* (!defined __ARM_MVE_PRESERVE_USER_NAMESPACE) */

#if (__ARM_FEATURE_MVE & 2) && (!defined __ARM_MVE_PRESERVE_USER_NAMESPACE)

static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_f32)))
float16x8_t vreinterpretq_f16_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_f32)))
float16x8_t vreinterpretq_f16(float32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_s16)))
float16x8_t vreinterpretq_f16_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_s16)))
float16x8_t vreinterpretq_f16(int16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_s32)))
float16x8_t vreinterpretq_f16_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_s32)))
float16x8_t vreinterpretq_f16(int32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_s64)))
float16x8_t vreinterpretq_f16_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_s64)))
float16x8_t vreinterpretq_f16(int64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_s8)))
float16x8_t vreinterpretq_f16_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_s8)))
float16x8_t vreinterpretq_f16(int8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_u16)))
float16x8_t vreinterpretq_f16_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_u16)))
float16x8_t vreinterpretq_f16(uint16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_u32)))
float16x8_t vreinterpretq_f16_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_u32)))
float16x8_t vreinterpretq_f16(uint32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_u64)))
float16x8_t vreinterpretq_f16_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_u64)))
float16x8_t vreinterpretq_f16(uint64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_u8)))
float16x8_t vreinterpretq_f16_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f16_u8)))
float16x8_t vreinterpretq_f16(uint8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_f16)))
float32x4_t vreinterpretq_f32_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_f16)))
float32x4_t vreinterpretq_f32(float16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_s16)))
float32x4_t vreinterpretq_f32_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_s16)))
float32x4_t vreinterpretq_f32(int16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_s32)))
float32x4_t vreinterpretq_f32_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_s32)))
float32x4_t vreinterpretq_f32(int32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_s64)))
float32x4_t vreinterpretq_f32_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_s64)))
float32x4_t vreinterpretq_f32(int64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_s8)))
float32x4_t vreinterpretq_f32_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_s8)))
float32x4_t vreinterpretq_f32(int8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_u16)))
float32x4_t vreinterpretq_f32_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_u16)))
float32x4_t vreinterpretq_f32(uint16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_u32)))
float32x4_t vreinterpretq_f32_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_u32)))
float32x4_t vreinterpretq_f32(uint32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_u64)))
float32x4_t vreinterpretq_f32_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_u64)))
float32x4_t vreinterpretq_f32(uint64x2_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_u8)))
float32x4_t vreinterpretq_f32_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_f32_u8)))
float32x4_t vreinterpretq_f32(uint8x16_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_f16)))
int16x8_t vreinterpretq_s16_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_f16)))
int16x8_t vreinterpretq_s16(float16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_f32)))
int16x8_t vreinterpretq_s16_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s16_f32)))
int16x8_t vreinterpretq_s16(float32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_f16)))
int32x4_t vreinterpretq_s32_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_f16)))
int32x4_t vreinterpretq_s32(float16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_f32)))
int32x4_t vreinterpretq_s32_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s32_f32)))
int32x4_t vreinterpretq_s32(float32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_f16)))
int64x2_t vreinterpretq_s64_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_f16)))
int64x2_t vreinterpretq_s64(float16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_f32)))
int64x2_t vreinterpretq_s64_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s64_f32)))
int64x2_t vreinterpretq_s64(float32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_f16)))
int8x16_t vreinterpretq_s8_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_f16)))
int8x16_t vreinterpretq_s8(float16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_f32)))
int8x16_t vreinterpretq_s8_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_s8_f32)))
int8x16_t vreinterpretq_s8(float32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_f16)))
uint16x8_t vreinterpretq_u16_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_f16)))
uint16x8_t vreinterpretq_u16(float16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_f32)))
uint16x8_t vreinterpretq_u16_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u16_f32)))
uint16x8_t vreinterpretq_u16(float32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_f16)))
uint32x4_t vreinterpretq_u32_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_f16)))
uint32x4_t vreinterpretq_u32(float16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_f32)))
uint32x4_t vreinterpretq_u32_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u32_f32)))
uint32x4_t vreinterpretq_u32(float32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_f16)))
uint64x2_t vreinterpretq_u64_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_f16)))
uint64x2_t vreinterpretq_u64(float16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_f32)))
uint64x2_t vreinterpretq_u64_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u64_f32)))
uint64x2_t vreinterpretq_u64(float32x4_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_f16)))
uint8x16_t vreinterpretq_u8_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_f16)))
uint8x16_t vreinterpretq_u8(float16x8_t);
static __inline__ __attribute__((__clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_f32)))
uint8x16_t vreinterpretq_u8_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_builtin_alias(__builtin_arm_mve_vreinterpretq_u8_f32)))
uint8x16_t vreinterpretq_u8(float32x4_t);

#endif /* (__ARM_FEATURE_MVE & 2) && (!defined __ARM_MVE_PRESERVE_USER_NAMESPACE) */

#ifdef __cplusplus
}
#endif
