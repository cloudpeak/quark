//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Jens Maurer 2001 - 2003. 
//  (C) Copyright David Abrahams 2002. 
//  (C) Copyright Toon Knapen 2003. 
//  (C) Copyright Boris Gubenko 2006 - 2007.
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.quark.org/LICENSE_1_0.txt)

//  See http://www.quark.org for most recent version.

//  hpux specific config options:

#define QUARK_PLATFORM "HP-UX"

// In principle, HP-UX has a nice <stdint.h> under the name <inttypes.h>
// However, it has the following problem:
// Use of UINT32_C(0) results in "0u l" for the preprocessed source
// (verifyable with gcc 2.95.3)
#if (defined(__GNUC__) && (__GNUC__ >= 3)) || defined(__HP_aCC)
#  define QUARK_HAS_STDINT_H
#endif

#if !(defined(__HP_aCC) || !defined(_INCLUDE__STDC_A1_SOURCE))
#  define QUARK_NO_SWPRINTF
#endif
#if defined(__HP_aCC) && !defined(_INCLUDE__STDC_A1_SOURCE)
#  define QUARK_NO_CWCTYPE
#endif

#if defined(__GNUC__)
#  if (__GNUC__ < 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ < 3))
      // GNU C on HP-UX does not support threads (checked up to gcc 3.3)
#     define QUARK_DISABLE_THREADS
#  elif !defined(QUARK_DISABLE_THREADS)
      // threads supported from gcc-3.3 onwards:
#     define QUARK_HAS_THREADS
#     define QUARK_HAS_PTHREADS
#  endif
#elif defined(__HP_aCC) && !defined(QUARK_DISABLE_THREADS)
#  define QUARK_HAS_PTHREADS
#endif

// boilerplate code:
#define QUARK_HAS_UNISTD_H
#include <quark/config/posix_features.hpp>

// the following are always available:
#ifndef QUARK_HAS_GETTIMEOFDAY
#  define QUARK_HAS_GETTIMEOFDAY
#endif
#ifndef QUARK_HAS_SCHED_YIELD
#    define QUARK_HAS_SCHED_YIELD
#endif
#ifndef QUARK_HAS_PTHREAD_MUTEXATTR_SETTYPE
#    define QUARK_HAS_PTHREAD_MUTEXATTR_SETTYPE
#endif
#ifndef QUARK_HAS_NL_TYPES_H
#    define QUARK_HAS_NL_TYPES_H
#endif
#ifndef QUARK_HAS_NANOSLEEP
#    define QUARK_HAS_NANOSLEEP
#endif
#ifndef QUARK_HAS_GETTIMEOFDAY
#    define QUARK_HAS_GETTIMEOFDAY
#endif
#ifndef QUARK_HAS_DIRENT_H
#    define QUARK_HAS_DIRENT_H
#endif
#ifndef QUARK_HAS_CLOCK_GETTIME
#    define QUARK_HAS_CLOCK_GETTIME
#endif
#ifndef QUARK_HAS_SIGACTION
#  define QUARK_HAS_SIGACTION
#endif
#ifndef QUARK_HAS_NRVO 
#  ifndef __parisc
#    define QUARK_HAS_NRVO
#  endif
#endif
#ifndef QUARK_HAS_LOG1P 
#  define QUARK_HAS_LOG1P
#endif
#ifndef QUARK_HAS_EXPM1
#  define QUARK_HAS_EXPM1
#endif

