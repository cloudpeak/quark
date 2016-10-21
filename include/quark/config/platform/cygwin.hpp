//  (C) Copyright John Maddock 2001 - 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.quark.org/LICENSE_1_0.txt)

//  See http://www.quark.org for most recent version.

//  cygwin specific config options:

#define QUARK_PLATFORM "Cygwin"
#define QUARK_HAS_DIRENT_H
#define QUARK_HAS_LOG1P
#define QUARK_HAS_EXPM1

//
// Threading API:
// See if we have POSIX threads, if we do use them, otherwise
// revert to native Win threads.
#define QUARK_HAS_UNISTD_H
#include <unistd.h>
#if defined(_POSIX_THREADS) && (_POSIX_THREADS+0 >= 0) && !defined(QUARK_HAS_WINTHREADS)
#  define QUARK_HAS_PTHREADS
#  define QUARK_HAS_SCHED_YIELD
#  define QUARK_HAS_GETTIMEOFDAY
#  define QUARK_HAS_PTHREAD_MUTEXATTR_SETTYPE
#  define QUARK_HAS_SIGACTION
#else
#  if !defined(QUARK_HAS_WINTHREADS)
#     define QUARK_HAS_WINTHREADS
#  endif
#  define QUARK_HAS_FTIME
#endif

//
// find out if we have a stdint.h, there should be a better way to do this:
//
#include <sys/types.h>
#ifdef _STDINT_H
#define QUARK_HAS_STDINT_H
#endif

/// Cygwin has no fenv.h
#define QUARK_NO_FENV_H

// boilerplate code:
#include <quark/config/posix_features.hpp>

//
// Cygwin lies about XSI conformance, there is no nl_types.h:
//
#ifdef QUARK_HAS_NL_TYPES_H
#  undef QUARK_HAS_NL_TYPES_H
#endif
 




