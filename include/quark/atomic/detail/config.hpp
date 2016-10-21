/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.quark.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2012 Hartmut Kaiser
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/config.hpp
 *
 * This header defines configuraion macros for Boost.Atomic
 */

#ifndef QUARK_ATOMIC_DETAIL_CONFIG_HPP_INCLUDED_
#define QUARK_ATOMIC_DETAIL_CONFIG_HPP_INCLUDED_

#include <quark/config.hpp>

#ifdef QUARK_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(__has_builtin)
#if __has_builtin(__builtin_memcpy)
#define QUARK_ATOMIC_DETAIL_HAS_BUILTIN_MEMCPY
#endif
#if __has_builtin(__builtin_memcmp)
#define QUARK_ATOMIC_DETAIL_HAS_BUILTIN_MEMCMP
#endif
#elif defined(QUARK_GCC)
#define QUARK_ATOMIC_DETAIL_HAS_BUILTIN_MEMCPY
#define QUARK_ATOMIC_DETAIL_HAS_BUILTIN_MEMCMP
#endif

#if defined(QUARK_ATOMIC_DETAIL_HAS_BUILTIN_MEMCPY)
#define QUARK_ATOMIC_DETAIL_MEMCPY __builtin_memcpy
#else
#define QUARK_ATOMIC_DETAIL_MEMCPY std::memcpy
#endif

#if defined(QUARK_ATOMIC_DETAIL_HAS_BUILTIN_MEMCMP)
#define QUARK_ATOMIC_DETAIL_MEMCMP __builtin_memcmp
#else
#define QUARK_ATOMIC_DETAIL_MEMCMP std::memcmp
#endif

#if defined(__CUDACC__)
// nvcc does not support alternatives in asm statement constraints
#define QUARK_ATOMIC_DETAIL_NO_ASM_CONSTRAINT_ALTERNATIVES
// nvcc does not support condition code register ("cc") clobber in asm statements
#define QUARK_ATOMIC_DETAIL_NO_ASM_CLOBBER_CC
#endif

#if !defined(QUARK_ATOMIC_DETAIL_NO_ASM_CLOBBER_CC)
#define QUARK_ATOMIC_DETAIL_ASM_CLOBBER_CC "cc"
#define QUARK_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA "cc",
#else
#define QUARK_ATOMIC_DETAIL_ASM_CLOBBER_CC
#define QUARK_ATOMIC_DETAIL_ASM_CLOBBER_CC_COMMA
#endif

#if (defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)) && (defined(__GNUC__) && (__GNUC__ * 100 + __GNUC_MINOR__) < 403)
// This macro indicates we're using older binutils that don't support implied zero displacements for memory opereands,
// making code like this invalid:
//   movl 4+(%%edx), %%eax
#define QUARK_ATOMIC_DETAIL_NO_ASM_IMPLIED_ZERO_DISPLACEMENTS
#endif

#if defined(__clang__) || (defined(QUARK_GCC) && (QUARK_GCC+0) < 40500)
// This macro indicates that the compiler does not support allocating rax:rdx register pairs ("A") in asm blocks
#define QUARK_ATOMIC_DETAIL_NO_ASM_RAX_RDX_PAIRS
#endif

#endif // QUARK_ATOMIC_DETAIL_CONFIG_HPP_INCLUDED_
