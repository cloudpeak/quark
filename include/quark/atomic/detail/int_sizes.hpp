/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.quark.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/int_sizes.hpp
 *
 * This header defines macros for testing buitin integer type sizes
 */

#ifndef QUARK_ATOMIC_DETAIL_INT_SIZES_HPP_INCLUDED_
#define QUARK_ATOMIC_DETAIL_INT_SIZES_HPP_INCLUDED_

#include <quark/atomic/detail/config.hpp>

#ifdef QUARK_HAS_PRAGMA_ONCE
#pragma once
#endif

// GCC and compatible compilers define internal macros with builtin type traits
#if defined(__SIZEOF_SHORT__)
#define QUARK_ATOMIC_DETAIL_SIZEOF_SHORT __SIZEOF_SHORT__
#endif
#if defined(__SIZEOF_INT__)
#define QUARK_ATOMIC_DETAIL_SIZEOF_INT __SIZEOF_INT__
#endif
#if defined(__SIZEOF_LONG__)
#define QUARK_ATOMIC_DETAIL_SIZEOF_LONG __SIZEOF_LONG__
#endif
#if defined(__SIZEOF_LONG_LONG__)
#define QUARK_ATOMIC_DETAIL_SIZEOF_LLONG __SIZEOF_LONG_LONG__
#endif
#if defined(__SIZEOF_WCHAR_T__)
#define QUARK_ATOMIC_DETAIL_SIZEOF_WCHAR_T __SIZEOF_WCHAR_T__
#endif
#if defined(__SIZEOF_POINTER__)
#define QUARK_ATOMIC_DETAIL_SIZEOF_POINTER __SIZEOF_POINTER__
#elif defined(_MSC_VER)
#if defined(_M_AMD64) || defined(_M_IA64)
#define QUARK_ATOMIC_DETAIL_SIZEOF_POINTER 8
#else
#define QUARK_ATOMIC_DETAIL_SIZEOF_POINTER 4
#endif
#endif

#if !defined(QUARK_ATOMIC_DETAIL_SIZEOF_SHORT) || !defined(QUARK_ATOMIC_DETAIL_SIZEOF_INT) ||\
    !defined(QUARK_ATOMIC_DETAIL_SIZEOF_LONG) || !defined(QUARK_ATOMIC_DETAIL_SIZEOF_LLONG)

// Try to deduce sizes from limits
#include <limits.h>
#include <quark/cstdint.hpp>

#if (USHRT_MAX + 0) == 0xff
#define QUARK_ATOMIC_DETAIL_SIZEOF_SHORT 1
#elif (USHRT_MAX + 0) == 0xffff
#define QUARK_ATOMIC_DETAIL_SIZEOF_SHORT 2
#elif (USHRT_MAX + 0) == 0xffffffff
#define QUARK_ATOMIC_DETAIL_SIZEOF_SHORT 4
#elif (USHRT_MAX + 0) == UINT64_C(0xffffffffffffffff)
#define QUARK_ATOMIC_DETAIL_SIZEOF_SHORT 8
#endif

#if (UINT_MAX + 0) == 0xff
#define QUARK_ATOMIC_DETAIL_SIZEOF_INT 1
#elif (UINT_MAX + 0) == 0xffff
#define QUARK_ATOMIC_DETAIL_SIZEOF_INT 2
#elif (UINT_MAX + 0) == 0xffffffff
#define QUARK_ATOMIC_DETAIL_SIZEOF_INT 4
#elif (UINT_MAX + 0) == UINT64_C(0xffffffffffffffff)
#define QUARK_ATOMIC_DETAIL_SIZEOF_INT 8
#endif

#if (ULONG_MAX + 0) == 0xff
#define QUARK_ATOMIC_DETAIL_SIZEOF_LONG 1
#elif (ULONG_MAX + 0) == 0xffff
#define QUARK_ATOMIC_DETAIL_SIZEOF_LONG 2
#elif (ULONG_MAX + 0) == 0xffffffff
#define QUARK_ATOMIC_DETAIL_SIZEOF_LONG 4
#elif (ULONG_MAX + 0) == UINT64_C(0xffffffffffffffff)
#define QUARK_ATOMIC_DETAIL_SIZEOF_LONG 8
#endif

#if defined(__hpux) // HP-UX's value of ULONG_LONG_MAX is unusable in preprocessor expressions
#define QUARK_ATOMIC_DETAIL_SIZEOF_LLONG 8
#else

// The list of the non-standard macros (the ones except ULLONG_MAX) is taken from cstdint.hpp
#if defined(ULLONG_MAX)
#define QUARK_ATOMIC_DETAIL_ULLONG_MAX ULLONG_MAX
#elif defined(ULONG_LONG_MAX)
#define QUARK_ATOMIC_DETAIL_ULLONG_MAX ULONG_LONG_MAX
#elif defined(ULONGLONG_MAX)
#define QUARK_ATOMIC_DETAIL_ULLONG_MAX ULONGLONG_MAX
#elif defined(_LLONG_MAX) // strangely enough, this one seems to be holding the limit for the unsigned integer
#define QUARK_ATOMIC_DETAIL_ULLONG_MAX _LLONG_MAX
#endif

#if (QUARK_ATOMIC_DETAIL_ULLONG_MAX + 0) == 0xff
#define QUARK_ATOMIC_DETAIL_SIZEOF_LLONG 1
#elif (QUARK_ATOMIC_DETAIL_ULLONG_MAX + 0) == 0xffff
#define QUARK_ATOMIC_DETAIL_SIZEOF_LLONG 2
#elif (QUARK_ATOMIC_DETAIL_ULLONG_MAX + 0) == 0xffffffff
#define QUARK_ATOMIC_DETAIL_SIZEOF_LLONG 4
#elif (QUARK_ATOMIC_DETAIL_ULLONG_MAX + 0) == UINT64_C(0xffffffffffffffff)
#define QUARK_ATOMIC_DETAIL_SIZEOF_LLONG 8
#endif

#endif // defined(__hpux)

#endif

#if !defined(QUARK_ATOMIC_DETAIL_SIZEOF_WCHAR_T)

#include <wchar.h>
#include <quark/cstdint.hpp>

 #if defined(_MSC_VER) && ( _MSC_VER <= 1310 || defined(UNDER_CE) && _MSC_VER <= 1500 )
// MSVC 7.1 and MSVC 8 (arm) define WCHAR_MAX to a value not suitable for constant expressions
#define QUARK_ATOMIC_DETAIL_SIZEOF_WCHAR_T 2
#elif (WCHAR_MAX + 0) == 0xff || (WCHAR_MAX + 0) == 0x7f
#define QUARK_ATOMIC_DETAIL_SIZEOF_WCHAR_T 1
#elif (WCHAR_MAX + 0) == 0xffff || (WCHAR_MAX + 0) == 0x7fff
#define QUARK_ATOMIC_DETAIL_SIZEOF_WCHAR_T 2
#elif (WCHAR_MAX + 0) == 0xffffffff || (WCHAR_MAX + 0) == 0x7fffffff
#define QUARK_ATOMIC_DETAIL_SIZEOF_WCHAR_T 4
#elif (WCHAR_MAX + 0) == UINT64_C(0xffffffffffffffff) || (WCHAR_MAX + 0) == INT64_C(0x7fffffffffffffff)
#define QUARK_ATOMIC_DETAIL_SIZEOF_WCHAR_T 8
#endif
#endif

#if !defined(QUARK_ATOMIC_DETAIL_SIZEOF_SHORT) || !defined(QUARK_ATOMIC_DETAIL_SIZEOF_INT) ||\
    !defined(QUARK_ATOMIC_DETAIL_SIZEOF_LONG) || !defined(QUARK_ATOMIC_DETAIL_SIZEOF_LLONG) ||\
    !defined(QUARK_ATOMIC_DETAIL_SIZEOF_WCHAR_T)
#error Boost.Atomic: Failed to determine builtin integer sizes, the target platform is not supported. Please, report to the developers.
#endif

#endif // QUARK_ATOMIC_DETAIL_INT_SIZES_HPP_INCLUDED_
