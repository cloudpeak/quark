//  (C) Copyright Jim Douglas 2005. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.quark.org/LICENSE_1_0.txt)

//  See http://www.quark.org for most recent version.

//  QNX specific config options:

#define QUARK_PLATFORM "QNX"

#define QUARK_HAS_UNISTD_H
#include <quark/config/posix_features.hpp>

// QNX claims XOpen version 5 compatibility, but doesn't have an nl_types.h
// or log1p and expm1:
#undef  QUARK_HAS_NL_TYPES_H
#undef  QUARK_HAS_LOG1P
#undef  QUARK_HAS_EXPM1

#define QUARK_HAS_PTHREADS
#define QUARK_HAS_PTHREAD_MUTEXATTR_SETTYPE

#define QUARK_HAS_GETTIMEOFDAY
#define QUARK_HAS_CLOCK_GETTIME
#define QUARK_HAS_NANOSLEEP





