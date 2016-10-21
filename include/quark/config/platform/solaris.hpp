//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Jens Maurer 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.quark.org/LICENSE_1_0.txt)

//  See http://www.quark.org for most recent version.

//  sun specific config options:

#define QUARK_PLATFORM "Sun Solaris"

#define QUARK_HAS_GETTIMEOFDAY

// boilerplate code:
#define QUARK_HAS_UNISTD_H
#include <quark/config/posix_features.hpp>

//
// pthreads don't actually work with gcc unless _PTHREADS is defined:
//
#if defined(__GNUC__) && defined(_POSIX_THREADS) && !defined(_PTHREADS)
# undef QUARK_HAS_PTHREADS
#endif

#define QUARK_HAS_STDINT_H 
#define QUARK_HAS_PTHREAD_MUTEXATTR_SETTYPE 
#define QUARK_HAS_LOG1P 
#define QUARK_HAS_EXPM1


