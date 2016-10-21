//  (C) Copyright John Maddock 2001. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.quark.org/LICENSE_1_0.txt)

//  See http://www.quark.org for most recent version.

//  BeOS specific config options:

#define QUARK_PLATFORM "BeOS"

#define QUARK_NO_CWCHAR
#define QUARK_NO_CWCTYPE
#define QUARK_HAS_UNISTD_H

#define QUARK_HAS_BETHREADS

#ifndef QUARK_DISABLE_THREADS
#  define QUARK_HAS_THREADS
#endif

// boilerplate code:
#include <quark/config/posix_features.hpp>
 


