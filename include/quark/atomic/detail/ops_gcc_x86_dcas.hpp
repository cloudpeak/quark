/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.quark.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2012 Tim Blechmann
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/ops_gcc_x86_dcas.hpp
 *
 * This header contains implementation of the double-width CAS primitive for x86.
 */

#ifndef QUARK_ATOMIC_DETAIL_OPS_GCC_X86_DCAS_HPP_INCLUDED_
#define QUARK_ATOMIC_DETAIL_OPS_GCC_X86_DCAS_HPP_INCLUDED_

#include <quark/cstdint.hpp>
#include <quark/memory_order.hpp>
#include <quark/atomic/detail/config.hpp>
#include <quark/atomic/detail/storage_type.hpp>
#include <quark/atomic/capabilities.hpp>

#ifdef QUARK_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace quark {
namespace atomics {
namespace detail {

#if defined(QUARK_ATOMIC_DETAIL_X86_HAS_CMPXCHG8B)

template< bool Signed >
struct gcc_dcas_x86
{
    typedef typename make_storage_type< 8u, Signed >::type storage_type;
    typedef typename make_storage_type< 8u, Signed >::aligned aligned_storage_type;

    static QUARK_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order) QUARK_NOEXCEPT
    {
        if ((((uint32_t)&storage) & 0x00000007) == 0)
        {
#if defined(__SSE2__)
            __asm__ __volatile__
            (
#if defined(__AVX__)
                "vmovq %1, %%xmm4\n\t"
                "vmovq %%xmm4, %0\n\t"
#else
                "movq %1, %%xmm4\n\t"
                "movq %%xmm4, %0\n\t"
#endif
                : "=m" (storage)
                : "m" (v)
                : "memory", "xmm4"
            );
#else
            __asm__ __volatile__
            (
                "fildll %1\n\t"
                "fistpll %0\n\t"
                : "=m" (storage)
                : "m" (v)
                : "memory"
            );
#endif
        }
        else
        {
#if !defined(QUARK_ATOMIC_DETAIL_NO_ASM_IMPLIED_ZERO_DISPLACEMENTS)
#if defined(__PIC__)
            uint32_t scratch;
            __asm__ __volatile__
            (
                "movl %%ebx, %[scratch]\n\t"
                "movl %[value_lo], %%ebx\n\t"
                "movl %[dest], %%eax\n\t"
                "movl 4+%[dest], %%edx\n\t"
                ".align 16\n\t"
                "1: lock; cmpxchg8b %[dest]\n\t"
                "jne 1b\n\t"
                "movl %[scratch], %%ebx\n\t"
                : [scratch] "=m" (scratch), [dest] "=o" (storage)
                : [value_lo] "a" ((uint32_t)v), "c" ((uint32_t)(v >> 32))
                : QUARK_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "edx", "memory"
            );
#else // defined(__PIC__)
            __asm__ __volatile__
            (
                "movl %[dest], %%eax\n\t"
                "movl 4+%[dest], %%edx\n\t"
                ".align 16\n\t"
                "1: lock; cmpxchg8b %[dest]\n\t"
                "jne 1b\n\t"
                : [dest] "=o" (storage)
                : [value_lo] "b" ((uint32_t)v), "c" ((uint32_t)(v >> 32))
                : QUARK_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "eax", "edx", "memory"
            );
#endif // defined(__PIC__)
#else // !defined(QUARK_ATOMIC_DETAIL_NO_ASM_IMPLIED_ZERO_DISPLACEMENTS)
#if defined(__PIC__)
            uint32_t scratch;
            __asm__ __volatile__
            (
                "movl %%ebx, %[scratch]\n\t"
                "movl %[value_lo], %%ebx\n\t"
                "movl 0(%[dest]), %%eax\n\t"
                "movl 4(%[dest]), %%edx\n\t"
                ".align 16\n\t"
                "1: lock; cmpxchg8b 0(%[dest])\n\t"
                "jne 1b\n\t"
                "movl %[scratch], %%ebx\n\t"
#if !defined(QUARK_ATOMIC_DETAIL_NO_ASM_CONSTRAINT_ALTERNATIVES)
                : [scratch] "=m,m" (scratch)
                : [value_lo] "a,a" ((uint32_t)v), "c,c" ((uint32_t)(v >> 32)), [dest] "D,S" (&storage)
#else
                : [scratch] "=m" (scratch)
                : [value_lo] "a" ((uint32_t)v), "c" ((uint32_t)(v >> 32)), [dest] "D" (&storage)
#endif
                : QUARK_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "edx", "memory"
            );
#else // defined(__PIC__)
            __asm__ __volatile__
            (
                "movl 0(%[dest]), %%eax\n\t"
                "movl 4(%[dest]), %%edx\n\t"
                ".align 16\n\t"
                "1: lock; cmpxchg8b 0(%[dest])\n\t"
                "jne 1b\n\t"
                :
#if !defined(QUARK_ATOMIC_DETAIL_NO_ASM_CONSTRAINT_ALTERNATIVES)
                : [value_lo] "b,b" ((uint32_t)v), "c,c" ((uint32_t)(v >> 32)), [dest] "D,S" (&storage)
#else
                : [value_lo] "b" ((uint32_t)v), "c" ((uint32_t)(v >> 32)), [dest] "D" (&storage)
#endif
                : QUARK_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "eax", "edx", "memory"
            );
#endif // defined(__PIC__)
#endif // !defined(QUARK_ATOMIC_DETAIL_NO_ASM_IMPLIED_ZERO_DISPLACEMENTS)
        }
    }

    static QUARK_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order) QUARK_NOEXCEPT
    {
        storage_type value;

        if ((((uint32_t)&storage) & 0x00000007) == 0)
        {
#if defined(__SSE2__)
            __asm__ __volatile__
            (
#if defined(__AVX__)
                "vmovq %1, %%xmm4\n\t"
                "vmovq %%xmm4, %0\n\t"
#else
                "movq %1, %%xmm4\n\t"
                "movq %%xmm4, %0\n\t"
#endif
                : "=m" (value)
                : "m" (storage)
                : "memory", "xmm4"
            );
#else
            __asm__ __volatile__
            (
                "fildll %1\n\t"
                "fistpll %0\n\t"
                : "=m" (value)
                : "m" (storage)
                : "memory"
            );
#endif
        }
        else
        {
#if defined(__clang__)
            // Clang cannot allocate eax:edx register pairs but it has sync intrinsics
            value = __sync_val_compare_and_swap(&storage, (storage_type)0, (storage_type)0);
#else
            // We don't care for comparison result here; the previous value will be stored into value anyway.
            // Also we don't care for ebx and ecx values, they just have to be equal to eax and edx before cmpxchg8b.
            __asm__ __volatile__
            (
                "movl %%ebx, %%eax\n\t"
                "movl %%ecx, %%edx\n\t"
                "lock; cmpxchg8b %[storage]\n\t"
                : "=&A" (value)
                : [storage] "m" (storage)
                : QUARK_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
            );
#endif
        }

        return value;
    }

    static QUARK_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order, memory_order) QUARK_NOEXCEPT
    {
#if defined(__clang__)
        // Clang cannot allocate eax:edx register pairs but it has sync intrinsics
        storage_type old_expected = expected;
        expected = __sync_val_compare_and_swap(&storage, old_expected, desired);
        return expected == old_expected;
#elif defined(__PIC__)
        // Make sure ebx is saved and restored properly in case
        // of position independent code. To make this work
        // setup register constraints such that ebx can not be
        // used by accident e.g. as base address for the variable
        // to be modified. Accessing "scratch" should always be okay,
        // as it can only be placed on the stack (and therefore
        // accessed through ebp or esp only).
        //
        // In theory, could push/pop ebx onto/off the stack, but movs
        // to a prepared stack slot turn out to be faster.

        uint32_t scratch;
        bool success;
        __asm__ __volatile__
        (
            "movl %%ebx, %[scratch]\n\t"
            "movl %[desired_lo], %%ebx\n\t"
            "lock; cmpxchg8b %[dest]\n\t"
            "movl %[scratch], %%ebx\n\t"
            "sete %[success]\n\t"
#if !defined(QUARK_ATOMIC_DETAIL_NO_ASM_CONSTRAINT_ALTERNATIVES)
            : "+A,A,A,A,A,A" (expected), [dest] "+m,m,m,m,m,m" (storage), [scratch] "=m,m,m,m,m,m" (scratch), [success] "=q,m,q,m,q,m" (success)
            : [desired_lo] "S,S,D,D,m,m" ((uint32_t)desired), "c,c,c,c,c,c" ((uint32_t)(desired >> 32))
#else
            : "+A" (expected), [dest] "+m" (storage), [scratch] "=m" (scratch), [success] "=q" (success)
            : [desired_lo] "S" ((uint32_t)desired), "c" ((uint32_t)(desired >> 32))
#endif
            : QUARK_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
        return success;
#else
        bool success;
        __asm__ __volatile__
        (
            "lock; cmpxchg8b %[dest]\n\t"
            "sete %[success]\n\t"
#if !defined(QUARK_ATOMIC_DETAIL_NO_ASM_CONSTRAINT_ALTERNATIVES)
            : "+A,A" (expected), [dest] "+m,m" (storage), [success] "=q,m" (success)
            : "b,b" ((uint32_t)desired), "c,c" ((uint32_t)(desired >> 32))
#else
            : "+A" (expected), [dest] "+m" (storage), [success] "=q" (success)
            : "b" ((uint32_t)desired), "c" ((uint32_t)(desired >> 32))
#endif
            : QUARK_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
        return success;
#endif
    }

    static QUARK_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) QUARK_NOEXCEPT
    {
        return compare_exchange_strong(storage, expected, desired, success_order, failure_order);
    }

    static QUARK_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order order) QUARK_NOEXCEPT
    {
#if defined(__clang__)
        // Clang cannot allocate eax:edx register pairs but it has sync intrinsics
        storage_type old_val = storage;
        while (true)
        {
            storage_type val = __sync_val_compare_and_swap(&storage, old_val, v);
            if (val == old_val)
                return val;
            old_val = val;
        }
#elif !defined(QUARK_ATOMIC_DETAIL_NO_ASM_IMPLIED_ZERO_DISPLACEMENTS)
#if defined(__PIC__)
        uint32_t scratch;
        __asm__ __volatile__
        (
            "movl %%ebx, %[scratch]\n\t"
            "movl %%eax, %%ebx\n\t"
            "movl %%edx, %%ecx\n\t"
            "movl %[dest], %%eax\n\t"
            "movl 4+%[dest], %%edx\n\t"
            ".align 16\n\t"
            "1: lock; cmpxchg8b %[dest]\n\t"
            "jne 1b\n\t"
            "movl %[scratch], %%ebx\n\t"
            : "+A" (v), [scratch] "=m" (scratch), [dest] "+o" (storage)
            :
            : QUARK_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "ecx", "memory"
        );
        return v;
#else // defined(__PIC__)
        __asm__ __volatile__
        (
            "movl %[dest], %%eax\n\t"
            "movl 4+%[dest], %%edx\n\t"
            ".align 16\n\t"
            "1: lock; cmpxchg8b %[dest]\n\t"
            "jne 1b\n\t"
            : "=A" (v), [dest] "+o" (storage)
            : "b" ((uint32_t)v), "c" ((uint32_t)(v >> 32))
            : QUARK_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
        return v;
#endif // defined(__PIC__)
#else // !defined(QUARK_ATOMIC_DETAIL_NO_ASM_IMPLIED_ZERO_DISPLACEMENTS)
#if defined(__PIC__)
        uint32_t scratch;
        __asm__ __volatile__
        (
            "movl %%ebx, %[scratch]\n\t"
            "movl %%eax, %%ebx\n\t"
            "movl %%edx, %%ecx\n\t"
            "movl 0(%[dest]), %%eax\n\t"
            "movl 4(%[dest]), %%edx\n\t"
            ".align 16\n\t"
            "1: lock; cmpxchg8b 0(%[dest])\n\t"
            "jne 1b\n\t"
            "movl %[scratch], %%ebx\n\t"
#if !defined(QUARK_ATOMIC_DETAIL_NO_ASM_CONSTRAINT_ALTERNATIVES)
            : "+A,A" (v), [scratch] "=m,m" (scratch)
            : [dest] "D,S" (&storage)
#else
            : "+A" (v), [scratch] "=m" (scratch)
            : [dest] "D" (&storage)
#endif
            : QUARK_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "ecx", "memory"
        );
        return v;
#else // defined(__PIC__)
        __asm__ __volatile__
        (
            "movl 0(%[dest]), %%eax\n\t"
            "movl 4(%[dest]), %%edx\n\t"
            ".align 16\n\t"
            "1: lock; cmpxchg8b 0(%[dest])\n\t"
            "jne 1b\n\t"
#if !defined(QUARK_ATOMIC_DETAIL_NO_ASM_CONSTRAINT_ALTERNATIVES)
            : "=A,A" (v)
            : "b,b" ((uint32_t)v), "c,c" ((uint32_t)(v >> 32)), [dest] "D,S" (&storage)
#else
            : "=A" (v)
            : "b" ((uint32_t)v), "c" ((uint32_t)(v >> 32)), [dest] "D" (&storage)
#endif
            : QUARK_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
        return v;
#endif // defined(__PIC__)
#endif
    }

    static QUARK_FORCEINLINE bool is_lock_free(storage_type const volatile&) QUARK_NOEXCEPT
    {
        return true;
    }
};

#endif // defined(QUARK_ATOMIC_DETAIL_X86_HAS_CMPXCHG8B)

#if defined(QUARK_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B)

template< bool Signed >
struct gcc_dcas_x86_64
{
    typedef typename make_storage_type< 16u, Signed >::type storage_type;
    typedef typename make_storage_type< 16u, Signed >::aligned aligned_storage_type;

    static QUARK_FORCEINLINE void store(storage_type volatile& storage, storage_type v, memory_order) QUARK_NOEXCEPT
    {
        uint64_t const* p_value = (uint64_t const*)&v;
#if !defined(QUARK_ATOMIC_DETAIL_NO_ASM_IMPLIED_ZERO_DISPLACEMENTS)
        __asm__ __volatile__
        (
            "movq %[dest], %%rax\n\t"
            "movq 8+%[dest], %%rdx\n\t"
            ".align 16\n\t"
            "1: lock; cmpxchg16b %[dest]\n\t"
            "jne 1b\n\t"
            : [dest] "=o" (storage)
            : "b" (p_value[0]), "c" (p_value[1])
            : QUARK_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "rax", "rdx", "memory"
        );
#else // !defined(QUARK_ATOMIC_DETAIL_NO_ASM_IMPLIED_ZERO_DISPLACEMENTS)
        __asm__ __volatile__
        (
            "movq 0(%[dest]), %%rax\n\t"
            "movq 8(%[dest]), %%rdx\n\t"
            ".align 16\n\t"
            "1: lock; cmpxchg16b 0(%[dest])\n\t"
            "jne 1b\n\t"
            :
            : "b" (p_value[0]), "c" (p_value[1]), [dest] "r" (&storage)
            : QUARK_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "rax", "rdx", "memory"
        );
#endif // !defined(QUARK_ATOMIC_DETAIL_NO_ASM_IMPLIED_ZERO_DISPLACEMENTS)
    }

    static QUARK_FORCEINLINE storage_type load(storage_type const volatile& storage, memory_order) QUARK_NOEXCEPT
    {
#if defined(__clang__)
        // Clang cannot allocate rax:rdx register pairs but it has sync intrinsics
        storage_type value = storage_type();
        return __sync_val_compare_and_swap(&storage, value, value);
#elif defined(QUARK_ATOMIC_DETAIL_NO_ASM_RAX_RDX_PAIRS)
        // GCC 4.4 can't allocate rax:rdx register pair either but it also doesn't support 128-bit __sync_val_compare_and_swap
        storage_type value;

        // We don't care for comparison result here; the previous value will be stored into value anyway.
        // Also we don't care for rbx and rcx values, they just have to be equal to rax and rdx before cmpxchg16b.
#if !defined(QUARK_ATOMIC_DETAIL_NO_ASM_IMPLIED_ZERO_DISPLACEMENTS)
        __asm__ __volatile__
        (
            "movq %%rbx, %%rax\n\t"
            "movq %%rcx, %%rdx\n\t"
            "lock; cmpxchg16b %[storage]\n\t"
            "movq %%rax, %[value]\n\t"
            "movq %%rdx, 8+%[value]\n\t"
            : [value] "=o" (value)
            : [storage] "m" (storage)
            : QUARK_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory", "rax", "rdx"
        );
#else // !defined(QUARK_ATOMIC_DETAIL_NO_ASM_IMPLIED_ZERO_DISPLACEMENTS)
        __asm__ __volatile__
        (
            "movq %%rbx, %%rax\n\t"
            "movq %%rcx, %%rdx\n\t"
            "lock; cmpxchg16b %[storage]\n\t"
            "movq %%rax, 0(%[value])\n\t"
            "movq %%rdx, 8(%[value])\n\t"
            :
            : [storage] "m" (storage), [value] "r" (&value)
            : QUARK_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory", "rax", "rdx"
        );
#endif // !defined(QUARK_ATOMIC_DETAIL_NO_ASM_IMPLIED_ZERO_DISPLACEMENTS)

        return value;
#else // defined(QUARK_ATOMIC_DETAIL_NO_ASM_RAX_RDX_PAIRS)
        storage_type value;

        // We don't care for comparison result here; the previous value will be stored into value anyway.
        // Also we don't care for rbx and rcx values, they just have to be equal to rax and rdx before cmpxchg16b.
        __asm__ __volatile__
        (
            "movq %%rbx, %%rax\n\t"
            "movq %%rcx, %%rdx\n\t"
            "lock; cmpxchg16b %[storage]\n\t"
            : "=&A" (value)
            : [storage] "m" (storage)
            : QUARK_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );

        return value;
#endif
    }

    static QUARK_FORCEINLINE bool compare_exchange_strong(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order, memory_order) QUARK_NOEXCEPT
    {
#if defined(__clang__)
        // Clang cannot allocate rax:rdx register pairs but it has sync intrinsics
        storage_type old_expected = expected;
        expected = __sync_val_compare_and_swap(&storage, old_expected, desired);
        return expected == old_expected;
#elif defined(QUARK_ATOMIC_DETAIL_NO_ASM_RAX_RDX_PAIRS)
        // GCC 4.4 can't allocate rax:rdx register pair either but it also doesn't support 128-bit __sync_val_compare_and_swap
        uint64_t const* p_desired = (uint64_t const*)&desired;
        bool success;
#if !defined(QUARK_ATOMIC_DETAIL_NO_ASM_IMPLIED_ZERO_DISPLACEMENTS)
        __asm__ __volatile__
        (
            "movq %[expected], %%rax\n\t"
            "movq 8+%[expected], %%rdx\n\t"
            "lock; cmpxchg16b %[dest]\n\t"
            "sete %[success]\n\t"
            "movq %%rax, %[expected]\n\t"
            "movq %%rdx, 8+%[expected]\n\t"
            : [dest] "+m" (storage), [expected] "+o" (expected), [success] "=q" (success)
            : "b" (p_desired[0]), "c" (p_desired[1])
            : QUARK_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory", "rax", "rdx"
        );
#else // !defined(QUARK_ATOMIC_DETAIL_NO_ASM_IMPLIED_ZERO_DISPLACEMENTS)
        __asm__ __volatile__
        (
            "movq 0(%[expected]), %%rax\n\t"
            "movq 8(%[expected]), %%rdx\n\t"
            "lock; cmpxchg16b %[dest]\n\t"
            "sete %[success]\n\t"
            "movq %%rax, 0(%[expected])\n\t"
            "movq %%rdx, 8(%[expected])\n\t"
            : [dest] "+m" (storage), [success] "=q" (success)
            : "b" (p_desired[0]), "c" (p_desired[1]), [expected] "r" (&expected)
            : QUARK_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory", "rax", "rdx"
        );
#endif // !defined(QUARK_ATOMIC_DETAIL_NO_ASM_IMPLIED_ZERO_DISPLACEMENTS)

        return success;
#else // defined(QUARK_ATOMIC_DETAIL_NO_ASM_RAX_RDX_PAIRS)
        uint64_t const* p_desired = (uint64_t const*)&desired;
        bool success;
        __asm__ __volatile__
        (
            "lock; cmpxchg16b %[dest]\n\t"
            "sete %[success]\n\t"
#if !defined(QUARK_ATOMIC_DETAIL_NO_ASM_CONSTRAINT_ALTERNATIVES)
            : "+A,A" (expected), [dest] "+m,m" (storage), [success] "=q,m" (success)
            : "b,b" (p_desired[0]), "c,c" (p_desired[1])
#else
            : "+A" (expected), [dest] "+m" (storage), [success] "=q" (success)
            : "b" (p_desired[0]), "c" (p_desired[1])
#endif
            : QUARK_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
        return success;
#endif
    }

    static QUARK_FORCEINLINE bool compare_exchange_weak(
        storage_type volatile& storage, storage_type& expected, storage_type desired, memory_order success_order, memory_order failure_order) QUARK_NOEXCEPT
    {
        return compare_exchange_strong(storage, expected, desired, success_order, failure_order);
    }

    static QUARK_FORCEINLINE storage_type exchange(storage_type volatile& storage, storage_type v, memory_order) QUARK_NOEXCEPT
    {
#if defined(__clang__)
        // Clang cannot allocate eax:edx register pairs but it has sync intrinsics
        storage_type old_val = storage;
        while (true)
        {
            storage_type val = __sync_val_compare_and_swap(&storage, old_val, v);
            if (val == old_val)
                return val;
            old_val = val;
        }
#elif defined(QUARK_ATOMIC_DETAIL_NO_ASM_RAX_RDX_PAIRS)
        // GCC 4.4 can't allocate rax:rdx register pair either but it also doesn't support 128-bit __sync_val_compare_and_swap
        storage_type old_value;
        uint64_t const* p_value = (uint64_t const*)&v;
#if !defined(QUARK_ATOMIC_DETAIL_NO_ASM_IMPLIED_ZERO_DISPLACEMENTS)
        __asm__ __volatile__
        (
            "movq %[dest], %%rax\n\t"
            "movq 8+%[dest], %%rdx\n\t"
            ".align 16\n\t"
            "1: lock; cmpxchg16b %[dest]\n\t"
            "jne 1b\n\t"
            "movq %%rax, %[old_value]\n\t"
            "movq %%rdx, 8+%[old_value]\n\t"
            : [dest] "+o" (storage), [old_value] "=o" (old_value)
            : "b" (p_value[0]), "c" (p_value[1])
            : QUARK_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory", "rax", "rdx"
        );
#else // !defined(QUARK_ATOMIC_DETAIL_NO_ASM_IMPLIED_ZERO_DISPLACEMENTS)
        __asm__ __volatile__
        (
            "movq 0(%[dest]), %%rax\n\t"
            "movq 8(%[dest]), %%rdx\n\t"
            ".align 16\n\t"
            "1: lock; cmpxchg16b 0(%[dest])\n\t"
            "jne 1b\n\t"
            "movq %%rax, 0(%[old_value])\n\t"
            "movq %%rdx, 8(%[old_value])\n\t"
            :
            : "b" (p_value[0]), "c" (p_value[1]), [dest] "r" (&storage), [old_value] "r" (&old_value)
            : QUARK_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory", "rax", "rdx"
        );
#endif // !defined(QUARK_ATOMIC_DETAIL_NO_ASM_IMPLIED_ZERO_DISPLACEMENTS)

        return old_value;
#else // defined(QUARK_ATOMIC_DETAIL_NO_ASM_RAX_RDX_PAIRS)
        uint64_t const* p_value = (uint64_t const*)&v;
#if !defined(QUARK_ATOMIC_DETAIL_NO_ASM_IMPLIED_ZERO_DISPLACEMENTS)
        __asm__ __volatile__
        (
            "movq %[dest], %%rax\n\t"
            "movq 8+%[dest], %%rdx\n\t"
            ".align 16\n\t"
            "1: lock; cmpxchg16b %[dest]\n\t"
            "jne 1b\n\t"
            : "=&A" (v), [dest] "+o" (storage)
            : "b" (p_value[0]), "c" (p_value[1])
            : QUARK_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#else // !defined(QUARK_ATOMIC_DETAIL_NO_ASM_IMPLIED_ZERO_DISPLACEMENTS)
        __asm__ __volatile__
        (
            "movq 0(%[dest]), %%rax\n\t"
            "movq 8(%[dest]), %%rdx\n\t"
            ".align 16\n\t"
            "1: lock; cmpxchg16b 0(%[dest])\n\t"
            "jne 1b\n\t"
            : "=&A" (v)
            : "b" (p_value[0]), "c" (p_value[1]), [dest] "r" (&storage)
            : QUARK_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "memory"
        );
#endif // !defined(QUARK_ATOMIC_DETAIL_NO_ASM_IMPLIED_ZERO_DISPLACEMENTS)

        return v;
#endif
    }

    static QUARK_FORCEINLINE bool is_lock_free(storage_type const volatile&) QUARK_NOEXCEPT
    {
        return true;
    }
};

#endif // defined(QUARK_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B)

} // namespace detail
} // namespace atomics
} // namespace quark

#endif // QUARK_ATOMIC_DETAIL_OPS_GCC_X86_DCAS_HPP_INCLUDED_
