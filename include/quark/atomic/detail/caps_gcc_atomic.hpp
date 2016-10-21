/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.quark.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/caps_gcc_atomic.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef QUARK_ATOMIC_DETAIL_CAPS_GCC_ATOMIC_HPP_INCLUDED_
#define QUARK_ATOMIC_DETAIL_CAPS_GCC_ATOMIC_HPP_INCLUDED_

#include <quark/atomic/detail/config.hpp>
#include <quark/atomic/detail/int_sizes.hpp>

#ifdef QUARK_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(__i386__) && defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8)
#define QUARK_ATOMIC_DETAIL_X86_HAS_CMPXCHG8B 1
#endif

#if defined(__x86_64__) && defined(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_16)
#define QUARK_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B 1
#endif

#if defined(QUARK_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B) && (defined(QUARK_HAS_INT128) || !defined(QUARK_NO_ALIGNMENT))
#define QUARK_ATOMIC_INT128_LOCK_FREE 2
#else
#define QUARK_ATOMIC_INT128_LOCK_FREE 0
#endif

#if __GCC_ATOMIC_LLONG_LOCK_FREE == 2
#define QUARK_ATOMIC_LLONG_LOCK_FREE 2
#else
#define QUARK_ATOMIC_LLONG_LOCK_FREE QUARK_ATOMIC_INT128_LOCK_FREE
#endif

#if __GCC_ATOMIC_LONG_LOCK_FREE == 2
#define QUARK_ATOMIC_LONG_LOCK_FREE 2
#else
#define QUARK_ATOMIC_LONG_LOCK_FREE QUARK_ATOMIC_LLONG_LOCK_FREE
#endif

#if __GCC_ATOMIC_INT_LOCK_FREE == 2
#define QUARK_ATOMIC_INT_LOCK_FREE 2
#else
#define QUARK_ATOMIC_INT_LOCK_FREE QUARK_ATOMIC_LONG_LOCK_FREE
#endif

#if __GCC_ATOMIC_SHORT_LOCK_FREE == 2
#define QUARK_ATOMIC_SHORT_LOCK_FREE 2
#else
#define QUARK_ATOMIC_SHORT_LOCK_FREE QUARK_ATOMIC_INT_LOCK_FREE
#endif

#if __GCC_ATOMIC_CHAR_LOCK_FREE == 2
#define QUARK_ATOMIC_CHAR_LOCK_FREE 2
#else
#define QUARK_ATOMIC_CHAR_LOCK_FREE QUARK_ATOMIC_SHORT_LOCK_FREE
#endif

#if __GCC_ATOMIC_POINTER_LOCK_FREE == 2
#define QUARK_ATOMIC_POINTER_LOCK_FREE 2
#else
#define QUARK_ATOMIC_POINTER_LOCK_FREE 0
#endif


#define QUARK_ATOMIC_INT8_LOCK_FREE QUARK_ATOMIC_CHAR_LOCK_FREE

#if QUARK_ATOMIC_DETAIL_SIZEOF_SHORT == 2
#define QUARK_ATOMIC_INT16_LOCK_FREE QUARK_ATOMIC_SHORT_LOCK_FREE
#elif QUARK_ATOMIC_DETAIL_SIZEOF_INT == 2
#define QUARK_ATOMIC_INT16_LOCK_FREE QUARK_ATOMIC_INT_LOCK_FREE
#elif QUARK_ATOMIC_DETAIL_SIZEOF_LONG == 2
#define QUARK_ATOMIC_INT16_LOCK_FREE QUARK_ATOMIC_LONG_LOCK_FREE
#elif QUARK_ATOMIC_DETAIL_SIZEOF_LLONG == 2
#define QUARK_ATOMIC_INT16_LOCK_FREE QUARK_ATOMIC_LLONG_LOCK_FREE
#else
#define QUARK_ATOMIC_INT16_LOCK_FREE 0
#endif

#if QUARK_ATOMIC_DETAIL_SIZEOF_SHORT == 4
#define QUARK_ATOMIC_INT32_LOCK_FREE QUARK_ATOMIC_SHORT_LOCK_FREE
#elif QUARK_ATOMIC_DETAIL_SIZEOF_INT == 4
#define QUARK_ATOMIC_INT32_LOCK_FREE QUARK_ATOMIC_INT_LOCK_FREE
#elif QUARK_ATOMIC_DETAIL_SIZEOF_LONG == 4
#define QUARK_ATOMIC_INT32_LOCK_FREE QUARK_ATOMIC_LONG_LOCK_FREE
#elif QUARK_ATOMIC_DETAIL_SIZEOF_LLONG == 4
#define QUARK_ATOMIC_INT32_LOCK_FREE QUARK_ATOMIC_LLONG_LOCK_FREE
#else
#define QUARK_ATOMIC_INT32_LOCK_FREE 0
#endif

#if QUARK_ATOMIC_DETAIL_SIZEOF_SHORT == 8
#define QUARK_ATOMIC_INT64_LOCK_FREE QUARK_ATOMIC_SHORT_LOCK_FREE
#elif QUARK_ATOMIC_DETAIL_SIZEOF_INT == 8
#define QUARK_ATOMIC_INT64_LOCK_FREE QUARK_ATOMIC_INT_LOCK_FREE
#elif QUARK_ATOMIC_DETAIL_SIZEOF_LONG == 8
#define QUARK_ATOMIC_INT64_LOCK_FREE QUARK_ATOMIC_LONG_LOCK_FREE
#elif QUARK_ATOMIC_DETAIL_SIZEOF_LLONG == 8
#define QUARK_ATOMIC_INT64_LOCK_FREE QUARK_ATOMIC_LLONG_LOCK_FREE
#else
#define QUARK_ATOMIC_INT64_LOCK_FREE 0
#endif


#if __GCC_ATOMIC_WCHAR_T_LOCK_FREE == 2
#define QUARK_ATOMIC_WCHAR_T_LOCK_FREE 2
#elif QUARK_ATOMIC_DETAIL_SIZEOF_WCHAR_T == 8
#define QUARK_ATOMIC_WCHAR_T_LOCK_FREE QUARK_ATOMIC_INT64_LOCK_FREE
#elif QUARK_ATOMIC_DETAIL_SIZEOF_WCHAR_T == 4
#define QUARK_ATOMIC_WCHAR_T_LOCK_FREE QUARK_ATOMIC_INT32_LOCK_FREE
#elif QUARK_ATOMIC_DETAIL_SIZEOF_WCHAR_T == 2
#define QUARK_ATOMIC_WCHAR_T_LOCK_FREE QUARK_ATOMIC_INT16_LOCK_FREE
#elif QUARK_ATOMIC_DETAIL_SIZEOF_WCHAR_T == 1
#define QUARK_ATOMIC_WCHAR_T_LOCK_FREE QUARK_ATOMIC_INT8_LOCK_FREE
#else
#define QUARK_ATOMIC_WCHAR_T_LOCK_FREE 0
#endif

#define QUARK_ATOMIC_CHAR32_T_LOCK_FREE QUARK_ATOMIC_INT32_LOCK_FREE
#define QUARK_ATOMIC_CHAR16_T_LOCK_FREE QUARK_ATOMIC_INT16_LOCK_FREE

#define QUARK_ATOMIC_THREAD_FENCE 2
#define QUARK_ATOMIC_SIGNAL_FENCE 2

#endif // QUARK_ATOMIC_DETAIL_CAPS_GCC_ATOMIC_HPP_INCLUDED_
