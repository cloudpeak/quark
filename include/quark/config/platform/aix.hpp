//  (C) Copyright John Maddock 2001 - 2002. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.quark.org/LICENSE_1_0.txt)

//  See http://www.quark.org for most recent version.

//  IBM/Aix specific config options:

#define QUARK_PLATFORM "IBM Aix"

#define QUARK_HAS_UNISTD_H
#define QUARK_HAS_NL_TYPES_H
#define QUARK_HAS_NANOSLEEP
#define QUARK_HAS_CLOCK_GETTIME

// This needs support in "quark/cstdint.hpp" exactly like FreeBSD.
// This platform has header named <inttypes.h> which includes all
// the things needed.
#define QUARK_HAS_STDINT_H

// Threading API's:
#define QUARK_HAS_PTHREADS
#define QUARK_HAS_PTHREAD_DELAY_NP
#define QUARK_HAS_SCHED_YIELD
//#define QUARK_HAS_PTHREAD_YIELD

// boilerplate code:
#include <quark/config/posix_features.hpp>




